/** 
    @file EagleSDK_4_20_mA_loop.ino 
    @authors Rebecca McWilliam <rmcwilliam@irisdynamics.com>
    @version 2.2.0
    @brief  This program uses the EagleSDK_2.0 libraries to output a pwm signal. This signal is being constrained such that the motor's position is normalized between 4-20mA using
            and external pwm controlled 4-20mA current loop simulator board (A2127).
            An input ctrl signal will be used to control the force of the motor.

            The PWM ouptut signal are on pins 25 and 32 corresponding to IO A and B on the Eagle, both series resistors are shorted on the IO circuit for these channels.
            Ctrl signals are on pins A4 and A5 corresponding to IO C and D on the Eagle, the first series resistor is shorted, the second is 1.58kOhm.
            There is a 133 ohm resistor across the LED pad to ground. A 5V ESD diode and a 0.1 uF capacitor.

    Copyright 2022 Iris Dynamics Ltd 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    For questions or feedback on this file, please email <support@irisdynamics.com>. 
*/

/*
    Include addional Eagle SDK libraries and files within this project
*/
#include <iriscontrols4.h>                          //iris controls 4 library (GUI Handling)
#include <modbus_lib.h>                             //modbus client library (UART communications with motors)
#include "client/device_applications/actuator.h"    //actuator objects (abstracts communication to motor)
#include "Main_GUI.h"                               //custom IrisControls GUI interface
#include <EEPROM.h>                                 //save values to Eagle memory


#define alpha 0.03                                  //ctrl signal filter

//Motors on UART port 1 and 2
Actuator motor[2] {
    {1, "Orca 1", CYCLES_PER_MICRO}
    , {2, "Orca 2", CYCLES_PER_MICRO}
};

int32_t ctrl_current[2];                            //input ctrl current
int32_t target_force[2];                            //target motor force
int out_pwm[2];                                     //output signal from motor position

enum {
    inactive,
    ramp_zone,
    active
};
int control_state[2] = {inactive, inactive};

//Pass reference to the GUI
GUI gui(motor,
        ctrl_current,
        target_force,
        out_pwm,
        control_state);                                     //Pass by reference the motor obeject to the gui object so that gui elements have access to the motor
IrisControls4 *IC4_virtual = &gui;                  //Pointer to the gui that will be used by that will be used to check version compatibility and occasional writing ot the console with errors

int analog_inpin[2] = {A4, A5};

int analog_outpin[2] = {25, 32};

int new_ctrl_current[2];

Actuator::ConnectionConfig connection_config;


uint32_t ramp_zone_start[2];
uint32_t ramp_zone_period = 2000;


/*
    @brief Setup function is called once at the first when the Eagle resets (bootloader button pressed or power cycled)
    Set up the pins and analog resolutions.
    Initalize and enable the motors and read configuration values from EEPROM
*/
void setup() {
    analogWriteResolution(12);
    analogReadResolution(12);
    connection_config.target_baud_rate_bps      = 780000;  //625000 //780000
    connection_config.target_delay_us           = 0;

    for (int i = 0; i < 2; i++) {
        motor[i].init();                                   //intialize the UART port on the Eagle to allow communications with a motor (enabling interrupts and setting a default baud rate)
        motor[i].enable();                                  //Start pinging the port for a connected motor (will automatically handshake when detected)
        pinMode(analog_inpin[i], INPUT);
        pinMode(analog_outpin[i], OUTPUT);
        motor[i].set_connection_config(connection_config);
        motor[i].set_mode(Actuator::SleepMode);
        int j = motor[i].channel_number();
        if (EEPROM.read(0 + j * 10) == EEPROM_VERSION) {
            gui.current_loop_gui[i].max_position = EEPROM.read(1 + j * 10) + (EEPROM.read(2 + j * 10) << 8) + (EEPROM.read(3 + j * 10) << 16) + (EEPROM.read(4 + j * 10) << 24);
            gui.current_loop_gui[i].force_gain = EEPROM.read(5 + j * 10) + (EEPROM.read(6 + j * 10) << 8) + (EEPROM.read(7 + j * 10) << 16) + (EEPROM.read(8 + j * 10) << 24);
        }
        else{
             gui.current_loop_gui[i].max_position = 100000;
             gui.current_loop_gui[i].force_gain = 2000;
        }
    }

}


/*
    @brief Main loop that gets called continuously
    Motor frames communication are done here, depending on the mode either Sleep, Force or Position will be commanded
    Return frame contains information about motor position, force, temperature, power, errors.
    When the in inactive mode the motor will sleep until a ctrl signal greater than 3.8 mA is received which will move it to ramp zone.
    The target force output will ramp up based on the value of the ramp period. When that period is reached, provided the ctrl signal has not
    dropped below 3.8 mA and become inactive, the control state will move to active where the target force will be directly related to the
    ctrl signal without ramping.
*/
void loop() {

    for (int i = 0; i < 2; i++) {
        motor[i].set_force_mN(target_force[i]);
        motor[i].run_in();                                 //Parse incoming motor frames (Motor -> Eagle)
        motor[i].run_out();                                //Send out motor frames (Eagle -> Motor)

        if (!motor[i].is_connected()) control_state[i] = inactive;

        //filter ctrl current signal
        new_ctrl_current[i] = analogRead(analog_inpin[i]) * ADC_TO_uA;
        ctrl_current[i] = ctrl_current[i] * ( 1 - alpha) + new_ctrl_current[i] * alpha;
        switch (control_state[i]) {
            case inactive:
                target_force[i] = 0;
                motor[i].set_mode(Actuator::SleepMode);
                if ((ctrl_current[i]) > 3800) {
                    if (motor[i].get_errors() || !motor[i].is_connected() || (IC4_virtual->is_connected() && gui.current_loop_gui[i].sleep_btn.get())) {
                        motor[i].set_mode(Actuator::SleepMode);
                    }
                    else {
                        control_state[i] = ramp_zone;
                        ramp_zone_start[i] = millis();
                        motor[i].set_mode(Actuator::ForceMode);
                    }

                }
                break;
            case ramp_zone:
                target_force[i] = (((ctrl_current[i] - 12000) * gui.current_loop_gui[i].force_gain * 2) / USEABLE_CURRENT_RANGE);
                target_force[i] = target_force[i] * ( (uint32_t)(millis() - ramp_zone_start[i]) / (float)ramp_zone_period);
                if ( (uint32_t)(millis() - ramp_zone_start[i]) > ramp_zone_period ) {
                    control_state[i] = active;
                    motor[i].set_mode(Actuator::ForceMode);
                }
                if ((ctrl_current[i]) < 3800) {
                    control_state[i] = inactive;
                    target_force[i] = 0;
                    motor[i].set_mode(Actuator::SleepMode);
                }
                break;
            case active:
                target_force[i] = (((ctrl_current[i] - 12000) * gui.current_loop_gui[i].force_gain * 2) / USEABLE_CURRENT_RANGE) ;
                if ((ctrl_current[i]) < 3800) {
                    control_state[i] = inactive;
                    target_force[i] = 0;
                    motor[i].set_mode(Actuator::SleepMode);
                }
                break;
        }
        //bound the output pwm signal from for the motor position between 4-20mA
        out_pwm[i]  = motor[i].get_position_um() * USEABLE_PWM_RANGE / gui.current_loop_gui[i].max_position + PWM_MIN_OFFSET;
        if (out_pwm[i] > (PWM_MIN_OFFSET + USEABLE_PWM_RANGE)) out_pwm[i] = PWM_MIN_OFFSET + USEABLE_PWM_RANGE;
        if (out_pwm[i] < PWM_MIN_OFFSET) out_pwm[i] = PWM_MIN_OFFSET;
        analogWrite(analog_outpin[i], out_pwm[i]);
    }

    gui.run();                                      //Run IrisControls connectivity, GUI element interaction, serial parsing found in Main_GUI.h
}

/*
    Interrupts handling for uart 1 and 2
    The uart status interrupt is fired when a message byte is either sent or received
    The motor's isr function handles the sending and receiving of bytes
*/
void uart1_status_isr() {
    motor[0].isr();
}

void uart2_status_isr() {
    motor[1].isr();
}

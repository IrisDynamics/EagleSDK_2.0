/** 
    @file Main_GUI.h
    @author Rebecca McWilliam <rmcwilliam@irisdynamics.com>
    @brief Main application that handles IrisControls connection and gui interaction
    @version 2.2.0

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

#ifndef MAIN_GUI_H_
#define MAIN_GUI_H_

#include "device_drivers/k20/ic4_k20.h"
#include "client/device_applications/actuator.h"
#include "orca600.h"

#include "Current_loop_panel.h"


/**
    @file Main_GUI.h
    @class GUI
    @brief Extension of the K20 (Eagle) device driver for the IC4 library, handles connectivity with IrisControls4 and gui element interaction
*/
class GUI : public IC4_k20 {

        Actuator* motor;                                    //Reference to an actor object that will be passed in when this object is initialized
        uint32_t gui_timer = 0;                      // This will keep track of the last update
        uint8_t gui_update_period = 20;             //This is the time between updates in milliseconds (100 ms = 10 fps)

    public:
        CurrentLoopPanel current_loop_gui[2];

        //Constructor
        GUI(
            Actuator* _motor                                //Parameter for constructing the GUI object is a reference to a motor
            //this will allow this object to have access to control and feedback from the motor.
            , int32_t* _ctrl_current
            , int32_t* _target_force
            , int* _out_pwm
            , int* _control_state
        ):
            motor(_motor)                                   //Initialization list
            , current_loop_gui{{_motor[0], _ctrl_current[0], _target_force[0], _out_pwm[0], _control_state[0], "Motor 1" , 19, 0},
            {_motor[1], _ctrl_current[1], _target_force[1], _out_pwm[1], _control_state[1], "Motor 2" , 40, 0}}
        {
            set_server_name("4-20mA Control v 2.2.0");                  //Server name, changes the name in the initial connection message with IrisControls
            set_device_id("Eagle");                         //Device ID, changes how the device will show up in the com port drop down
        }

        /*
            @Brief Handles connectivity and gui interaction with IrisControls
        */
        void run() {
            check();                                        // Parses incoming serial communications (IrisControls -> Eagle)
            switch (gui_frame_state) {
                case rx:
                    // If connection times out, set disconnected
                    if ( is_timed_out() ) {
                        set_disconnected();
                    }
                    break;

                case tx:
                    if (new_connection()) {                                                             // IRIS CONTROLS HAS ESTABLISHED CONNECTION
                        print_l("4-20mA Control Example shows how two motors can react to one another using GPIO.");
                        print_l(" See the Eagle Current Loop IO User Guide for more details. \r");
                        setup();
                    }

                    if (is_connected() ) {                          // IRIS CONTROLS REGULAR UPDATES
                        // When IrisControls is connected only update the gui at a specified gui period (in milliseconds)
                        // This dictates the frame rate of the GUI, if the gui period is too large the gui might be choppy
                        // If the period is too small there will be an unneeded amount of serial traffic and could cause lag
                        if ( (uint32_t)(millis() - gui_timer) > gui_update_period ) {
                            gui_timer = millis();
                            gui_update();
                            // Transmit end of transmission message
                            end_of_frame();
                        }
                    }
                    send();                                         //Sends anything in the transmit buffer (Eagle -> IrisControls)
                    break;
            }//SWITCH
        }

    private:
        /*
            @brief GUI initalization called from check for new IrisControls connection
        */
        void setup() {
            gui_set_grid(35, 65);                                                           // This will set the size of the IrisControls window,
            print_l("Eagle Connected to IrisControls\r");                                   // Message is printed when IrisControls establishes a connection with the Eagle
            current_loop_gui[0].setup();
            current_loop_gui[1].setup();

            int j = motor[0].channel_number();
            if (EEPROM.read(0 + j * 10) == EEPROM_VERSION) {

                current_loop_gui[0].max_position = EEPROM.read(1 + j * 10) + (EEPROM.read(2 + j * 10) << 8) + (EEPROM.read(3 + j * 10) << 16) + (EEPROM.read(4 + j * 10) << 24);
                current_loop_gui[0].force_gain = EEPROM.read(5 + j * 10) + (EEPROM.read(6 + j * 10) << 8) + (EEPROM.read(7 + j * 10) << 16) + (EEPROM.read(8 + j * 10) << 24);
            }
            else {
                current_loop_gui[0].max_position = 100000;
                current_loop_gui[0].force_gain = 2000;
            }
        }
        /*
            @brief action to be called every gui frame go here
            This is called inside the is connected gui update loop
            Run the current loop panel for each motor.
        */
        void gui_update() {
            current_loop_gui[0].run();
            current_loop_gui[1].run();
        }

};

#endif

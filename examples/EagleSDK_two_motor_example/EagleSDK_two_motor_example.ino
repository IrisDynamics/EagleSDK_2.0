/**
 * @file EagleSDK_two_motor_example.ino
 * @author Rebecca McWilliam <rmcwilliam@irisdynamics.com>
 * @brief Example of using two actuator objects to create motor movement with either position control or force control
          Graphs that give motor feedback
          Using gui elements panels and communication objects from the eagle sdk libraries
 * @version 2.2.2
 * @date 2022-08-10
 * 
 * @copyright Copyright 2022 Iris Dynamics Ltd 
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
 * 
 */


#include <iriscontrols4.h>  //iris controls 4 library (GUI Handling)
#include <modbus_lib.h>  //modbus client library (UART communications with motors)
#include "client/device_applications/actuator.h" //actuator objects (abstracts communication to motor)
#include "Main_GUI.h"  //custom GUI interface


/*  Initialize array of actuator objects use 1 up to 3
    The channel or Uart number corresponds to which port on the eagle the motor is plugged into.
*/
Actuator motors[2] {
  {1, "Orca 1", CYCLES_PER_MICRO}
  , {2, "Orca 2", CYCLES_PER_MICRO}
};

int32_t force_target[2];
int32_t position_target[2];

/*
    Pass the array of motors to the gui object to be used to update gui elements
*/
GUI gui(motors, force_target, position_target);
IrisControls4 *IC4_virtual = &gui;
//!< custom communication settings for baud rate and interframe delay to allow faster communication than modbus protocol
Actuator::ConnectionConfig connection_config;
/*
    @brief initialize and enable the motors
    Initializing the motor will set up the UART on the specified port with the default baud rate
    and appropriate interrupts
    Enabling the motor means that discovery pings will begin sending on the motor's port in
    order to handshake with the motor and establish a connection
*/
void setup() {
  /// This section is optional, if not added will default to 625000 bps and 80us
  connection_config.target_baud_rate_bps      = 780000;  //625000 //780000
  connection_config.target_delay_us           = 0;
  for (int i = 0; i < 2; i++) {
    motors[i].set_connection_config(connection_config);
    motors[i].init();
    motors[i].enable();
  }
}

/*
    @brief Main loop that runs the gui, creates and parses motor communication frames
*/
void loop() {
  gui.run();
  for (int i = 0; i < 2; i++) {
    motors[i].set_force_mN(force_target[i]);
    motors[i].set_position_um(position_target[i]);
    motors[i].run_in();
    motors[i].run_out();
  }
}

/*
    Interrupts handling for uart 1
    The uart status interrupt is fired when a message byte is either sent or received
    The motor's isr function handles the sending and receiving of bytes
*/

void uart1_status_isr(void) {
  motors[0].isr();
}
void uart2_status_isr(void) {
  motors[1].isr();
}

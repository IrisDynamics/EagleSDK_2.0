/**
    Tutorial Starting Point:
    This project serves as a starting point to follow the EagleSDK tutorial guide.
    
    Getting Started:
    1. Set board target (Tools -> Board -> teensyduino -> Teensy 3.2/3.1)
    2. Set sketchbook location to the EagleSDK_2.0 folder (File -> Preferences -> Sketchbook Location: C:\Users\RMcWilliam\Desktop\Repository\EagleSDK_2.0)
       While in preference line numbers can be turned on by checking the display line number box
    3. Press the check mark in the top left to compile the code (there will be a green progress bar in the bottom right)
    4. The build will automatically load to the teensy.exe app. Ensure the green auto button is pressed
    5. When the Eagle is plugged in via micro usb (or while powered and connected with isolated usb) press the physical button on the bootloader board(small board connected to the Eagle).
       A programing progress bar will begin in the teensy app.
    6. Now that this firmware has been flashed to the board, open the IrisControls software (EagleSDK_2.0/IrisControls4/IrisControls4.exe)
    7. There will be a drop down menu that you can use to select the com port of the Eagle. 
    8. Once connected there will be a message in the console box saying that an Eagle has been connected.
       
    @author Rebecca McWilliam <rmcwilliam@irisdynamics.com>
    @version 2.2.0
    
    @copyright Copyright 2022 Iris Dynamics Ltd 
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
 * Include addional Eagle SDK libraries and files within this project
 */
#include <iriscontrols4.h>                          // Iris controls 4 library (GUI Handling)
#include <modbus_lib.h>                             // Modbus client library (UART communications with motors)
#include "client/device_applications/actuator.h"    // Actuator objects (abstracts communication to motor)
#include "Main_GUI.h"                               // Custom IrisControls GUI interface

//Motor connected on port 1 of the Eagle board
Actuator motor(1, "Motor 1", CYCLES_PER_MICRO);     // Initialize the actuator object to be a motor plugged into port 1 of the Eagle 
                                                    // The port number specifies the UART channel being used (communications with motor)
                                                    // Changing the port will require changing the interrupt handler at the bottom of this file

//Pass reference of the motor object to the GUI
GUI gui(motor);                                     // Pass by reference the motor object to the gui object so that gui elements have access to the motor
IrisControls4 *IC4_virtual = &gui;                  // Pointer to the gui that will be used by that will be used to check version compatibility and occasional writing ot the console with errors


/*
 * @brief Setup function is called once at the first when the Eagle resets (bootloader button pressed or power cycled)
 */
void setup() {
    motor.init();                                   // Intialize the UART port on the Eagle to allow communications with a motor (enabling interrupts and setting a default baud rate)
    motor.enable();                                 // Start pinging the port for a connected motor (will automatically handshake when detected)
}


/*
 * @brief Main loop that gets called continuously
 * Motor frames communication are done here, depending on the mode either Sleep, Force or Position will be commanded
 * Return frame contains information about motor position, force, temperature, power, errors.
 * Additional commands can be injected into the stream.
 */
void loop() {
    motor.run_in();                                 // Parse incoming motor frames (Motor -> Eagle)
    motor.run_out();                                // Send out motor frames (Eagle -> Motor)
    gui.run();                                      // Run IrisControls connectivity, GUI element interaction, serial parsing found in Main_GUI.h 
}

/*
    Interrupts handling for uart 1 
    The uart status interrupt is fired when a message byte is either sent or received
    The motor's isr function handles the sending and receiving of bytes
*/
void uart1_status_isr() {                           // If port 2 is used instead of or in addition to port 1 when initializing the motor object uart2_status_isr() should be used
    motor.isr();
}

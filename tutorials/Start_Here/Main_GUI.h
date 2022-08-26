/**
    @file Main_GUI.h
    @author Rebecca McWilliam
    @brief Main application that handles IrisControls connection and gui interaction
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

#ifndef MAIN_GUI_H_
#define MAIN_GUI_H_

#include "device_drivers/k20/ic4_k20.h"
#include "client/device_applications/actuator.h"

/**
    @file Main_GUI.h
    @class GUI
    @brief Extension of the K20 (Eagle) device driver for the IC4 library, handles connectivity with IrisControls4 and gui element interaction
*/
class GUI : public IC4_k20 {

        Actuator& motor;                                    // Reference to an actuator object that will be passed in when this object is initialized
        uint32_t gui_timer = 0;                             // This will keep track of the last update
        uint8_t gui_update_period = 100;                    // This is the time between updates in milliseconds (100 ms = 10 fps)
    public:

        /* Constructor */
        GUI(
            /** Parameter for constructing the GUI object is a reference to a motor. This will allow this object to have access to control and receive feedback from the motor */
            Actuator& _motor
        ):
            /* Initialization List */
            motor(_motor)                                   
        {
            set_server_name("Start Here");                  // Server name, changes the name in the initial connection message with IrisControls
            set_device_id("Eagle");                         // Device ID, changes how the device will show up in the com port drop down
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
                        reset_all();
                    }
                    break;

                case tx:
                    if (new_connection()) {                 // IRIS CONTROLS HAS ESTABLISHED CONNECTION
                        setup();
                    }

                    if (is_connected() ) {                  // IRIS CONTROLS REGULAR UPDATES
                        // When IrisControls is connected only update the gui at a specified gui period (in milliseconds)
                        // This dictates the frame rate of the GUI, if the gui period is too large the gui might be choppy
                        // If the period is too small there will be an unneeded amount of serial traffic and could cause lag
                        if ( (uint32_t)(millis() - gui_timer) > gui_update_period ) {
                            gui_timer = millis();

                            // Update GUI
                            frame_update();
                            
                            // Transmit end of transmission message
                            end_of_frame();
                        }
                    }
                    send();                                 // Sends anything in the transmit buffer (Eagle -> IrisControls)
                    break;
            }//SWITCH
        }

    private:

        /*
            @brief GUI initalization called from check for new IrisControls connection
        */
        void setup() {
            gui_set_grid(30, 30);                           // This will set the size of the IrisControls window,
            print_l("Eagle Connected to IrisControls\r");   // Message is printed when IrisControls establishes a connection with the Eagle
        }
        
        /*
            @brief action to be called every gui frame go here
            This is called inside the is_connected gui update loop
        */
        void frame_update() {
        }

        /** @brief Reset all gui elements */
        void hide_all(){
          
        }

        /** @brief Reset all gui elements */
        void reset_all(){
          
        }

};

#endif

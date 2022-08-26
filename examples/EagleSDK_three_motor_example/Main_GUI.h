/**
    @file Main_GUI.h
    @author Kali Erickson, Rebecca McWilliam
    @brief Main application that populates the gui elements when iriscontrols is connected
    Any other behaviour that either needs to happen in or out of the gui, or during a connection or disconnection from iriscontrols can be done here
    @version 2.2.5

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

#include <iriscontrols4.h>
#include <device_drivers/k20/ic4_k20.h>
#include "client/device_applications/actuator.h"
#include "Motor_Plot_Panel.h"
#include "Motor_Control_Panel.h"
/**
    @file Main_GUI.h
    @class GUI
    @brief Class makes and updates elements in the GUI.
*/
class GUI : public IC4_k20 {

        uint16_t last_GUI_update;
        Actuator* motors;

    public:
        uint32_t tnow = millis();
        int32_t* force_target;
        int32_t* position_target;
        Motor_Plot motor_plot[3];           //from gui_panels library
        Motor_Control motor_control[3];

        GUI(
            Actuator* _motors
            , int32_t* _force_target
            , int32_t* _position_target
        ):
            motors(_motors)
            , force_target(_force_target)
            , position_target(_position_target)
        {
            set_server_name("Three Motor Example v 2.2.5");
            set_device_id("Eagle");
        }

        /*
            @brief Setup the gui panels
        */
        void setup() {
            motor_control[0].add(&motors[0], &force_target[0], &position_target[0], 3, 43);
            motor_control[1].add(&motors[1], &force_target[1], &position_target[1], 18, 43);
            motor_control[2].add(&motors[2], &force_target[2], &position_target[2], 32, 43);
            motor_plot[0].add(&motors[0], "Orca 0", 1, 19, 10, 20);
            motor_plot[1].add(&motors[1], "Orca 1", 16, 19, 10, 20);
            motor_plot[2].add(&motors[2], "Orca 2", 30, 19, 10, 20);

        }

        /*
            @Brief Handles
            Runs the run function of the current panels
        */
        void run() {
            check();
            switch (gui_frame_state) {
                ////////////// RX STATE /////////////////////////////////
                case rx: {

                        /////////////////// IRIS CONTROLS IS TIMED OUT ////////////////////
                        if ( is_timed_out() ) {

                            // DO THINGS WHEN TIMED OUT...

                            set_disconnected();
                        }
                        break;
                    } // RX CASE

                ////////////// TX STATE /////////////////////////////////
                case tx: {

                        /////////////////// IRIS CONTROLS RECONNECT AFTER TIMEOUT /////////
                        if ( restored_connection()) {
                            print_l("\r\r==== Iris Controls Was Timed Out ====\r\r");

                            //DO THINGS...

                        }

                        /////////////////// IRIS CONTROLS HAS ESTABLISHED CONNECTION //////
                        if (new_connection()) {
                            print_l("The Three Motor Example shows how the Eagle can control up to three motors at once, by using position or force control. ");
                            print_l("It shows a plot for each motor, which displays a green title when connected, a red title when connected with error(s), and a grey title when not connected. ");
                            print_l("The motor control panel beside each plot is made up of buttons that will send commands to each respective motor, ");
                            print_l("as well as sliders to change the commanded position or force. ");
                            print_l("The sliders will activate when their corresponding button is toggled, enabling force or position mode.\r");
                            gui_set_grid(45, 65);
                            setup();
                            last_GUI_update = millis();

                        }

                        /////////////////// IRIS CONTROLS REGULAR UPDATES /////////////////
                        if (is_connected() ) {

                            tnow = millis();
                            static uint32_t gui_timer = 0;
                            static uint8_t gui_update_period = 10;
                            if ( (uint32_t)(tnow - gui_timer) > gui_update_period ) {
                                gui_timer = tnow;
                                for (int i = 0; i < 3; i++) {
                                    motor_plot[i].run();
                                    motor_control[i].run();
                                }
                                // Reset last update time
                                last_GUI_update = millis();

                                // Transmit end of transmission message which signals IC4 to transmit in half duplex
                                end_of_frame();

                            }
                        }
                        send();
                        break;
                    } // TX CASE
            } // SWITCH
        } // run()

    protected:

        int parse_app(char * cmd, char * args) {
            std::string command_list;

#define SERIAL_COMMAND(_ARG_)                   \
    COMMAND_IS (  (command_list += (std::string)_ARG_ + (std::string)"\r\n").capacity()  ? _ARG_: _ARG_    ) THEN_DO

            START_PARSING

            COMMAND_IS "a" THEN_DO
            IC4_virtual->print_l("bc");

            COMMAND_IS "s" THEN_DO
            IC4_virtual->print_l("\rsleep");
            motors[0].set_mode(Actuator::SleepMode);
            motors[1].set_mode(Actuator::SleepMode);
            motors[2].set_mode(Actuator::SleepMode);

            FINISH_PARSING
        }

};

#endif

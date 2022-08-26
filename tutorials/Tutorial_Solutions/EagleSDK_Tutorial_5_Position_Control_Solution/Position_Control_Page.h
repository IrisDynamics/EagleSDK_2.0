/**
    @file Position_Control_Page.h
    @class Position_Control_Page
    @brief Provides control for updating Orca motor's position
    @author Michelle Aleman <maleman@irisdynamics.com>
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

#ifndef _POSITION_CONTROL_PAGE_H_
#define _POSITION_CONTROL_PAGE_H_

#include "Signal_Panel.h"
#include "Motor_Plot_Panel.h"


class Position_Control_Page {

        Actuator& motor;                                                // Reference to an actuator object that will be passed in when this object is initialized

        Dataset position_signal;                                        // Dataset to add to plot. Data will always take the Signal_Panel signal value

        Motor_Plot motor_plot;                                          // Motor plot object to display live motor data
        FlexLabel page_label;                                           // Position Control page label element
        GUI_Page  page_elements;                                        // GUI_Page object to handle displaying/hiding all elements in home page

        bool first_setup = true;                                        // Boolean value tracks whether or not the page has been initialized yet
        int32_t signal_init_value;                                      // Value used by the signal panel to track the motor's starting position, used to avoid sudden extreme changes in position
        
    public:
        Signal_Panel signal_panel;                                      // Provides interface for entering signal type and parameters
        bool is_running = true;                                         // Boolean value tracks whether or not the page is active

        /* Constructor */
        Position_Control_Page(
            /** Parameter for constructing the GUI object is a reference to a motor. This will allow this object to have access to control and feedback from the motor.*/
            Actuator& _motor

        ):
            /* Initialization List */
            motor(_motor)
        {}


        /** @brief Handles initializing position control page elements */
        void setup() {
            if (first_setup) {
                
                // Initialize GUI_Page object
                page_elements.add();

                // Initialize signal panel
                signal_panel.add(&page_elements, &signal_init_value, 5, 19);
                
                // Initialize motor plot
                motor_plot.add(&page_elements, &motor, "Orca Motor", 1, 35);

                // Add position signal to plot
                position_signal.add(&motor_plot.plot, "Position Signal", "Time", "*mu*m", Dataset::TIMEPLOT + Dataset::NONE);
                position_signal.set_max_data_points(25000);
                position_signal.set_colour(GREEN);
                position_signal.show();

                // Initialize home page label element
                page_label.add(&page_elements, "<p_style=\"font-size:20px;\">Position Control</p>", 1, 19, 2, 10);
            }
            else {
                page_elements.show();
            }
            is_running = true;
            motor.set_mode(Actuator::PositionMode);
            motor.tune_position_controller(200,0,0,5000);
        }

        /**
            @brief Handles updating the Position Page with Orca data and running the signal panel.
        */
        void run() {
            if (!is_running) return;
            
            // Update signal fields displayed depending on slider value
            signal_panel.run();
            signal_init_value = motor.get_position_um();

            // Update position signal dataset with signal value
            position_signal.add_data(IC4_virtual->system_time(), (int)(signal_panel.get_target_value()));
            
            // Update plot with motor data
            motor_plot.run();
        }

        /**
         * @brief Hides all Position Control Page elements in GUI view
        */

        void hide() {
            page_elements.hide();
            is_running = false;
        }

        /**
         * @brief Resets all Position Control Page elements in GUI view
        */
        void reset() {
            hide();
            first_setup = true;
        }
};

#endif

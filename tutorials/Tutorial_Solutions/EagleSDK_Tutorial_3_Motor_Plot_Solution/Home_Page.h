/**
    @file Home_Page.h
    @author Michelle Aleman <maleman@irisdynamics.com>
    @brief Home page displays Orca motor data
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

#ifndef _HOME_PAGE_H_
#define _HOME_PAGE_H_

#include "Motor_Plot_Panel.h"
/**
    @file Home_Page.h
    @class Home_Page
    @brief Displays Orca motor data
*/
class Home_Page {

        Actuator& motor;                                    // Reference to an actuator object that will be passed in when this object is initialized

        Motor_Plot motor_plot;                              // Motor plot object to display live motor data

        Dataset new_data;                                   // New dataset to add to plot: data will always take the new_data_slider slider value.

        FlexSlider new_data_slider;                         // Slider whose value is used as the new_data y-value

        FlexLabel page_label;                               // Home page label element

        FlexData position_element;                          // Data element for displaying the motor's position

        GUI_Page  page_elements;                            // GUI_Page object to handle displaying/hiding all elements in home page

        bool first_setup = true;                            // Boolean value tracks whether or not the page has been initialized yet

    public:
        bool is_running = true;                             // Boolean value tracks whether or not the page is active

        /* Constructor */
        Home_Page(
            /** Parameter for constructing the GUI object is a reference to a motor. This will allow this object to have access to control and receive feedback from the motor */
            Actuator& _motor
        ):
            /* Initialization List */
            motor(_motor)
        {}

        /**
            @brief Handles initializing the home page
        */
        void setup() {
            if (first_setup) {
                first_setup = false;
               
                // Initialize GUI_Page object
                page_elements.add();
                
                // Initialize motor plot
                motor_plot.add(&page_elements, &motor, "Orca Motor", 1, 35);

                // Add new dataset to plot
                new_data.add(&motor_plot.plot, "New Data", "Time", "Slider Value", Dataset::TIMEPLOT + Dataset::NONE);
                new_data.set_max_data_points(25000);
                new_data.set_colour(GREEN);
                new_data.show();

                // Init slider for dataset values
                new_data_slider.add(&page_elements, "Plot Value", 8, 19, 1, 15, 0, 300, 0, 1000, FlexSlider::ALLOW_INPUT);

                // Initialize position data element
                position_element.add(&page_elements, "Position: ", 5, 19, 2, 10, 0, 1, "*mu*m", FlexData::UNITS);  // Init element with a name, row and col anchors, row and col spans, init value, denominator (can be used to divide a value for unit conversions, using 1 has no effect), units, and configurations.

                // Initialize home page label element
                page_label.add(&page_elements, "<p_style=\"font-size:20px;\">Home</p>", 1, 19, 2, 9);
            }
            else {
                page_elements.show();
            }
            is_running = true;
        }

        /**
            @brief Handles updating the home page with Orca data
        */
        void run() {
            if (!is_running) return;
            
            // Update motor plot with motor data
            motor_plot.run();

            // Update new dataset
            uint64_t now = IC4_virtual->system_time();      // Get current time
            new_data.add_data(now, new_data_slider.get());

            // Update position element with motor position
            position_element.update(motor.get_position_um());
        }

        /**
            @brief Hides all Home Page elements in GUI view
        */
        void hide() {
            page_elements.hide();
            is_running = false;
        }

        /**
            @brief Resets all Home Page elements in GUI view
        */
        void reset() {
            hide();
            first_setup = true;
        }
};

#endif
/**
 * @file Home_Page.h
 * @version 2.2.0
    
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


class Home_Page {
        Actuator& motor;                                    // Reference to an actuator object that will be passed in when this object is initialize
        FlexData position_element;                          // Data element for displaying the motor's position
        FlexLabel   page_label;                             // Label for this page
        GUI_Page page_elements;                             // GUI_Page object to handle hiding/displaying page contents
        bool first_setup = true;                            // Boolean value tracks whether or not the page has been initialized yet

    public:
        bool is_running = true;                             // Boolean value tracks whether or not the page is active
        
        /* Constructor */
        Home_Page(
            /* Parameter for constructing the GUI object is a reference to a motor. This will allow this object to have access to control and receive feedback from the motor */
            Actuator& _motor
        ):
            /* Initialization List */
            motor(_motor)
        {}


        /**
            @brief Initializes all home page elements and puts the motor into sleep mode.
        */
        void setup() {
            if (first_setup) {
                first_setup = false;

                // Initialize GUI_Page object
                page_elements.add();

                // Initialize position data element
                position_element.add(&page_elements, "Position: ", 5, 19, 2, 10, 0, 1, "*mu*m", FlexData::UNITS);  // Init data element with a name, row and col anchors, row and col spans, init value, denominator (can be used to divide a value passed to the element, using 1 has no effect), units, and configurations.
                
                // Initialize home page label element

                page_label.add(&page_elements, "<p_style=\"font-size:20px;\">Home</p>", 1, 19, 2, 9);
            }
            else {
                page_elements.show();
            }
            is_running = true;
        }

        /**
            @brief Handles updating home page elements with motor data.
        */
        void run() {
            if (!is_running) return;
            
            // Update position element with motor position
            position_element.update(motor.get_position_um());
        }
        
    
        /**
            @brief Hides all home page elements from GUI view
        */
        void hide() {
            page_elements.hide();
            is_running = false;
        }

        /**
            @brief Resets the home page so that it will reinitialized if set up again.
        */
        void reset() {
            hide();
            first_setup = true;
        }
};

#endif

/**
    @file Force_Effect_Panel.h
    @class Force_Effect_Panel
    @brief   Contains slider input fields for force effects: spring gain and center, damper gain, and force control.
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


#pragma once


#include <k20_libraries.h>
#include "Physics/ConstantForce.h"
#include "Physics/Spring.h"
#include "Physics/Damping.h"
#include "Physics/Motion.h"
#include <iriscontrols4.h>


class Force_Effect_Panel {

    ConstantForce constant_force;
    SpringEffect spring_effect;
    DampingEffect damping_effect;
    Derivative speed{0.02};

    // Actuator Object
    Actuator * motor;

    // GUI_Page to handle displaying/hiding elements in panel
    GUI_Page * panel_elements;

    // Sum of force effect values
    int32_t force_value = 0;

    // Label elements for spring, spring gain, and spring center
    FlexLabel spring_label, spring_gain_label, spring_center_label;

    // Slider elements for spring gain and spring center
    FlexSlider spring_gain, spring_center;

    // Label elements for damper and damper gain
    FlexLabel damper_label, damper_gain_label;

    // Slider element for damper gain
    FlexSlider damper_gain;

    // Label and slider element for constant force
    FlexLabel cforce_label;
    FlexSlider cforce_slider;

    // Button to trigger setting force effects in motor
    FlexButton update_btn;


    public:

        /** @brief Initializes all flex elements in the force effect panel and adds them to a new local GUI_Page object */
        void add(Actuator * _motor, uint8_t y_anchor, uint8_t x_anchor){
            panel_elements = new GUI_Page();
            motor = _motor;
            init(y_anchor, x_anchor);
        }

        /** @brief Initializes all flex elements in the force effect panel and adds them to the specified GUI_Page object argument  */
        void add(GUI_Page * _panel_elements, Actuator * _motor, uint8_t y_anchor, uint8_t x_anchor){
            panel_elements = _panel_elements;
            motor = _motor;
            init(y_anchor, x_anchor);
        }


        /** @brief Initializes all label and slider elements in GUI view */
        void init(uint8_t y_anchor, uint8_t x_anchor){

            // Init GUI_Page object
            panel_elements->add();
            
            // Add spring elements
            spring_label.add(panel_elements, "<p_style=\"font-size:14px;\">Spring</p>", y_anchor, x_anchor, 1, 4);
            spring_gain_label.add(panel_elements, "gain:", y_anchor, x_anchor + 4, 1, 3);
            spring_center_label.add(panel_elements, "center:", y_anchor + 1, x_anchor + 4, 1, 3);
            spring_gain.add(panel_elements, "", y_anchor, x_anchor + 7, 1, 12, 0, 100, 0, 1, FlexData::ALLOW_INPUT);
            spring_center.add(panel_elements, "", y_anchor + 1, x_anchor + 7, 1, 12, 0, 150, 0, 1, FlexData::ALLOW_INPUT);

            // Add damper elements
            damper_label.add(panel_elements, "<p_style=\"font-size:14px;\">Damper</p>", y_anchor + 3, x_anchor, 1, 4);
            damper_gain_label.add(panel_elements, "gain:", y_anchor + 3, x_anchor + 4, 1, 3);
            damper_gain.add(panel_elements, "", y_anchor + 3, x_anchor + 7, 1, 12, 0, 100, 0, 1, FlexData::ALLOW_INPUT);

            // Add constant force elements
            cforce_label.add(panel_elements, "<p_style=\"font-size:14px;\">Constant Force</p>", y_anchor + 5, x_anchor, 1, 6);
            cforce_slider.add(panel_elements, "", y_anchor + 5, x_anchor + 7, 1, 12, -2000, 2000, 0, 1, FlexData::ALLOW_INPUT);

            // Add update button
            update_btn.add(panel_elements, "Update", -1, y_anchor + 5, x_anchor + 19, 1, 5);
        }


        /** @brief Updates the Actuator object's force with the sum of the force effect objects */
        int32_t run(){

            // Update spring effect, speed, and damping effect object values when the actuator object has new data
            if(motor->new_data()){

                // Update spring effect object with actuator position in millimeters
                spring_effect.update(motor->get_position_um() / 1000.);

                // Update speed object with actuator position in millimeters
                speed.update(motor->get_position_um() / 1000.);

                // Update damping effect object with speed
                damping_effect.update(speed.get());
            }
            
            // Get sum of force effect object values
            force_value = 0;
            force_value += spring_effect.getForce();
            force_value += cforce_slider.get(); //constant_force.getForce();
            force_value += damping_effect.getForce();
            
            // Return sum of force effect values
            return force_value;
            
        }

        
        /** @brief Updates the force effect objects with the force effect slider values */
        void update_objects(){

            if(update_btn.pressed()){

                // Update constant force effect object with slider value
                constant_force.update(cforce_slider.get());

                // Adjust spring effect object with negative spring gain slider value
                spring_effect.adjustK(-1 * spring_gain.get());

                // Update spring effect center with spring center slider value
                spring_effect.moveCenter(spring_center.get());

                // Adjust damping effect object with negative damper gain slider value
                damping_effect.adjustK(-1 * damper_gain.get());
            }
        }


        /** @brief Hides all force effect elements in GUI view */
        void hide(){
            panel_elements->hide();   
        }
        

        /** @brief Shows all force effect elements in GUI view */
        void show(){
            panel_elements->show();      
        }

};

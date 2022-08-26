/**
   @file Gain_Panel.h
   @class Gain_Panel
   @brief interface for updating each the motor's PID controller gains and its saturation.
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

#include <iriscontrols4.h>
#include "client/device_applications/actuator.h" 


class Gain_Panel {

    // GUI_Page object handles hiding/displaying all panel flex elements
    GUI_Page * panel_elements;

    // Actuator object used to update motor PID controller gain values
    Actuator * motor;

    // Label elements for the pgain, igain, and dgain input fields
    FlexLabel pgain_label, igain_label, dgain_label;

    // Data elements for the pgain, igain, and dgain input fields
    FlexData pgain, igain, dgain;

    // Button element for updating gain values in motor
    FlexButton update_btn;

    public:

        /** @brief Initializes all panel flex elements and adds them to a new local GUI_Page */
        void add(Actuator * _motor, uint8_t y_anchor, uint8_t x_anchor){
            panel_elements = new GUI_Page();
            motor = _motor;
            init(y_anchor, x_anchor);
        }

        /** @brief Initializes all panel flex elements and adds them to the GUI_Page argument specified. */
        void add(GUI_Page * _panel_elements, Actuator * _motor, uint8_t y_anchor, uint8_t x_anchor){
            panel_elements = _panel_elements;
            motor = _motor;
            init(y_anchor, x_anchor);
        }
        

        /** @brief Initializes the label and data elements for each gain in the GUI view */
        void init(uint8_t y_anchor, uint8_t x_anchor){

            // Init GUI_Page object
           panel_elements->add();
            
            // Add FlexLabels for pgain, igain, dgain
            pgain_label.add(panel_elements, "pgain:", y_anchor, x_anchor, 1, 4);
            igain_label.add(panel_elements, "igain:", y_anchor + 1, x_anchor, 1, 4);
            dgain_label.add(panel_elements, "dgain:", y_anchor + 2, x_anchor, 1, 4);

            // Add FlexData input fields for pgain, igain, dgain
            pgain.add(panel_elements, "", y_anchor, x_anchor + 6, 1, 5, 200, 1, FlexData::ALLOW_INPUT + FlexData::FRAME + FlexData::DIGITS_7 + FlexData::VALUE_ALIGN_LEFT);
            igain.add(panel_elements, "", y_anchor + 1, x_anchor + 6, 1, 5, 0, 1, FlexData::ALLOW_INPUT + FlexData::FRAME + FlexData::DIGITS_7 + FlexData::VALUE_ALIGN_LEFT);
            dgain.add(panel_elements, "", y_anchor + 2, x_anchor + 6, 1, 5, 0, 1, FlexData::ALLOW_INPUT + FlexData::FRAME + FlexData::DIGITS_7 + FlexData::VALUE_ALIGN_LEFT);

            // Add update button
           update_btn.add(panel_elements, "Update", -1, y_anchor + 2, x_anchor + 19, 1, 5);

        }

        /** @brief Updates the motor's pgain, igain, and dgain using values in the input field values */
        void run(){

            if(update_btn.pressed()){
                motor->tune_position_controller((uint16_t) pgain.get(), (uint16_t) igain.get(), (uint16_t) dgain.get(), 5000);
            }    
        }


        /**
         * @brief Hides all gain panel elements in GUI view
        */
        void hide(){
            panel_elements->hide();
        }
        


        /**
         * @brief Shows all gain panel elements in GUI view
        */
        void show(){
            (*panel_elements).show();
        }
        

};

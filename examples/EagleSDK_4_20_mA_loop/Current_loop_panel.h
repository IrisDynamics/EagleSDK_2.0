/** 
    @file Current_loop_panel.h
    @author Rebecca McWilliam <rmcwilliam@irisdynamics.com>
    @brief GUI for display of current loop input and outputs as well as configuration options.
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

#include <EEPROM.h>
#include "Motor_Plot_Panel.h"

//Defined values based on hardware setup
#define CURRENT_OUT_MIN 3300
#define CURRENT_OUT_MAX 21500
#define TOTAL_CURRENT_RANGE  (CURRENT_OUT_MAX - CURRENT_OUT_MIN)
#define USEABLE_CURRENT_RANGE 16000
#define PWM_RESOLUTION 4096
#define USEABLE_PWM_RANGE (PWM_RESOLUTION*USEABLE_CURRENT_RANGE/TOTAL_CURRENT_RANGE)
#define PWM_MIN_OFFSET (PWM_RESOLUTION*(4000-CURRENT_OUT_MIN)/TOTAL_CURRENT_RANGE)
#define ADC_TO_uA ((3300000/4096)/133.)

#define EEPROM_VERSION 101

class CurrentLoopPanel {
    public:

        FlexData motor_position_display, input_current_display, output_pwm_display, target_force_display, ctrl_state_display;
        Motor_Plot motor_plot;
        FlexButton save_btn, sleep_btn;
        FlexSlider force_gain_slider, max_position_slider ;
        FlexLabel panel_label;
        int32_t max_position, force_gain;
        uint8_t control_type;
        Actuator& motor;
        int32_t& ctrl_current;
        int32_t& target_force;
        int & out_pwm;
        int & control_state;
        const char * panel_name;
        int anchor_row, anchor_col;

        CurrentLoopPanel(Actuator& _motor, int32_t& _ctrl_current, int32_t& _target_force, int& _out_pwm, int& _control_state, const char* _panel_name, int _anchor_col, int _anchor_row):
            motor(_motor),
            ctrl_current(_ctrl_current),
            target_force(_target_force),
            out_pwm(_out_pwm),
            control_state(_control_state),
            panel_name(_panel_name),
            anchor_row(_anchor_row),
            anchor_col(_anchor_col)
        {}

        void setup() {

            motor_plot.add(&motor, panel_name, anchor_row, anchor_col, 10, 20);
            input_current_display    .add("Ctrl Current  ", anchor_row + 16, anchor_col, 1, 15, 0, 1, "*mu*A", FlexData::VALUE_ALIGN_LEFT + FlexData::UNITS);
            output_pwm_display       .add("  PWM Output  ", anchor_row + 18, anchor_col, 1, 15, 0, 1, "", FlexData::VALUE_ALIGN_LEFT + FlexData::UNITS);
            target_force_display     .add("Force Target  ", anchor_row + 20, anchor_col, 1, 15, 0, 1, "", FlexData::VALUE_ALIGN_LEFT + FlexData::UNITS);
            ctrl_state_display       .add("Control State ", anchor_row + 22, anchor_col, 1, 15, 0, 1, "", FlexData::VALUE_ALIGN_LEFT + FlexData::UNITS);

            max_position_slider      .add("Max Position", anchor_row + 26, anchor_col, 1, 15, 0, 350000, max_position, 1, FlexSlider::ALLOW_INPUT);
            force_gain_slider        .add("  Force Gain", anchor_row + 28, anchor_col, 1, 15, 0, 65535, force_gain, 1, FlexSlider::ALLOW_INPUT);
            save_btn                 .add("Save Config", -1, anchor_row + 30, anchor_col, 2, 5);
            sleep_btn                .add("Sleep Motor", 0, anchor_row + 30, anchor_col + 6, 2, 5);
        }

        /*
            @brief update GUI elements and handle configuration saving
        */
        void run() {
            motor_plot.run();

            input_current_display.update(ctrl_current);
            output_pwm_display.update(out_pwm);

            if (save_btn.pressed()) {
                int j = motor.channel_number();
                EEPROM.write((0 + j * 10), (uint8_t) EEPROM_VERSION);
                EEPROM.write((1 + j * 10), (uint8_t)max_position_slider.get());
                EEPROM.write((2 + j * 10), (uint8_t)(max_position_slider.get() >> 8));
                EEPROM.write((3 + j * 10), (uint8_t)(max_position_slider.get() >> 16));
                EEPROM.write((4 + j * 10), (uint8_t)(max_position_slider.get() >> 24));
                EEPROM.write((5 + j * 10), (uint8_t)force_gain_slider.get());
                EEPROM.write((6 + j * 10), (uint8_t)(force_gain_slider.get() >> 8));
                EEPROM.write((7 + j * 10), (uint8_t)(force_gain_slider.get() >> 16));
                EEPROM.write((8 + j * 10), (uint8_t)(force_gain_slider.get() >> 24));
                max_position = EEPROM.read(1 + j * 10) + (EEPROM.read(2 + j * 10) << 8) + (EEPROM.read(3 + j * 10) << 16) + (EEPROM.read(4 + j * 10) << 24);
                force_gain = EEPROM.read(5 + j * 10) + (EEPROM.read(6 + j * 10) << 8) + (EEPROM.read(7 + j * 10) << 16) + (EEPROM.read(8 + j * 10) << 24);
            }
            target_force_display.update(target_force);
            ctrl_state_display.update(control_state);

            if (sleep_btn.toggled()) {
                if (sleep_btn.get()) {
                    motor.set_mode(Actuator::SleepMode);
                    control_state = 0;
                }
                else motor.set_mode(Actuator::ForceMode);
            }

        }
};

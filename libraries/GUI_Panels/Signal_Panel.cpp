/**
   @file Signal_Panel.h
   @brief A GUI interface for the Signals library
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


#include "Signal_Panel.h"


/**
 * @brief Function initializes all flex elements in the signal panel and adds them to a new GUI_Page object
*/
void Signal_Panel::add(int32_t* _init_value, uint8_t _y_anchor, uint8_t  _x_anchor){
	init_value = _init_value;
	x_anchor = _x_anchor;
	y_anchor = _y_anchor;
	setup();
}


/**
 * @brief Function initializes all flex elements in the signal panel and adds them to the GUI_Page object specified
*/
void Signal_Panel::add(GUI_Page * _panel_elements, int32_t * _init_value, uint8_t _y_anchor, uint8_t  _x_anchor){
	panel_elements = _panel_elements;
	init_value = _init_value;
	x_anchor = _x_anchor;
	y_anchor = _y_anchor;
	setup();
}



/**
 * @brief Initializes all signal input elements and signal GUI_Pages with the elements required for each signal. After first initializing, only the "Select Signal" label and the slider are displayed.
*/
void Signal_Panel::setup() {

	//Init values
	target_value = 0;
	signal_paused = false;
	signal_type = None;

	// Init GUI_Page
	panel_elements->add();
	// Initialize update/start signal button
	start_signal_btn.add(panel_elements, "Start Signal", -1, y_anchor, x_anchor + 5, 2, 4);

	// Initialize pause button
	pause_signal_btn.add(panel_elements, "Pause Signal", -1, y_anchor, x_anchor, 2, 4);
	// Add slider to selet signal type
	signal_slider.add(panel_elements, "      None", y_anchor+3, x_anchor, 1, 15, 0, 4, 0, 1, FlexData::ALLOW_INPUT);
	last_slider_value = 0;
	// Initialize and hide the three input fields
	input1.add(panel_elements, "target(*mu*m)", y_anchor + 5, x_anchor, 1, 8, 0, 1, FlexData::ALLOW_INPUT + FlexData::FRAME + FlexData::DIGITS_7);
	input2.add(panel_elements, "period(ms)", y_anchor + 7, x_anchor, 1, 8, 0, 1, FlexData::ALLOW_INPUT + FlexData::FRAME + FlexData::DIGITS_7);
	input3.add(panel_elements, "period(ms)", y_anchor + 9, x_anchor, 1, 8, 0, 1, FlexData::ALLOW_INPUT + FlexData::FRAME + FlexData::DIGITS_7);

	update_panel_fields(None);
}


/**
 * @brief Initializes the specified signal if the "start signal" button is pressed. Continues to return values for this signal until another signal is specified.
*/
void Signal_Panel::run() {

	// If slider value changed, update displayed panel fields
	if(slider_change()) update_panel_fields(signal_slider.get());

	// If pause button was pressed, put motor into sleep mode
	if( pause_signal_btn.pressed() ){
		pause();
	}

	// If start button is pressed, initialize signal with the parameters specified in input fields
	if (start_signal_btn.pressed()) {
		signal_type = signal_slider.get();
			switch (signal_type) {
			case None:
				break;
			case Ramp:
				// Initialize ramp signal
				ramp_signal.init(*init_value, input1.get(), input2.get());
				break;
			case Square:
				// Initialize square signal
				square_wave.init(*init_value, input1.get(), input2.get(), input3.get());
				break;
			case Triangle:
				// Initialize triangle signal
				triangle_wave.init(*init_value, input1.get(), input2.get(), input3.get());

				break;
			case Sine:
				// Initialize sine wave signal
				sine_wave.init(*init_value, input1.get(), input2.get(), input3.get());
				break;
			}
		}
}


/**
 * @brief Returns true if the panel slider has been updated sine the last time this function has been called, otherwise false.
*/
bool Signal_Panel::slider_change() {
	// Return value
	bool slider_change = false;
	// Check if slider value has changed
	if (last_slider_value != signal_slider.get()) {
		// Update return value
		slider_change = true;
		// Update last slider value
		last_slider_value = signal_slider.get();
	}
	return slider_change;
}


/**
 * @brief Updates the panel's displayed input fields to suit the signal type parameter specified.
 */
void Signal_Panel::update_panel_fields(int signal_type) {
	clear_inputs();
	
	switch (signal_type) {
	case None:
		input1.hide();
		input2.hide();
		input3.hide();
		start_signal_btn.hide();
		signal_slider.rename("      None");

		break;
	case Ramp:
		input1.show();
		input2.show();
		input3.hide();
		input1.rename("target(*mu*m)");
		input2.rename("period(ms)");
		start_signal_btn.show();
		signal_slider.rename("      Ramp");
		break;
	case Square:
		input1.show();
		input2.show();
		input3.show();
		start_signal_btn.show();
		input1.rename("   max(*mu*m)");
		input2.rename("   min(*mu*m)");
		signal_slider.rename("    Square");
		break;
	case Triangle:
		input1.show();
		input2.show();
		input3.show();
		start_signal_btn.show();
		input1.rename("   max(*mu*m)");
		input2.rename("   min(*mu*m)");
		signal_slider.rename("  Triangle");
		break;
	case Sine:
		input1.show();
		input2.show();
		input3.show();
		start_signal_btn.show();
		input1.rename("   amp(*mu*m)");
		input2.rename("offset(*mu*m)");
		signal_slider.rename("      Sine"); 
		break;
	}
}


/**
 * @brief Returns the target value.
 */
int32_t Signal_Panel::get_target_value() {
	return target_value;
}


/**
 * @brief Generates and returns the next value in the specified signal. If none, the initial value is returned. 
 */
int32_t Signal_Panel::generate() {
	// Get next target_position value by calling the signal run function
	switch (signal_type) {
	case None:
		target_value = *init_value;
		break;
	case Ramp:
		target_value = ramp_signal.run();
		break;
	case Square:
		target_value = square_wave.run();
		break;
	case Triangle:
		target_value = triangle_wave.run();
		break;
	case Sine:
		target_value = sine_wave.run();
		break;
	}

	return target_value;
}


/**
 * @brief Stops the panel from generating new signal values.
*/
void Signal_Panel::pause() {
	signal_type = None;
}


/**
 * @brief Clears data from input field elements
*/
void Signal_Panel::clear_inputs() {
	input1.update(0);
	input2.update(0);
	input3.update(0);
}


/**
* @brief Hides all signal panel elements
*/
void Signal_Panel::hide() {
	panel_elements->hide();
}


/**
 * @brief Shows the slider and "Select signal" label elements
*/
void Signal_Panel::show() {
	panel_elements->show();
}

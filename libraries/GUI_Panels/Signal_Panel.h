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

#pragma once

#include "client/device_applications/actuator.h"
#include "Ramp_Signal.h"
#include "Square_Wave_Signal.h"
#include "Triangle_Wave_Signal.h"
#include "Sine_Wave_Signal.h"
#include <iriscontrols4.h>


/*
 * enum specifies a signal type: 0-None, 1-Ramp, 2-Square wave, 3-Triangle wave, 4-Sine wave
*/
enum SignalType {
	None = 0,
	Ramp = 1,
	Square = 2,
	Triangle = 3,
	Sine = 4
};



/**
   @file Signal_Panel.h
   @class Signal_Panel
   @brief Interface for generating signals. A slider can be used to display input fields for either a ramp, square wave, triangle wave, sine wave, or no signal.
   A start button can be pressed to generate the specified signal's values, and a pause button can be used to stop generating these values.
*/
class Signal_Panel {

	int32_t target_value;							// value to be continuously updated with generated signal values

	// Signal objects for generating signal values
	RampSignal ramp_signal;
	SquareWave square_wave;
	TriangleWave triangle_wave;
	SineWave sine_wave;

    GUI_Page * panel_elements;						// GUI_Page object for showing/hiding panel elements

	FlexSlider signal_slider;						// Slider whose value determines the value of signal_type: 0-None, 1-Ramp, 2-Square Wave, 3-Triangle Wave, 4-Sine Wave
	FlexLabel signal_label;							// Signal label
	FlexData input1, input2, input3; 				// Input fields for signal parameters
	FlexButton start_signal_btn, pause_signal_btn; 	// Start and pause signal buttons

	uint8_t last_slider_value;						// Last slider value, used to determine when the slider has been updated by user

    int32_t * init_value;							// Address of value used for initializing signals
    
    uint8_t y_anchor;								// Panel y anchor
    uint8_t x_anchor;								// Panel x anchor

	bool signal_paused;								// Boolean value indicating whether the signal is running or paused.



public:

	int signal_type;		// Value represents a signal type: 0-None, 1-Ramp, 2-Square Wave, 3-Triangle Wave, 4-Sine Wave
	void add(int32_t* _init_value, uint8_t _y_anchor, uint8_t  _x_anchor);
	void add(GUI_Page * _panel_elements, int32_t* _init_value, uint8_t _y_anchor, uint8_t  _x_anchor);
	void setup();
	void run();				// Updates displayed input fields and handles button clicks
	bool slider_change();
	void update_panel_fields(int signal_type);
	int32_t get_target_value();
	int32_t generate();		// Returns the generated signal value (should be called more frequently than the GUI update period to generate enough values for a smooth signal)
	void pause();
	void clear_inputs();
	void hide();
	void show();

};



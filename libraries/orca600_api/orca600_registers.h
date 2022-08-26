/**
 * @file orca600_registers.h
 *
 *  Created on: Jan. 24, 2022
 *      Author: sjeffery
	
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

#ifndef ORCA600_REGISTERS_H_
#define ORCA600_REGISTERS_H_

#include "types.h"


/**
 * @class CONTROL_REG
 * @brief Base class for a control register.
 *
 * Only defines virtual versions of read and write functions.
 * If the helper functions for control registers (i.e. set_flag) are to be used, these functions must be implemented.
 */
class CONTROL_REG {
public:
	virtual void write(u16 address, u16 value);

	virtual u16 read(u16 address);
};


 /**
  *  @class CONTROL_REG_0
  *  @brief Control Register 0.
  */
class CONTROL_REG_0 : public CONTROL_REG {
public:

	static const int address = CTRL_REG_0;

	typedef enum {
		reset_flag						= 1 << 0,
		clear_errors_flag				= 1 << 1,
		position_zero_flag				= 1 << 2
	} control_register_0_t;

};


/**
 *  @class CONTROL_REG_1
 *  @brief Control Register 1 contains flags for starting calibration routines.
 */
class CONTROL_REG_1 : public CONTROL_REG {
public:

	static const int address = CTRL_REG_1;

	typedef enum {
		hall_gain_set_flag					= 1 << 3,
		current_gain_set_flag				= 1 << 4,
		hall_zero_flag						= 1 << 5,
		current_zero_flag					= 1 << 6,
		stator_calibration_flag				= 1 << 7,
		shaft_calibration_flag				= 1 << 8,
		force_calibration_flag				= 1 << 9,
		position_controller_gain_set_flag	= 1 << 10,
		current_controller_gain_set_flag	= 1 << 11
	} control_register_1_t;

};


/**
 *  @class CONTROL_REG_2
 *  @brief Control Register 2 contains flags for saving data to nonvolatile memory.
 */
class CONTROL_REG_2 : public CONTROL_REG {
public:

	static const int address = CTRL_REG_2;

	typedef enum {
		parameter_save_flag				= 1 << 0,
		stator_calibration_save_flag 	= 1 << 2,
		shaft_calibration_save_flag 	= 1 << 3,
		force_calibration_save_flag 	= 1 << 4,
		controls_save_flag 				= 1 << 5,
		usr_opt_save_flag 				= 1 << 6,
		motion_config_save_flag 		= 1 << 7
	} control_register_2_t;

};


/**
 *  @class CONTROL_REG_3
 *  @brief Control Register 3 controls the transitions between Orca modes.
 */
class CONTROL_REG_3 : public CONTROL_REG {
public:

	static const int address  = CTRL_REG_3;
	static const int mode_reg = MODE_OF_OPERATION;

	typedef enum {
		sleep_sid				= 1,
		force_control_sid		= 2,
		position_control_sid	= 3,
		current_tuning_sid		= 4,
		kinematic_control_sid	= 5
	} control_register_3_t;

	/**
	 * @brief Write a state id to control register 3, commanding the Orca to change to the selected mode.
	 */
	void set_mode (control_register_3_t sid) {
		write(address, sid);
	}

	/**
	 * @brief Return the value stored in control register 3, i.e. what mode the Orca is in.
	 */
	u16 get_mode() {
		return read(mode_reg);
	}
};

/**
 * @class ERROR_REG_0
 * @brief Error Register 0 contains the Orcas error flags.
 */
class ERROR_REG_0 {
public:

	static const int address_active_errors		= ERROR_0;
	static const int address_latched_errors		= ERROR_1;

	typedef enum {
		configuration_invalid		= 1 << 0,
		force_control_clipping		= 1 << 5,
		max_temp_exceeded			= 1 << 6,
		max_force_exceeded			= 1 << 7,
		max_power_exceeded			= 1 << 8,
		shaft_image_failed			= 1 << 9,
		voltage_invalid				= 1 << 10,
		comms_timeout				= 1 << 11
	} orca_error_t;


	static const int configuration_errors		= configuration_invalid;


	/* When a calibration error is active, PWM output is disabled. */
	static const int calibration_error_mask		= max_temp_exceeded | voltage_invalid;

	/* Force errors cause the force controller to stop producing outputs. */
	static const int force_error_mask			= configuration_errors | max_temp_exceeded | max_power_exceeded | shaft_image_failed | voltage_invalid;

	/* Position errors cause the position controller to stop producing outputs. */
	static const int position_error_mask		= configuration_errors | max_temp_exceeded | max_power_exceeded | shaft_image_failed | voltage_invalid;

};


#endif /* ORCA600_REGISTERS_H_ */

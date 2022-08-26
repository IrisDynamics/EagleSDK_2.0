/**
* @file orca600_memory_map.h
*
* @brief Addresses of Orca600 registers
	
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

/* This file generated 7/7/2022 3:50:20 PM by memory_map_generator.xlsm */

/* NOTE: Registers of width 2 or more that will be accessed by 32 bit pointers MUST begin on an even array index. */

#ifndef ORCA600_MEMORY_MAP_H_
#define ORCA600_MEMORY_MAP_H_

#define CTRL_REG_0                    0         // CTRL_REG_SECTION     | Width: 1    | Control Register 1
#define CTRL_REG_1                    1         // CTRL_REG_SECTION     | Width: 1    | Control Register 2
#define CTRL_REG_2                    2         // CTRL_REG_SECTION     | Width: 1    | Control Register 3
#define CTRL_REG_3                    3         // CTRL_REG_SECTION     | Width: 1    | Control Register 4
#define CTRL_REG_4                    4         // CTRL_REG_SECTION     | Width: 1    | Control Register 5
#define CTRL_REG_5                    5         // CTRL_REG_SECTION     | Width: 1    | Control Register 6
#define CTRL_REG_6                    6         // CTRL_REG_SECTION     | Width: 1    | Control Register 7
#define CTRL_REG_7                    7         // CTRL_REG_SECTION     | Width: 1    | Control Register 8
#define GUI_PERIOD_CMD                8         // CTRL_REG_SECTION     | Width: 1    | Commanded period between IrisControls GUI frames in milliseconds.
#define KIN_SW_TRIGGER                9         // CTRL_REG_SECTION     | Width: 1    | Software trigger for intiating kinematic movements over Modbus.
/***********************************************************
 * Non-contiguous addresses. 18 free registers. 10 - 27
 ***********************************************************/
#define FORCE_CMD                     28        // CTRL_REG_SECTION     | Width: 1    | Commanded actuator output force in millinewtons. Lower 2 bytes.
#define FORCE_CMD_H                   29        // CTRL_REG_SECTION     | Width: 1    | Commanded actuator output force in millinewtons. Upper 2 bytes.
#define POS_CMD                       30        // CTRL_REG_SECTION     | Width: 1    | Commanded actuator position in micrometers. Lower 2 bytes.
#define POS_CMD_H                     31        // CTRL_REG_SECTION     | Width: 1    | Commanded actuator position in micrometers. Upper 2 bytes.
/***********************************************************
 * Non-contiguous addresses. 1 free registers. 32 - 32
 ***********************************************************/
#define STATOR_CAL_VERSION            33        // STATOR_CAL_SECTION   | Width: 1    | Stator calibration version.
#define BS_GAIN_CMD                   34        // STATOR_CAL_SECTION   | Width: 1    | Hall sensor analog circuit gain.
#define CS_GAIN_CMD                   35        // STATOR_CAL_SECTION   | Width: 1    | Current sensor analog circuit gain.
#define HALL_0_ZERO                   36        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 0.
#define HALL_1_ZERO                   37        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 1.
#define HALL_2_ZERO                   38        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 2.
#define HALL_3_ZERO                   39        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 3.
#define HALL_4_ZERO                   40        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 4.
#define HALL_5_ZERO                   41        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 5.
#define HALL_6_ZERO                   42        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 6.
#define HALL_7_ZERO                   43        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for Hall sensor 7.
#define CURRENT_0_ZERO                44        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 0.
#define CURRENT_1_ZERO                45        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 1.
#define CURRENT_2_ZERO                46        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 2.
#define CURRENT_3_ZERO                47        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 3.
#define CURRENT_4_ZERO                48        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 4.
#define CURRENT_5_ZERO                49        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 5.
#define CURRENT_6_ZERO                50        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 6.
#define CURRENT_7_ZERO                51        // STATOR_CAL_SECTION   | Width: 1    | Saved zero value for current sensor 7.
#define CS_TRANSFER_FN                52        // STATOR_CAL_SECTION   | Width: 1    | -
#define PHASE_0_RESISTANCE            53        // STATOR_CAL_SECTION   | Width: 1    | Total resistance of motor phase 0.
#define PHASE_1_RESISTANCE            54        // STATOR_CAL_SECTION   | Width: 1    | Total resistance of motor phase 1.
#define PHASE_2_RESISTANCE            55        // STATOR_CAL_SECTION   | Width: 1    | Total resistance of motor phase 2.
#define PHASE_3_RESISTANCE            56        // STATOR_CAL_SECTION   | Width: 1    | Total resistance of motor phase 3.
#define HALL_0_A_INT                  57        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_1_A_INT                  58        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_2_A_INT                  59        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_3_A_INT                  60        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_4_A_INT                  61        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_5_A_INT                  62        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_6_A_INT                  63        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_7_A_INT                  64        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_0_B_INT                  65        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_1_B_INT                  66        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_2_B_INT                  67        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_3_B_INT                  68        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_4_B_INT                  69        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_5_B_INT                  70        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_6_B_INT                  71        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_7_B_INT                  72        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_0_C_INT                  73        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_1_C_INT                  74        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_2_C_INT                  75        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_3_C_INT                  76        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_4_C_INT                  77        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_5_C_INT                  78        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_6_C_INT                  79        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_7_C_INT                  80        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_0_D_INT                  81        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_1_D_INT                  82        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_2_D_INT                  83        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_3_D_INT                  84        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_4_D_INT                  85        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_5_D_INT                  86        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_6_D_INT                  87        // STATOR_CAL_SECTION   | Width: 1    | -
#define HALL_7_D_INT                  88        // STATOR_CAL_SECTION   | Width: 1    | -
/***********************************************************
 * Non-contiguous addresses. 7 free registers. 89 - 95
 ***********************************************************/
#define SHAFT_CAL_VERSION             96        // SHAFT_CAL_SECTION    | Width: 1    | Shaft calibration version.
#define HALL_0_MAX                    97        // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 0.
#define HALL_1_MAX                    98        // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 1.
#define HALL_2_MAX                    99        // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 2.
#define HALL_3_MAX                    100       // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 3.
#define HALL_4_MAX                    101       // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 4.
#define HALL_5_MAX                    102       // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 5.
#define HALL_6_MAX                    103       // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 6.
#define HALL_7_MAX                    104       // SHAFT_CAL_SECTION    | Width: 1    | Maximum value read by Hall sensor 7.
#define SHAFT_C45                     105       // SHAFT_CAL_SECTION    | Width: 1    | -
#define SHAFT_C90                     106       // SHAFT_CAL_SECTION    | Width: 1    | -
/***********************************************************
 * Non-contiguous addresses. 5 free registers. 107 - 111
 ***********************************************************/
#define FORCE_CAL_VERSION             112       // FORCE_CAL_SECTION    | Width: 1    | Force calibration version.
#define PHASE_A_ALIGNMENT             113       // FORCE_CAL_SECTION    | Width: 1    | -
#define PHASE_B_ALIGNMENT             114       // FORCE_CAL_SECTION    | Width: 1    | -
#define PHASE_C_ALIGNMENT             115       // FORCE_CAL_SECTION    | Width: 1    | -
#define PHASE_D_ALIGNMENT             116       // FORCE_CAL_SECTION    | Width: 1    | -
#define FORCE_F30                     117       // FORCE_CAL_SECTION    | Width: 1    | -
#define FORCE_F60                     118       // FORCE_CAL_SECTION    | Width: 1    | -
#define FORCE_F90                     119       // FORCE_CAL_SECTION    | Width: 1    | -
/***********************************************************
 * Non-contiguous addresses. 8 free registers. 120 - 127
 ***********************************************************/
#define TUNING_VERSION                128       // TUNING_SECTION       | Width: 1    | Tuning calibration version.
#define CC_PGAIN                      129       // TUNING_SECTION       | Width: 1    | Current controller proportional gain.
#define CC_IGAIN                      130       // TUNING_SECTION       | Width: 1    | Current controller integral gain.
#define CC_FGAIN                      131       // TUNING_SECTION       | Width: 1    | Current controller forward gain.
#define CC_MAX_DUTY                   132       // TUNING_SECTION       | Width: 1    | Current controller maximum duty cycle.
#define PC_PGAIN                      133       // TUNING_SECTION       | Width: 1    | Position controller proportional gain.
#define PC_IGAIN                      134       // TUNING_SECTION       | Width: 1    | Position controller integral gain.
#define PC_DVGAIN                     135       // TUNING_SECTION       | Width: 1    | Position controller velocity gain.
#define PC_DEGAIN                     136       // TUNING_SECTION       | Width: 1    | Position controller error derivative gain.
#define PC_FSATU                      137       // TUNING_SECTION       | Width: 1    | Position controller maximum force output. Lower 2 bytes.
#define PC_FSATU_H                    138       // TUNING_SECTION       | Width: 1    | Position controller maximum force output. Upper 2 bytes.
#define USER_MAX_TEMP                 139       // TUNING_SECTION       | Width: 1    | User configurable maximum motor temperature before over temperature error in degrees Celsius.
#define USER_MAX_FORCE                140       // TUNING_SECTION       | Width: 1    | User configurable maximum force output in millinewtons. Lower 2 bytes.
#define USER_MAX_FORCE_H              141       // TUNING_SECTION       | Width: 1    | User configurable maximum force output in millinewtons. Upper 2 bytes.
#define USER_MAX_POWER                142       // TUNING_SECTION       | Width: 1    | User configurable maximum power burn in watts.
#define SAFETY_DGAIN                  143       // TUNING_SECTION       | Width: 1    | Speed damping gain value used when communications are interrupted.
#define PC_PGAIN_LOW_SPEED            144       // TUNING_SECTION       | Width: 1    | Position controller proportional gain to fade to (speed-based gain scheduling) as shaft speed falls below the PC_LOW_SPEED setting
#define PC_IGAIN_LOW_SPEED            145       // TUNING_SECTION       | Width: 1    | Position controller integral gain to fade to  (speed-based gain scheduling) as shaft speed falls below the PC_LOW_SPEED setting
#define PC_DVGAIN_LOW_SPEED           146       // TUNING_SECTION       | Width: 1    | Position controller velocity gain to fade to  (speed-based gain scheduling) as shaft speed falls below the PC_LOW_SPEED setting
#define PC_DEGAIN_LOW_SPEED           147       // TUNING_SECTION       | Width: 1    | Position controller error derivative gain to fade to  (speed-based gain scheduling) as shaft speed falls below the PC_LOW_SPEED setting
#define PC_LOW_SPEED                  148       // TUNING_SECTION       | Width: 1    | Speed (mm per second) at which the position controller gains will have completely faded away from the LOW_SPEED gains. When this is zero, gain scheduling is effectively disabled.
#define PC_GAIN_SCHEDULE_DISABLE      149       // TUNING_SECTION       | Width: 1    | When this register is set to 0, the gain scheduling algorithm for the position controller is enabled and the gains fade between the LOW_SPEED and normal settings according to the shaft speed and the PC_LOW_SPEED register
/***********************************************************
 * Non-contiguous addresses. 10 free registers. 150 - 159
 ***********************************************************/
#define USR_OPT_VERSION               160       // USER_OPTIONS_SECTION | Width: 1    | User options section version.
#define LOG_DATA_SELECTION            161       // USER_OPTIONS_SECTION | Width: 1    | Bitfield indicating which data will be logged periodically.
#define LOG_PERIOD                    162       // USER_OPTIONS_SECTION | Width: 1    | Period between data log entries.
#define USER_COMMS_TIMEOUT            163       // USER_OPTIONS_SECTION | Width: 1    | Time between succesful force or position commands before a communications error occurs. In milliseconds.
/***********************************************************
 * Non-contiguous addresses. 76 free registers. 164 - 239
 ***********************************************************/
#define HALL_0_ADC_FREQ               240       // COUNT_SECTION        | Width: 1    | -
#define HALL_1_ADC_FREQ               241       // COUNT_SECTION        | Width: 1    | -
#define HALL_2_ADC_FREQ               242       // COUNT_SECTION        | Width: 1    | -
#define HALL_3_ADC_FREQ               243       // COUNT_SECTION        | Width: 1    | -
#define HALL_4_ADC_FREQ               244       // COUNT_SECTION        | Width: 1    | -
#define HALL_5_ADC_FREQ               245       // COUNT_SECTION        | Width: 1    | -
#define HALL_6_ADC_FREQ               246       // COUNT_SECTION        | Width: 1    | -
#define HALL_7_ADC_FREQ               247       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_0_ADC_FREQ            248       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_1_ADC_FREQ            249       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_2_ADC_FREQ            250       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_3_ADC_FREQ            251       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_4_ADC_FREQ            252       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_5_ADC_FREQ            253       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_6_ADC_FREQ            254       // COUNT_SECTION        | Width: 1    | -
#define CURRENT_7_ADC_FREQ            255       // COUNT_SECTION        | Width: 1    | -
#define THERM_0_ADC_FREQ              256       // COUNT_SECTION        | Width: 1    | -
#define THERM_1_ADC_FREQ              257       // COUNT_SECTION        | Width: 1    | -
#define THERM_2_ADC_FREQ              258       // COUNT_SECTION        | Width: 1    | -
#define THERM_3_ADC_FREQ              259       // COUNT_SECTION        | Width: 1    | -
#define VDD_ADC_FREQ                  260       // COUNT_SECTION        | Width: 1    | -
#define ZERO_TEN_A_FREQ               261       // COUNT_SECTION        | Width: 1    | -
#define ZERO_TEN_B_FREQ               262       // COUNT_SECTION        | Width: 1    | -
#define UART0_UP_RATE                 263       // COUNT_SECTION        | Width: 1    | Number of bytes transmitted in the last second by UART0.
#define UART1_UP_RATE                 264       // COUNT_SECTION        | Width: 1    | Number of bytes transmitted in the last second by UART1.
#define UART0_DOWN_RATE               265       // COUNT_SECTION        | Width: 1    | Number of bytes received in the last second by UART0.
#define UART1_DOWN_RATE               266       // COUNT_SECTION        | Width: 1    | Number of bytes received in the last second by UART1.
#define GUI_DROPPED_FRAMES            267       // COUNT_SECTION        | Width: 1    | Total number of skipped IrisControls GUI transactions.
#define GUI_DROPPED_FPS               268       // COUNT_SECTION        | Width: 1    | Number of skipped IrisControls GUI transactions in the last second.
#define LOOP_FREQ                     269       // COUNT_SECTION        | Width: 1    | Main loop run frequency in kilohertz.
#define SHAFT_CAL_COUNT               270       // COUNT_SECTION        | Width: 1    | -
#define STATOR_CAL_COUNT              271       // COUNT_SECTION        | Width: 1    | -
#define MOTOR_FRAME_COUNT             272       // COUNT_SECTION        | Width: 1    | Number of complete motor frames in the last second.
#define MB_FREQ                       273       // COUNT_SECTION        | Width: 1    | Number of successful Modbus messages in the last second.
/***********************************************************
 * Non-contiguous addresses. 39 free registers. 274 - 312
 ***********************************************************/
#define GUI_PERIOD                    313       // STATUS_SECTION       | Width: 1    | Period between IrisControls GUI communications in milliseconds.
#define SHAFT_SIGNAL_STR              314       // STATUS_SECTION       | Width: 1    | -
#define BS_GAIN                       315       // STATUS_SECTION       | Width: 1    | Hall sensor analog circuit gain.
#define CS_GAIN                       316       // STATUS_SECTION       | Width: 1    | Current sensor analog circuit gain.
#define MODE_OF_OPERATION             317       // STATUS_SECTION       | Width: 1    | Active mode the actuator is currently running in.
#define CALIBRATION_STATUS            318       // STATUS_SECTION       | Width: 1    | A value other than zero indicates a calibration routine is in process.
/***********************************************************
 * Non-contiguous addresses. 17 free registers. 319 - 335
 ***********************************************************/
#define STATOR_TEMP                   336       // SENSOR_SECTION       | Width: 1    | Temperature of the motor stator in degrees Celsius.
#define DRIVER_TEMP                   337       // SENSOR_SECTION       | Width: 1    | Temperature of the motor driver in degrees Celsius.
#define VDD_FINAL                     338       // SENSOR_SECTION       | Width: 1    | Motor supply voltage in volts.
#define SHAFT_PHASE_FINAL             339       // SENSOR_SECTION       | Width: 1    | -
#define SHAFT_PIXEL                   340       // SENSOR_SECTION       | Width: 1    | -
#define SHAFT_PIXEL_H                 341       // SENSOR_SECTION       | Width: 1    | -
#define SHAFT_POS_UM                  342       // SENSOR_SECTION       | Width: 1    | Shaft absolute position in micrometers. Lower 2 bytes.
#define SHAFT_POSITION_H              343       // SENSOR_SECTION       | Width: 1    | Shaft absolute position in micrometers. Upper 2 bytes.
#define SHAFT_SPEED_MMPS              344       // SENSOR_SECTION       | Width: 1    | Shaft speed in millimeters per second. Lower 2 bytes.
#define SHAFT_SHEED_H                 345       // SENSOR_SECTION       | Width: 1    | Shaft speed in millimeters per second. Upper 2 bytes.
#define SHAFT_ACCEL_MMPSS             346       // SENSOR_SECTION       | Width: 1    | Shaft acceleration in millimeters per second per second. Lower 2 bytes.
#define SHAFT_ACCEL_H                 347       // SENSOR_SECTION       | Width: 1    | Shaft acceleration in millimeters per second per second. Upper 2 bytes.
#define FORCE                         348       // SENSOR_SECTION       | Width: 1    | Sensed actuator output force in millinewtons. Lower 2 bytes.
#define FORCE_H                       349       // SENSOR_SECTION       | Width: 1    | Sensed actuator output force in millinewtons. Upper 2 bytes.
#define POWER                         350       // SENSOR_SECTION       | Width: 1    | Sensed actuator output power in watts.
/***********************************************************
 * Non-contiguous addresses. 49 free registers. 351 - 399
 ***********************************************************/
#define PARAM_VERSION                 400       // PARAM_SECTION        | Width: 1    | Parameter calibration version.
#define MAX_TEMP                      401       // PARAM_SECTION        | Width: 1    | Absolute maximum motor temperature before over temperature error.
#define MIN_VOLTAGE                   402       // PARAM_SECTION        | Width: 1    | Minimum motor voltage in volts before invalid voltage error.
#define MAX_VOLTAGE                   403       // PARAM_SECTION        | Width: 1    | Maximum motor voltage in volts before invalid voltage error.
#define MAX_CURRENT                   404       // PARAM_SECTION        | Width: 1    | Maximum motor current output in milliamps.
#define MAX_POWER                     405       // PARAM_SECTION        | Width: 1    | Maximum motor power burn in watts.
#define SERIAL_NUMBER_LOW             406       // PARAM_SECTION        | Width: 1    | Actuator serial number. Lower 2 bytes.
#define SERIAL_NUMBER_HIGH            407       // PARAM_SECTION        | Width: 1    | Actuator serial number. Upper 2 bytes.
#define MAJOR_VERSION                 408       // PARAM_SECTION        | Width: 1    | Firmware major version.
#define RELEASE_STATE                 409       // PARAM_SECTION        | Width: 1    | Firmware minor version.
#define REVISION_NUMBER               410       // PARAM_SECTION        | Width: 1    | Firmware revision number.
/***********************************************************
 * Non-contiguous addresses. 1 free registers. 411 - 411
 ***********************************************************/
#define SOFTSTART_PERIOD              412       // PARAM_SECTION        | Width: 1    | Period over which to fade position controller gains in milliseconds.
#define CC_MIN_CURRENT                413       // PARAM_SECTION        | Width: 1    | Current controller minimum current output in milliamps.
#define HW_VERSION                    414       // PARAM_SECTION        | Width: 1    | Target hardware version for this firmware.
#define PWM_FREQ                      415       // PARAM_SECTION        | Width: 1    | Frequency of the PWM signals in hertz.
#define ADC_FREQ                      416       // PARAM_SECTION        | Width: 1    |
#define COMMS_TIMEOUT                 417       // PARAM_SECTION        | Width: 1    | Time between succesful force or position commands before a communications error occurs. In milliseconds.
/***********************************************************
 * Non-contiguous addresses. 14 free registers. 418 - 431
 ***********************************************************/
#define ERROR_0                       432       // ERROR_SECTION        | Width: 1    | Currently active error flags. Only reflects error conditions that have not been cleared.
#define ERROR_1                       433       // ERROR_SECTION        | Width: 1    | Latched error flags. Reflects all errors that have occurred since reset.
#define LISTEN_TDRE_ERROR             434       // ERROR_SECTION        | Width: 1    |
#define RX_TDRE_ERROR                 435       // ERROR_SECTION        | Width: 1    |
#define LISTEN_TC_ERROR               436       // ERROR_SECTION        | Width: 1    |
#define RX_TC_ERROR                   437       // ERROR_SECTION        | Width: 1    |
#define TX_RDRF_ERROR                 438       // ERROR_SECTION        | Width: 1    |
#define NO_SHAFT_ERROR                439       // ERROR_SECTION        | Width: 1    |
#define ADC_DATA_COLLISION            440       // ERROR_SECTION        | Width: 1    |
/***********************************************************
 * Non-contiguous addresses. 23 free registers. 441 - 463
 ***********************************************************/
#define DIAG_COUNTER_0                464       // MODBUS_SECTION       | Width: 1    | Return bus message count. Refer to Modbus specification.
#define DIAG_COUNTER_1                465       // MODBUS_SECTION       | Width: 1    | Return bus communication error. Refer to Modbus specification.
#define DIAG_COUNTER_2                466       // MODBUS_SECTION       | Width: 1    | Return server exception error count. Refer to Modbus specification.
#define DIAG_COUNTER_3                467       // MODBUS_SECTION       | Width: 1    | Return server message count. Refer to Modbus specification.
#define DIAG_COUNTER_4                468       // MODBUS_SECTION       | Width: 1    | Return server no response count. Refer to Modbus specification.
#define DIAG_COUNTER_5                469       // MODBUS_SECTION       | Width: 1    | Return server NAK count. Refer to Modbus specification.
#define DIAG_COUNTER_6                470       // MODBUS_SECTION       | Width: 1    | Return server busy count. Refer to Modbus specification.
#define DIAG_COUNTER_7                471       // MODBUS_SECTION       | Width: 1    | Return bus character overrun count. Refer to Modbus specification.
#define DIAG_COUNTER_8                472       // MODBUS_SECTION       | Width: 1    | Rx line error.
#define DIAG_COUNTER_9                473       // MODBUS_SECTION       | Width: 1    | Ignoring state error.
#define DIAG_COUNTER_10               474       // MODBUS_SECTION       | Width: 1    | Unexpected interchar.
#define DIAG_COUNTER_11               475       // MODBUS_SECTION       | Width: 1    | Unexpected interframe.
#define DIAG_COUNTER_12               476       // MODBUS_SECTION       | Width: 1    | Timeout sequence error.
#define DIAG_COUNTER_13               477       // MODBUS_SECTION       | Width: 1    | Unexpected emission.
#define DIAG_COUNTER_14               478       // MODBUS_SECTION       | Width: 1    | Unexpected reception.
#define DIAG_COUNTER_15               479       // MODBUS_SECTION       | Width: 1    | -
#define DIAG_COUNTER_16               480       // MODBUS_SECTION       | Width: 1    | -
#define DIAG_COUNTER_17               481       // MODBUS_SECTION       | Width: 1    | -
#define MODBUS_BAUD                   482       // MODBUS_SECTION       | Width: 1    | Modbus serial baudrate. Lower 2 bytes.
#define MODBUS_BAUD_H                 483       // MODBUS_SECTION       | Width: 1    | Modbus serial baudrate. Upper 2 bytes.
#define MODBUS_DELAY                  484       // MODBUS_SECTION       | Width: 1    | Modbus interframe delay in microseconds.
#define SERVER_ADDRESS                485       // MODBUS_SECTION       | Width: 1    | Modbus server address.
/***********************************************************
 * Non-contiguous addresses. 10 free registers. 486 - 495
 ***********************************************************/
#define MESSAGE_0_SIZE                496       // MODBUS_SECTION       | Width: 1    | Size of last received Modbus message in bytes.
#define MESSAGE_0                     497       // MODBUS_SECTION       | Width: 259  | -
/***********************************************************
 * Non-contiguous addresses. 22 free registers. 756 - 777
 ***********************************************************/
#define KINEMATIC_SECTION_VERSION     778       // KINEMATIC_SECTION    | Width: 1    |
#define KIN_CONFIG                    779       // KINEMATIC_SECTION    | Width: 1    | Kinematic controller configuration.
#define KIN_MOTION_0                  780       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_1                  786       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_2                  792       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_3                  798       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_4                  804       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_5                  810       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_6                  816       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_7                  822       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_8                  828       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_9                  834       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_10                 840       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_11                 846       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_12                 852       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_13                 858       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_14                 864       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_15                 870       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_16                 876       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_17                 882       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_18                 888       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_19                 894       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_20                 900       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_21                 906       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_22                 912       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_23                 918       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_24                 924       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_25                 930       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_26                 936       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_27                 942       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_28                 948       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_29                 954       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_30                 960       // KINEMATIC_SECTION    | Width: 6    |
#define KIN_MOTION_31                 966       // KINEMATIC_SECTION    | Width: 6    |


#define ORCA_REG_SIZE                 972

#define STATOR_CAL_REG_START          33
#define SHAFT_CAL_REG_START           96
#define FORCE_CAL_REG_START           112
#define TUNING_REG_START              128
#define PARAM_REG_START               400
#define USR_OPT_REG_START             160
#define KIN_REG_START                 778

#define STATOR_CAL_REG_SIZE           56
#define SHAFT_CAL_REG_SIZE            11
#define FORCE_CAL_REG_SIZE            8
#define TUNING_REG_SIZE               22
#define PARAM_REG_SIZE                18
#define USR_OPT_REG_SIZE              4
#define KIN_REG_SIZE                  194

#endif

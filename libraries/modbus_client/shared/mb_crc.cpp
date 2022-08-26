/*
 * mb_crc.cpp
 *
 *  Created on: Aug. 3, 2021
 *      Author: Sean
 */

#ifdef __MK20DX256__
#else
#include "mb_crc.h"
constexpr uint8_t ModbusCRC::crc_hi_table[256];
constexpr uint8_t ModbusCRC::crc_lo_table[256];

ModbusCRC mod_crc;
#endif
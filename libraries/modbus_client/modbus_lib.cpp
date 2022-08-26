///here for arduino include

#include "modbus_lib.h"

#ifdef __MK20DX256__
constexpr uint8_t ModbusCRC::crc_hi_table[256];
constexpr uint8_t ModbusCRC::crc_lo_table[256];

uint32_t Transaction::id_assigner = 0;
#endif
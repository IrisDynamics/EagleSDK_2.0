/**
 * @file modbus_k20_config.h
 * @author Kali Erickson <kerickson@irisdynamics.com>
 * @brief  Pre-processor definitions used by the Modbus Client library
 * 
 * 
 * @version 1.0
 * Copyright (C) Iris Dynamics Ltd - All Rights Reserved
 */
#ifdef __MK20DX256__
#ifndef MODBUS_K20_CONFIG_H_
#define MODBUS_K20_CONFIG_H_

#include "kinetis.h"
#include "Arduino.h"


#define BAUD2DIV(baud)  (((F_CPU * 2) + ((baud) >> 1)) / (baud))    
#define BAUD2DIV2(baud) (((F_CPU * 2) + ((baud) >> 1)) / (baud))
#define BAUD2DIV3(baud) (((F_BUS * 2) + ((baud) >> 1)) / (baud))    //F_BUS is 48MHz

//interrupt priorities - CONFIGURE AS NEEDED
#define IRQ_PRIORITY            64     // 0 = highest priority, 255 = lowest
#define PIT_PRIORITY            32
#define ERROR_PRIORITY          16

//interrupt, timers, receiver, and transmitter disabled/enabled states - CONFIGURE AS NEEDED
#define C2_DISABLE        (UART_C2_TE | UART_C2_RE)
#define C2_ENABLE         (UART_C2_TE | UART_C2_RE | UART_C2_RIE)
#define C2_TX_ENABLE      (C2_ENABLE | UART_C2_TIE | UART_C2_TCIE)
#define C2_TDRE_DISABLE   (C2_ENABLE | UART_C2_TCIE)
#define C2_TX_DISABLE     C2_ENABLE

#define C3_EI_ENABLE      (UART_C3_ORIE | UART_C3_NEIE | UART_C3_FEIE)

#define PIT_DISABLE       0
#define PIT_ENABLE        (PIT_TCTRL_TEN | PIT_TCTRL_TIE)
#define PIT_I_DISABLE     PIT_TCTRL_TEN



#endif
#endif

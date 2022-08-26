#ifndef MB_CONFIG_H_
#define MB_CONFIG_H_

//If you are not using the K20, KV31, or Zynq7000 platforms, uncomment ONE of the defines below:
//#define ATMEGA328
//#define WINDOWS
//#define QT_WINDOWS


#if defined(CPU_MKV31F256VLH12) || defined(__MK20DX256__) || defined(ATMEGA328) || defined(IRIS_ZYNQ_7000) || defined(WINDOWS) || defined(QT_WINDOWS)
#else 
#error Must uncomment one of the platform types in mb_config.h
#endif

/// Modbus virtual register adresses - Static - do not adjust ///
#define MB_BAUD_HIGH        65532
#define MB_BAUD_LOW         65533
#define MB_DELAY            65534
#define MB_SERVER_ID        65535

//

#define DEFAULT_INTERFRAME_uS	2000	//2000 
#define DEFAULT_INTERCHAR_uS	16000 	//8000	// 700
#define DEFAULT_TURNAROUND_uS	2000	//2000
#define DEFAULT_RESPONSE_uS    	100000	//750000 - windows		//100000

#define DEFAULT_CONNECTION_PAUSE_uS		750000



//uncomment one of the following buffer size options - MUST CONFIGURE
#ifdef __MK20DX256__
#define NUM_MESSAGES        16// 8  //4  //32  //64
#else
#define NUM_MESSAGES        64  //8  //4  //32  //64
#endif
//uncomment one of the following baud rate options
#define UART_BAUD_RATE      19200  //9600  //1000000  //625000  //500000   //Modbus specified default is 19200bps


#if defined(ATMEGA328)
#include <avr/pgmspace.h>
#define LESS_DATA_MEM   PROGMEM
#define ACCESS_PROGMEM(x)   pgm_read_word(&x)
#else
#define LESS_DATA_MEM
#define ACCESS_PROGMEM(x)   x
#endif

#endif

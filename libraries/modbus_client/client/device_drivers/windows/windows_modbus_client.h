/**
 * @file windows_modbus_client.h
 * @author Kate Colwell <kcolwell@irisdynamics.com>
 *
 * @brief  Virtual device driver for Modbus client serial communication using the Windows API
 *
 * This class extends the virtual ModbusClient base class
 *
 * @version 1.0
 * Copyright (C) Iris Dynamics Ltd - All Rights Reserved
 * trademark stuff
 */

#pragma once 

#include<iostream>
#include <windows.h>
#include <timeapi.h>
#include <vector>
#include <sstream>
#include "modbus_client.h"
#include "transaction.h"

 /**
  * @class windows_ModbusClient
  * @brief Extension of the ModbusClient virtual class that implements functions for the Eagle K20's timers, and interrupts. UART channel specific functions to be
 */

class windows_ModbusClient : public ModbusClient {

protected:

    int channel_number;
    uint32_t cycles_per_us;

public:

    //queue timer stuff 
    HANDLE timerHandle = NULL;
    HANDLE timerQueue = NULL;
    HANDLE timerEvent = NULL;
    int sucCounter = 0;
    int failCounter = 0;
    int callBCounter = 0;
    int isrCounter = 0;
    windows_ModbusClient* wmc;

    //comport stuff
    HANDLE hSerial;     //handle to the serial port 
    DCB dcbSerialParams = { 0 };

    //for messaging
    std::vector <char> sendBuf;
    DWORD      dwRes;
    DWORD      dwCommEvent;
    DWORD      dwStoredFlags;
    OVERLAPPED o;
    DWORD dwEventMask = 0;
        
    windows_ModbusClient(int _channel_number, uint32_t _cycles_per_us) : ModbusClient(_channel_number, _cycles_per_us)
    {
        //get port number from channel param
        std::ostringstream portOsStr;
        portOsStr << "\\\\.\\COM" << _channel_number;
        std::string portStr(portOsStr.str());
        LPCSTR portName = portStr.c_str();

        //open handle to comport
        hSerial = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);  //FILE_FLAG_OVERLAPPED //FILE_ATTRIBUTE_NORMAL
        if (hSerial == INVALID_HANDLE_VALUE) {
            LPCWSTR portErr = L"Error opening port\n";
            OutputDebugString(portErr);
        }

        //set comport parameters 
        init(UART_BAUD_RATE);

        //set comm Mask - will notify when a byte arrives in the port 
        if (!SetCommMask(hSerial, EV_RXCHAR)) {
            LPCWSTR maskErr = L"Error setting Com Mask\n";
            OutputDebugString(maskErr);
        }

        //initialize hEvent in the overlapped structure
        o.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (o.hEvent == NULL) {
            LPCWSTR eventErr = L"Error setting o event\n";
            OutputDebugString(eventErr);
        }

        //intialize the rest of the overlapped structure to 0
        o.Internal = 0;
        o.InternalHigh = 0;
        o.Offset = 0;
        o.OffsetHigh = 0;

        //start a queue timer to check for incoming bytes
        timerEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        timerQueue = CreateTimerQueue();
        wmc = this;
        if (!CreateTimerQueueTimer(&timerHandle, timerQueue, ListeningCallBack, wmc, 10, 10, 0)) {
            LPCWSTR tmrFail = L"Timer fail\n";
            OutputDebugString(tmrFail);
        }

        //set everything to a clear state 
        reset_state();
        sendBuf.clear();
    }


    static void CALLBACK ListeningCallBack(LPVOID lpParam, BOOLEAN TimerOrWaitFired) {
        windows_ModbusClient* w = (windows_ModbusClient*)(lpParam);
        DWORD dwCommEvent;

        if (WaitCommEvent(w->hSerial, &dwCommEvent, NULL)) {
            if (dwCommEvent == EV_RXCHAR) {
                w->uart_isr();
            }
        }
        else {
            //LPCWSTR eventErr = L"Error with wait comm event - queue timer\n";
            //OutputDebugString(eventErr);
            //int error = GetLastError();
            //qDebug() << error;
        }
    }

    /**
     * @brief Intializes the com port settings 
     * @param baud The baud rate as defined in the client_config.h file
    */
    void init(int baud) override {
        
        //get current state
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            LPCWSTR getErr = L"Error getting dcb state\n";
            OutputDebugString(getErr);
        }

        //set new state
        dcbSerialParams.BaudRate = baud;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = EVENPARITY;
       // dcbSerialParams.fRtsControl = RTS_CONTROL_ENABLE;
        if (!SetCommState(hSerial, &dcbSerialParams)) {
            LPCWSTR paramErr = L"Error setting serial port state\n";
            OutputDebugString(paramErr);
        }
    }


    //////////// Virtual function implementations ////////////

    /**
     * @brief Get the device's current system time
     * @return the current system time in microseconds
    */
    uint64_t get_system_time_us() {
        LARGE_INTEGER ticks;
        if (!QueryPerformanceCounter(&ticks)) {
            LPCWSTR tickErr = L"Error getting ticks for checking system time";
            OutputDebugString(tickErr);
        }
        return ticks.QuadPart / 10;
        //return ticks.QuadPart;
    }

public:

    /**
     * @brief If there are bytes left to send, add them to a buffer, then send them all together.
    */
    //need messages to be switched to protected, not private 
    void tx_enable() override {

        char charBuf[128] = { 0 };
        DWORD dwBytesWritten = 0;

        //while there are bytes left to send in the transaction, continue adding them to sendBuf
        while (messages.get_active_transaction()->bytes_left_to_send()) {
            if (my_state == emission) {
                send();
            }
        }

        //copy the contents of sendBuf over to charBuf - type issue
        for (int i = 0; i < sendBuf.size(); i++) {
            charBuf[i] = sendBuf[i];
        }

        //write the contents of charBuf to the serial port
        if (!WriteFile(hSerial, charBuf, sendBuf.size(), &dwBytesWritten, &o)) {
            if (GetLastError() != ERROR_IO_PENDING) {
                //ERROR_IO_PENDING - means the IO request was succesfully queued and will return later 
                LPCWSTR writeErr = L"Error sending bytes\n";
                OutputDebugString(writeErr);
                OutputDebugString((LPCWSTR)GetLastError());
            }
        }
        //flush butters and clear the sendbuf for next message 
        FlushFileBuffers(hSerial);
        sendBuf.clear();
    }

    /**
     * @brief Not using interupts, so no implementation needed.
    */
    void tx_disable() override {

    }

    /**
     * @brief Loads the send buffer with the next byte
     * @param byte		The byte to be transmitted.
     */
    void send_byte(uint8_t data) override {
        sendBuf.push_back(data);
    }

    /**
     * @brief Return the next byte received by the serial port.
     */
    uint8_t receive_byte() override {

        char buff = 0;
        int toRead = 1;
        DWORD bytesRead = 0;

        if (!ReadFile(hSerial, &buff, toRead, &bytesRead, &o)) { 
            if (GetLastError() != ERROR_IO_PENDING) {
                //ERROR_IO_PENDING - means the IO request was succesfully queued and will return later 
                LPCWSTR readErr = L"Error recieving bytes\n";
                OutputDebugString(readErr);
                OutputDebugString((LPCWSTR)GetLastError());
            }
            //else {
            //   // ERROR_IO_PENDING indicated - the readfile has not failed, but has not completed yet
            //    while (readPending) {
            //        bool complete = GetOverlappedResult(hSerial, &o, (LPDWORD)toRead, FALSE);
            //        if (!complete) {
            //            //read is not yet complete
            //            switch (dwError = GetLastError()) {
            //            case ERROR_IO_INCOMPLETE: {
            //                //operation is still pending, run through the loop again
            //                readPending = true;
            //                break;
            //            }
            //            default:
            //                //check for any other errors 
            //                LPCWSTR pendingErr = L"Error recieving byte - IO pending\n";
            //                OutputDebugString(LPCWSTR(pendingErr));
            //                OutputDebugString((LPCWSTR)GetLastError());
            //            }
            //        }
            //    }
            //    ResetEvent(o.hEvent);
            //}
        }

        return buff;
    }

    /**
     * @brief Adjust the baud rate
     * @param baud_rate the new baud rate in bps
     * this method overrides the modbus default delay
    */
    void adjust_baud_rate(uint32_t baud_rate_bps) override {

        if (!GetCommState(hSerial, &dcbSerialParams)) {
            LPCWSTR line = L"Error getting dcb state to update baud rate\n";
            OutputDebugString(line);
        }

        dcbSerialParams.BaudRate = baud_rate_bps;

        if (!SetCommState(hSerial, &dcbSerialParams)) {
            LPCWSTR line = L"Error setting serial port to new buadate\n";
            OutputDebugString(line);
        }
      
    }

    /**
    * @brief Get the device's current system time in cycles - not using cycles, so just returns elapsed time in microseconds
    */
    uint32_t get_system_cycles() override {
        LARGE_INTEGER ticks;
        if (!QueryPerformanceCounter(&ticks)) {
            LPCWSTR tickErr = L"Error getting ticks for checking system time";
            OutputDebugString(tickErr);
        }
        return ticks.QuadPart / 10;
    };


    /**
   * @brief Called whenever there is new data to recieve in the serial port.
   */
    void uart_isr() override {
        if (my_state == reception) {
            while (byte_ready_to_receive()) {

                receive();
                //    //slot called when new data arrives in the port 
                //    //as long as the state is reception and there is data to recieve, it will be recieved. 
                //    //receive method handles sloting data into the correct transaction.

            }

        }
    }

    /**
    * @brief checks the comport to determine if at least one byte is ready to be read
    */
    bool byte_ready_to_receive()override {

        LPDWORD lpErrors = 0;
        COMSTAT lpStat { 0 };
        if (!ClearCommError(hSerial, lpErrors, &lpStat)) {
            LPCWSTR clearErr = L"Issue checking com errors\n";
            OutputDebugString(clearErr);
            return false;
        }
        return (lpStat.cbInQue > 0);
    };


    /**
    * @brief ends the listening thread, purges the comport and closes it 
    */
    ~windows_ModbusClient() {

        //delete timers in the timer queue 
        //have to signal the timer here to stop the timer 

        SetEvent(timerEvent);
        DWORD result = WaitForSingleObject(timerEvent, 1000);
        if (result == WAIT_OBJECT_0) {
            LPCWSTR sig = L"Timer has terminated\n";
            OutputDebugString(sig);
        }
        else {
            LPCWSTR nonSig = L"Timer has not terminated yet\n";
            OutputDebugString(nonSig);
        }

        CloseHandle(timerEvent);

        if (!DeleteTimerQueue(timerQueue)) {
            if (GetLastError() != 997) {
                LPCWSTR delErr = L"Error deleting timers\n";
                OutputDebugString(delErr);
                int error = GetLastError();
                qDebug() << error;
            }
        }

        FlushFileBuffers(hSerial);
        PurgeComm(hSerial, PURGE_TXABORT);
        PurgeComm(hSerial, PURGE_RXABORT);
        CloseHandle(hSerial);

        //ExitProcess(0); //shuts down everything - only really used for unity, so could maybe be an if def?

        LPCWSTR clsPrt = L"Closing port\n";
        OutputDebugString(clsPrt);
    }
};

extern windows_ModbusClient modbus_client;



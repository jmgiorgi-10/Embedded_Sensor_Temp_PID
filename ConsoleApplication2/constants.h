#pragma once

//#include "ftd2xx.h"

//FT_HANDLE handle;

uint32 slaveAddress = 0b1010000;

//uint32 slaveAddress = 82;


uint8 TEMP_SENSOR_SETUP = 0x14;
uint8 FIFO_DATA = 0x08;
uint8 FIFO_CONFIGURATION = 0x0A;
uint8 FIFO_READ_POINTER = 0x05;
uint8 FIFO_OVERFLOW_COUNTER = 0x06;
uint8 FIFO_DATA_COUNTER = 0x07;



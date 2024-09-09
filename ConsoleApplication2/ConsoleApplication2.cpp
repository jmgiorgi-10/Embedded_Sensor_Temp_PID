// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include "ftd2xx.h"
#include "libmpsse_i2c.h"
#include "readwrite.h"
//#include "constants.h"
#include "tempread.h"
#include "voltageoutput.h"
#include "PID.h"

using namespace std;

FT_STATUS status;
FT_HANDLE handle;
uint8 buffer[256];
uint8 data;

ChannelConfig channelConfig;


int main()
{
    DWORD number_of_channels = 0;
    //DWORD sizeToTransfer = 1; // 1 byte (8 bits).
    //DWORD sizeTransfered = 0;
    DWORD options = 0x00000000;
    DWORD index = 0;
    //uint8 buffer[] = { 0x01, 0x02, 0xFF, 0x7F, 0xA5 }; // buffer stores 8 eight bit unsigned integers. When passing to a function buffer decays to a pointer to the first element.
  /*  uint8 bytesToTransfer = 0;*/
    uint8 data;

    Init_libMPSSE();
    status = I2C_GetNumChannels(&number_of_channels);
    cout << "Hello World!\n";
    cout << "number of channels equals " << number_of_channels << endl;

    // need to find a way to obtain the temperature sensor I2C slave address,
    // in order to read bytes from it on the FT232H.

    status = I2C_OpenChannel(index, &handle);

    channelConfig.ClockRate = I2C_CLOCK_STANDARD_MODE;
    channelConfig.Options = options;
    channelConfig.LatencyTimer = 75;
    status = I2C_InitChannel(handle, &channelConfig);
    if (status != FT_OK) {
        cout << "issue with status1" << endl;
    }
    else {
        cout << "status1 is working" << endl;
    }

    uint32 i2cOptions = I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_STOP_BIT;
  
    //// Connect to the Labjack DAQ for Voltage Ouptut //
    LabJack L0;
        // Run test pwm method:
    L0.TestPWM();

    // PID Object:
    PID pid0(0.042, 188, 28.2, 40, 1);
    pid0.PIDUpdate(24);

    while (1) {
    
        temp_measurement(handle);
        // if finished debugging i2c comm:
            // 1. make temp_measurment function return a float or float array (new_temp)
            // 2. drive = pid0.PIDUpdate(new_temp);
            // 3. LO.TestPWM(drive); // drive (% as 0-1, would multiply by the Labjack value corresponding to 100% duty cycle.)

    }

    Cleanup_libMPSSE();
    return(0);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

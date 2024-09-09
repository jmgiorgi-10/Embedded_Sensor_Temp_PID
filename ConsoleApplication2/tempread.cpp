
#include "readwrite.h"
#include "constants.h"
#include "tempread.h"
#include <bitset>
#include <iostream>

void printIfIssue(FT_STATUS status) {
    if (status != FT_OK) { std::cout << "error code: " << status << std::endl; }
    else { std::cout << "FT_STATUS is OK" << std::endl; }
}

void temp_measurement(FT_HANDLE handle) {

    FT_STATUS status;

    //uint8 data;
    //status = read_byte(handle, slaveAddress, TEMP_SENSOR_SETUP, &data);
    //printIfIssue(status);
    //uint8 new_data = data | 0b00000001;

    status = write_byte(handle, slaveAddress, TEMP_SENSOR_SETUP, 0b11111111);
    printIfIssue(status);

    uint8 temp_data[2];

    status = read_word(handle, slaveAddress, FIFO_DATA, temp_data);

   /* status = read_byte(handle, slaveAddress, FIFO_DATA, &temp_data[0]);
    status = read_byte(handle, slaveAddress, FIFO_DATA, &temp_data[1]);
    uint16_t combined_temp_data = (temp_data[1] << 8) | temp_data[0];*/
    std::cout << "16 bits raw temperature data: " << std::bitset<16>(temp_data) << std::endl;
    std::cout << "decimal temperature data: " << std::bitset<16>(temp_data).to_ulong() * 0.005 << std::endl;
    printIfIssue(status);


    // now, flush(clear) the FIFO register. //
    //uint8 FLUSH_FIFO_MASK = 0b00010000;
    //uint8 fifo_config_data;
    //status = read_byte(handle, slaveAddress, FIFO_CONFIGURATION, &fifo_config_data);
    //printIfIssue(status);
    //uint8 new_fifo_config_data = fifo_config_data | FLUSH_FIFO_MASK;
    //status = write_byte(handle, slaveAddress, FIFO_CONFIGURATION, new_fifo_config_data);
    //printIfIssue(status);

    // check if FIFO register was flushed, by looking at the FIFO READ POINTER
    uint8 fifo_read_pointer[1];
    status = read_byte(handle, slaveAddress, FIFO_READ_POINTER, &fifo_read_pointer[0]);
 
    std::cout << "fifo read pointer is at: " << std::bitset<5>(fifo_read_pointer[0]) << std::endl;


    // fifo data counter
    uint8 fifo_data_count[1];
    status = read_byte(handle, slaveAddress, FIFO_DATA_COUNTER, &fifo_data_count[0]);

    std::cout << "amount of words(2 bytes) in the fifo: " << std::bitset<6>(fifo_data_count).to_ulong() << std::endl;


    uint8 over_flow_condition[1];
    status = read_byte(handle, slaveAddress, FIFO_OVERFLOW_COUNTER, &over_flow_condition[0]);
    std::cout << "overflow count: " << std::bitset<5>(over_flow_condition[0]) << std::endl;
    
    printIfIssue(status);



    return;
}
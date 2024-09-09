#include "readwrite.h"
#include <iostream>


FT_STATUS read_word(FT_HANDLE handle, uint8 slaveAddress, uint8 registerAddress, uint8 data[2])
{

	FT_STATUS status;
	uint8 buffer[2];
	uint32 bytesToTransfer = 0;
	uint32 bytesTransfered;
	bytesToTransfer = 0;
	bytesTransfered = 0;

	buffer[bytesToTransfer++] = registerAddress; /*Byte addressed inside EEPROM */

	// NOTE: as per the MAX temp sensor standard, we write a Start bit, before the register address, but we do not send a stop bit.
	status = I2C_DeviceWrite(handle, slaveAddress, bytesToTransfer, buffer, &bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT);

	bytesToTransfer = 2;
	bytesTransfered = 0;
	// NOTE: as per the MAX temp sensor standard, we send a Repeated Start bit, before the data byte, and a Stop bit after
	status = I2C_DeviceRead(handle, slaveAddress, bytesToTransfer, buffer, \
		& bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_STOP_BIT); 

	std::cout << "bytes transferred from FIFO Data Register: " << bytesTransfered << std::endl;

	data[0] = buffer[0];
	data[1] = buffer[1];

	return status;
}





FT_STATUS read_byte(FT_HANDLE handle, uint8 slaveAddress, uint8 registerAddress, uint8* data)
{
	FT_STATUS status;
	uint8 buffer[1];
	uint32 bytesToTransfer = 0;
	uint32 bytesTransfered;
	bytesToTransfer = 0;
	bytesTransfered = 0;

	buffer[bytesToTransfer++] = registerAddress; /*Byte addressed inside EEPROM */

	// NOTE: as per the MAX temp sensor standard, we write a Start bit, before the register address, but we do not send a stop bit.
	status = I2C_DeviceWrite(handle, slaveAddress, bytesToTransfer, buffer, &bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT);

	bytesToTransfer = 1;
	bytesTransfered = 0;
	// NOTE: as per the MAX temp sensor standard, we send a Repeated Start bit, before the data byte, and a Stop bit after
	status = I2C_DeviceRead(handle, slaveAddress, bytesToTransfer, buffer, \
		& bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_STOP_BIT);

	*data = buffer[0];
	return status;
}


FT_STATUS write_byte(FT_HANDLE handle, uint8 slaveAddress, uint8 registerAddress, uint8 data)
{
	FT_STATUS status;
	/*uint8 buffer[10];*/

	uint8 buffer[1];

	uint32 bytesToTransfer;
	uint32 bytesTransfered;
	bool writeComplete = 0;
	uint32 retry = 0;
	bytesToTransfer = 1;
	bytesTransfered = 0;
	//buffer[bytesToTransfer++] = registerAddress; /* Byte addressed inside EEPROM */
	//buffer[bytesToTransfer++] = data;

	buffer[0] = registerAddress;

	status = I2C_DeviceWrite(handle, slaveAddress, bytesToTransfer, buffer, \
		& bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_STOP_BIT);

	/* poll to check completion */
	//while ((writeComplete == 0) && (retry < 10))
	//{
	//	bytesToTransfer = 0;
	//	bytesTransfered = 0;
	//	buffer[bytesToTransfer++] = registerAddress; /* Addressed inside EEPROM */

	//	status = I2C_DeviceWrite(handle, slaveAddress, bytesToTransfer, \
	//		buffer, &bytesTransfered, \
	//		I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
	//	if ((FT_OK == status) && (bytesToTransfer == bytesTransfered))
	//	{
	//		writeComplete = 1;
	//		/*print(" ... Write done\n");*/
	//	}
	//	retry++;
	//}
	return(status);
}
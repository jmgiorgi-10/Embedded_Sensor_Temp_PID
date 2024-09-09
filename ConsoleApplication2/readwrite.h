#pragma once

#include "ftd2xx.h"
#include "libmpsse_i2c.h"

FT_STATUS read_byte(FT_HANDLE, uint8, uint8, uint8*);
FT_STATUS read_word(FT_HANDLE, uint8, uint8, uint8[2]);

FT_STATUS write_byte(FT_HANDLE, uint8, uint8, uint8);
#pragma once

#include "LabJackUD.h"

class LabJack {

	LJ_HANDLE handle;

public:
	LabJack();
	LJ_ERROR Init();
	LJ_ERROR TestPWM();
	/*LJ_ERROR SetPWM(float);*/

};


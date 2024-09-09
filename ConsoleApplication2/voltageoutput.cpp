
#include "voltageoutput.h"



//class LabJack {
//
//	LJ_HANDLE handle;
//	
//	LabJack(){
//	
//		Init();
//	
//	}
//	
//	LJ_ERROR Init();
//	LJ_ERROR TestPWM();
//	LJ_ERROR SetPWM(float);
//
//};
//
//

// constructor definition.
LabJack::LabJack() {

	LabJack::Init();

}

LJ_ERROR LabJack::Init() {

	LJ_ERROR error;
	error = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", true , &handle);

	return(error);

}

LJ_ERROR LabJack::TestPWM() {

//Execute the pin_configuration_reset IOType so that all
//pin assignments are in the factory default condition.
//The ePut function is used, which combines the add/go/get.

	LJ_ERROR error;
	
	error = ePut(handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
	//First, an add/go/get block to configure the timers and counters.
	//Set the pin offset to 4, which causes the timers to start on FIO4.
	error = AddRequest(handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);
	//Enable both timers. They will use FIO4-FIO5
	error = AddRequest(handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 2, 0, 0);
	//Make sure Counter0 is disabled.
	error = AddRequest(handle, LJ_ioPUT_COUNTER_ENABLE, 0, 0, 0, 0);
	//Enable Counter1. It will use the next available line, FIO6.
	error = AddRequest(handle, LJ_ioPUT_COUNTER_ENABLE, 1, 1, 0, 0);
	//All output timers use the same timer clock, configured here. The
	//base clock is set to 48MHZ_DIV, meaning that the clock divisor
	//is supported and Counter0 is not available. Note that this timer
	//clock base is not valid with U3 hardware version 1.20.
	error = AddRequest(handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ_DIV, 0, 0);
	//Set the timer clock divisor to 48, creating a 1 MHz timer clock.
	error = AddRequest(handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 48, 0, 0);
	//Configure Timer0 as 8-bit PWM. It will have a frequency
	//of 1M/256 = 3906.25 Hz.
	error = AddRequest(handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM8, 0, 0);
	//Initialize the 8-bit PWM with a 50% duty cycle.
	error = AddRequest(handle, LJ_ioPUT_TIMER_VALUE, 0, 32768, 0, 0);
	//Configure Timer1 as duty cycle input.
	error = AddRequest(handle, LJ_ioPUT_TIMER_MODE, 1, LJ_tmDUTYCYCLE, 0, 0);
	//Execute the requests.
	error = GoOne(handle);

	return(error);

}




//LJ_ERROR LabJack::SetPWM(float duty_cycle) {
//
//	
//
//}
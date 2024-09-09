#pragma once

#include <vector>

class PID {

	float setpoint; // what is the desired temperature value of the control system?
	//float max_error; // at what error value (e.g. delta 20 deg C), do we want to use the full output?
	float max_drive; // what is the maximum value at which we can drive the output; the PID output will be calculated as % of that max; min is assumed to be 0. E.g. max = 5V, min = 0V.

	float p;
	float i;
	float d;

	bool with_derivative = false;

	int storage = 32; // how many past temperature values do we want to store (for integral)?
	std::vector<float> temp_store; // past temp value storage

	public:
		PID(float, float, float, float, float);
		float PIDUpdate(float);

};
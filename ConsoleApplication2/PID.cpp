
#include "PID.h"
#include <vector>

// Tuning the PID --> Start by experimenting enough to get a reasonable order of magnitude proportional factor, without including either integral or derivative terms.
// Try an integral term if you oftesteady state error.


// constructor
PID::PID(float p_arg, float i_arg, float d_arg, float setpoint_arg	, float max_drive_arg) : p(p_arg), i(i_arg), d(d_arg), setpoint(setpoint_arg), max_drive(max_drive_arg) {}

float PID::PIDUpdate(float current_temp) {

	float error = setpoint - current_temp;

	if (temp_store.size() >= storage) {
		temp_store.erase(temp_store.begin());
	}
	temp_store.push_back(current_temp);

	float integral = 0;
	for (auto& t : temp_store)
		integral += t;

	// Note: discrete filter-like approach to pid below assumes all time intervals between data points are equal ()
	float drive_output;
	if (temp_store.size() <= 2) {
		drive_output = std::max(p * error, max_drive);
	}
	else if (with_derivative) {
		drive_output = std::max(p * error + i * integral + d * (temp_store[temp_store.size()-1] - temp_store[temp_store.size()-2]), max_drive); // will add integer & derivative terms later.
	}
	else {
		drive_output = std::max(p * error + i * integral + d * (temp_store[temp_store.size() - 1] - temp_store[temp_store.size() - 2]), max_drive);
	}
			
	return(drive_output);
}



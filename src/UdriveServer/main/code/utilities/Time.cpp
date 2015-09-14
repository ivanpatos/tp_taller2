#include <ctime>
#include "../../include/utilities/Time.h"

std::string Time::getCurrentTime(){
	time_t timeNow = time(0);
	tm timeStruct = *localtime(&timeNow);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y,%X", &timeStruct);
	std::string time(buffer);
	return time;
}


#include <iostream>
#include <fstream>
#include <ctime>

#include "log.h"

namespace Log {
	
static const bool debug = false;
static const bool console = false;
	
static const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

void log(std::string msg)
{
	if (debug) {
		msg = std::string(currentDateTime()) + " – " + msg;
		std::ofstream logFile("log.txt", std::ios::app | std::ios::out);
		logFile << msg << std::endl;
		if (console) std::cerr << msg << std::endl;
		logFile.close();
	}
}

}
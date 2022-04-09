#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "Plane.h"
#include "utils.h"
#include "maths.h"

using std::runtime_error;
using std::cout;
using std::ofstream;
using std::ios;
using namespace std::chrono;

void returnToController();
void endProgram();

inline string getCurrentDateTime(string s) { //Logging methods. Attribution: Streamsoup on https://stackoverflow.com/questions/7400418/writing-a-log-file-in-c-c at 12:51 AM 4/7/2022
    time_t now = time(0);
    struct tm tstruct;
	char buf[80];
    localtime_s(&tstruct, &now);
    if (s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return string(buf);
};

string directory = "Flight Log " + getCurrentDateTime("now") + ".txt";

inline void Logger(string logMsg) {
    string now = getCurrentDateTime("now");

    ofstream ofs(directory.c_str(), std::ios_base::out | std::ios_base::app);
    ofs << now << '\t' << logMsg << '\n';
    ofs.close();
}

auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);

int main() {

	std::replace(directory.begin(), directory.end(), ':', '-');

	Logger("Logfile created");

	//Instantiation, and basic stats collection.

    bool flight = true;
    bool autoFlight = false;

    plane us;

    do
    {
        if (autoFlight)
        {

        }
        else
        {

        }
    } while (flight);

    endProgram();

}
void returnToController() {
	Logger("Returning to Remote Control...");
	endProgram();
}
void endProgram() {
	Logger("Ending the program...");
}
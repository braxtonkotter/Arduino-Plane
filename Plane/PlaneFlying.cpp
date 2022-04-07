#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Plane.h"

using std::runtime_error;
using std::cout;
using std::ofstream;
using std::ios;
using namespace std::chrono;

void returnToController();
void endProgram();

auto startTime = std::chrono::system_clock::now();

ofstream generalData(genericString, ios::out);
ofstream flightData;

int main() {

	std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
	string genericString;
	genericString += "Log" += std::ctime(&start_time) += ".txt";

	//Instantiation, and basic stats collection.


	try
	{
		// DepthAI code
	}
	catch (const runtime_error& e)
	{
		returnToController();
	}
}
void returnToController() {
	cout << "AN ERROR OCCURED AND WE RETURNED TO THE REMOTE!" << endl;
	endProgram();
}
void endProgram() {
	//fout.close();
	auto sysstop = high_resolution_clock::now();
}
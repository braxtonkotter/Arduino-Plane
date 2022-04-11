#include "waypoint.h"
#include "graph.h"
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;

void waypointTest();
void graphTest();
int main() {
	waypointTest();
	graphTest();
	return 1;
}
void waypointTest() {
	cout << "Waypoint Tests: " << endl;

	waypoint test(270, 180, 3);

	cout << "Test 1: ";
	if (fabs(test.getDistance() - 3) < 0.0001 && test.getElevation() == 0 && test.getOffset() == 90) {
		cout << "passed!" << endl;
	}
	else {
		cout << "failed." << endl;
		cout << test;
	}

	test.updateWaypoint(360, 720, -5);

	cout << "Test 2: ";
	if (fabs(test.getDistance() - 5) < 0.0001 && test.getElevation() == 0 && test.getOffset() == 180) {
		cout << "passed!" << endl;
	}
	else {
		cout << "failed." << endl;
		cout << test;
	}

	test.addToWaypoint(540, 180, 10);

	cout << "Test 3: ";
	if (fabs(test.getDistance() - 15) < 0.0001 && test.getElevation() == 0 && test.getOffset() == 180) {
		cout << "passed!" << endl;
	}
	else {
		cout << "failed." << endl;
		cout << test;
	}

	test.updateWaypoint(-720, 15, 2.70);

	cout << "Test 4: ";
	if (fabs(test.getDistance() - 2.7) < 0.0001 && test.getElevation() == 15 && test.getOffset() == 0) {
		cout << "passed!" << endl;
	}
	else {
		cout << "failed." << endl;
		cout << test;
	}

	test.addToWaypoint(-92, 56, -28);

	cout << "Test 5: ";
	if (fabs(test.getDistance() - 25.3) < 0.0001 && test.getElevation() == -71 && test.getOffset() == 88) {
		cout << "passed!" << endl;
	}
	else {
		cout << "failed." << endl;
		cout << test;
	}
}
void graphTest() {
	graph<int> intGraphA;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 400; i++) {
		intGraphA.add(i);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Creation duration: " << duration.count() << endl;
	cout << intGraphA;
}
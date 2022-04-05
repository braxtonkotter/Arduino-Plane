#include "waypoint.h"
#include "graph.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

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
	graph<int> intGraphA(1);
	for (int i = 0; i < 100; i++) {
		intGraphA.push_back(i);
	}
	cout << intGraphA;
	graph<int> intGraphB(0.01);
	for (int i = 0; i < 200; i += 2) {
		intGraphB.push_back(i);
	}
}
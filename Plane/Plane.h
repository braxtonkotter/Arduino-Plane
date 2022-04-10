#pragma once

#include <chrono>

#include "waypoint.h"
#include "utils.h"
#include "SpaceCurve.h" //Has all other headers included

class plane {
public:
	plane();

	Vector3 getPosition() { return pos; }
	Vector3 getOrientation() { return orientation; }

	void setTarget(Vector3 trg) { target = trg; flightplan(); }

	void fly(); //Send information to the arduino for an action. Built upon flight path.
private:

	void flightplan();
	bool plausibility();
	int safety();

	const Vector3 home = Vector3(0,0,0); //Home point. Determine plane stats based on this
	Vector3 target = Vector3(0,0,0); //Target point. Fly to here.
	Vector3 pos = Vector3(0,0,0);
	Vector3 orientation = Vector3(0, 0, 0);
	const Vector3 size = Vector3(0,0,0);
	
	waypoint w1 = waypoint(0, 0, 1); // 0-1
	waypoint w2 = waypoint(0, 0, 2); // 1-2
	waypoint w3 = waypoint(0, 0, 3); // 2-3
	waypoint w4 = waypoint(0, 0, 4); // 3-4
	waypoint w5 = waypoint(0, 0, 5); // 4-5
	waypoint w6 = waypoint(0, 0, 7.5); //5-7.5
	waypoint w7 = waypoint(0, 0, 10); //7.5-10
	waypoint w8 = waypoint(0, 0, 20); //10-20
	waypoint w9 = waypoint(0, 0, 30); //20-30
	waypoint w10 = waypoint(0, 0, 40); //30-40

	//SpaceCurve flightPath; // Space Curve of the flight path
};

plane::plane() {
	
}
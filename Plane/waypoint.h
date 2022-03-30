#pragma once
#include "utils.h"
#include <ostream>
#include <memory>

using std::ostream;
using std::string;

class waypoint {
public:
	waypoint(float a = 0.0, float b = 0.0, float c = 0.0, waypoint *d = nullptr, waypoint *e = nullptr) {
		position.offset = a;
		position.elevation = b;
		position.distance = c;
		reFormatPosition();

		previousWaypoint = d;
		nextWaypoint = e;
	}

	void updateWaypoint(float a, float b);
	void updateWaypoint(float a, float b, float c);

	void addToWaypoint(float a, float b);
	void addToWaypoint(float a, float b, float c);

	float getOffset() const;
	float getElevation() const;
	float getDistance() const;

	friend ostream& operator<< (ostream& o, const waypoint& w);
private:
	polarCoordinate position; // Where the waypoint points to and how far it is away
	void reFormatPosition();
	waypoint* previousWaypoint = nullptr;
	waypoint* nextWaypoint = nullptr;
};

void waypoint::updateWaypoint(float a, float b) {
	position.offset = a;
	position.elevation = b;
	reFormatPosition();
}

void waypoint::updateWaypoint(float a, float b, float c) {
	position.offset = a;
	position.elevation = b;
	position.distance = c;
	reFormatPosition();
}

void waypoint::addToWaypoint(float a, float b) {
	position.offset += a;
	position.elevation += b;
	reFormatPosition();
}

void waypoint::addToWaypoint(float a, float b, float c) {
	position.offset += a;
	position.elevation += b;
	position.distance += c;
	reFormatPosition();
}

void waypoint::reFormatPosition() {
	if (position.distance < 0) { //If we have a negative distance, we gotta set it positive then reverse the angles
		position.distance *= -1; //Puts it on the opposite side of the sphere
		position.elevation *= -1; //Flips it over the base disk
		position.offset += 180; //Rotates it back around to its beginning point
	}

	if (position.elevation < -90 || position.elevation > 90) { //If it's lower than straight down or higher than straight up
		while (position.elevation < -180 || position.elevation > 180) { //Modulus operation for a float.
			position.elevation += 360 * ((position.elevation < 0) ? 1 : -1); //Adds 360 if less than -180, subtracts 360 if more than 180.
		}

		if (position.elevation < -90 || position.elevation > 90) { //If it wasn't just hyper extended in a circle
			position.elevation = ((position.elevation < 0) ? -1 : 1) * 180 - position.elevation; //either 180 - (180 -> 90) or -180 - (-180 -> -90) (-180 + (180->90))

			position.offset += 180; //Rotate around
		}
	}

	while (position.offset >= 360 || position.offset < 0) { //If we're turned around more than once
		position.offset += 360 * ((position.offset<0) ? 1 : -1);
	}
}

float waypoint::getOffset() const { return position.offset; }
float waypoint::getElevation() const { return position.elevation; }
float waypoint::getDistance() const { return position.distance; }

ostream& operator<<(ostream& out, const waypoint& w) {
	out << "Angle of Offset: " << w.getOffset() << std::endl;
	out << "Angle of Elevation: " << w.getElevation() << std::endl;
	out << "Distance: " << w.getDistance() << std::endl;
	return out;
}
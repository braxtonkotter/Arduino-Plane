#pragma once
#include <iostream>

using std::string;

string dimensions[3] = { "mm", "m", "km" };
int ratio[3] = { 0.001, 1, 1000 };

class dimension {
public:
	dimension(string s) : unit(s) {}
	void convertTo(string newUnit);
	string getDimension();
private:
	string unit;
};

void dimension::convertTo(string newUnits) { //This will only happen between metric units for the time being
	if (unit != newUnits) {
		for (int i = 0; i < dimensions.length(); i++) {

		}
	}
}

string dimension::getDimension() {
	return unit;
}
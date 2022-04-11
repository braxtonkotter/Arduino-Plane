#pragma once

class expression;

struct Vector2 {
	Vector2() {
		x = 0;
		y = 0;
	}
	Vector2(float a, float b) {
		x = a;
		y = b;
	}
	float x;
	float y;
};

struct Vector3 {
	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	float x;
	float y;
	float z;
};

struct polarCoordinate {
	polarCoordinate() {
		elevation = 0;
		offset = 0;
		distance = 0;
	}
	polarCoordinate(float a, float b, float c) {
		elevation = a;
		offset = b;
		distance = c;
	}
	float elevation;
	float offset;
	float distance;
};
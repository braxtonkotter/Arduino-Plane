#pragma once

struct coordinate {
	coordinate(float a = 0, float b = 0) {
		x = a;
		y = b;
	}
	float x;
	float y;
};

struct Vector3 {
	Vector3(float a=0, float b=0, float c=0) {
		x = a;
		y = b;
		z = c;
	}
	float x;
	float y;
	float z;
};

struct polarCoordinate {
	polarCoordinate(float a=0, float b=0, float c=0) {
		elevation = a;
		offset = b;
		distance = c;
	}
	float elevation;
	float offset;
	float distance;
};

struct Object { //Position. orientation, size
	Object(Vector3 a, Vector3 b, Vector3 c) : position(a), orientation(b), size(c) {}
	Object(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0, float g = 0, float h = 0, float i = 0)
	{
		position.x = a;
		position.y = b;
		position.z = c;
		orientation.x = d;
		orientation.y = e;
		orientation.z = f;
		size.x = g;
		size.y = h;
		size.z = i;
	}
	Vector3 position;
	Vector3 orientation;
	Vector3 size;
};
#pragma once
#include "expression.h"

class variable {
public:
	variable(char n, double v, bool x = true) : name(n), value(v), var(x) {}

	double operator+(expression e); 
	double operator-(expression e); 
	double operator*(expression e); 
	double operator/(expression e); 
	double operator^(expression e); 

	double operator+(variable v);
	double operator-(variable v);
	double operator*(variable v);
	double operator/(variable v);
	double operator^(variable v);

	double operator+(coefficient e);
	double operator-(coefficient e);
	double operator*(coefficient e);
	double operator/(coefficient e);
	double operator^(coefficient e);
private:
	char name;
	double value;
	bool var;
};
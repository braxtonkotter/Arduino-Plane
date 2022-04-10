#pragma once
#include "expression.h"

class function {
public:
	function();
	function(string s);

	//void operator+(function f); // Add function to another

	//double operator()(double d); // Determine the value based on a parameter
private:
	shared_ptr<expression> val = nullptr;
};

function::function(string s) {
	val = make_shared<expression>(&s[0]);
}
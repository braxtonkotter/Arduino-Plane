#pragma once
#include "expression.h"
#include "utils.h"
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

class function {
public:
	function(string s);

	void operator+(function f); // Add function to another

	double operator()(double d); // Determine the value based on a parameter
private:
	expression val;
};

function::function(string s) {
	val = expression(&s[0]);
}
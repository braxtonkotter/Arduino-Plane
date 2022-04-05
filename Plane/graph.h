#pragma once
#include <memory>
#include <vector>
#include "utils.h"
#include <ostream>

/*

graph by Ryan Steed

The purpose of this code is to simulate a graph-type object.
Elements are stored in a queue.
There will be a hard length and subdivision size. 

This code is meant to be used for x y z roll yaw pitch speed and servo measures. It will be measured with distance as the x axis.
That distance will have constant subdivision sizes, and depending on how far ahead we need to plan, we'll populate the graph.
For a first call, we use a vector to populate the graph with a subdivisions size.

Do we truncate data or implement? I say we have no set "distance" but we keep a sense of order. We'll mark subdivision size and have no max length.
We'll need to retrieve values as well, maybe more than one point at a time.

*/

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::ostream;

template<class type>
struct Node {
	type data;
	shared_ptr<Node<type>> next = nullptr;
};

template<class type>
class graph {
public:
	graph();
	graph(float a) : dx(a) { remainder = 0.0; }
	graph(float a, vector<type> lst) : dx(a) { remainder = 0.0; add(lst); }

	void push_back(vector<type>); //Adds values from a vector list to the end of a graph
	void push_back(type); //Add an element
	void clear(); //Clears the list of all values. Sets front and back to null, deleting all smart pointers.

	type peek() const { return front->data; }
	//type peek(float i); //Returns the specified point. For future planning.? PUT ON HOLD UNTIL LATER

	void pop(); //Pops the top value
	void pop(float step); //Pops however many values the step covers.
	void pop(int idx); //Pops this many values

	void setdx(float i); //Changes the xStep size. Needed if accuracy needs to be changed. Rescales each value in the graph to fit what it was before, filling in if needed. Really, it  creates a new graph.
	
	float getdx() const	{ return dx; }

	void rePopulateGraph(vector<type> l) { clear(); add(l); } //Re populate the grpah
	void populateGraph(vector<type> l) { add(l); } //Add to the graph
	friend ostream& operator<< (ostream& out, const graph& g);
private:
	int size; //How many elements the graph holds
	float dx; //How much the x axis increases per value
	float remainder; //Marks how much further past the last value but not quite to the next value we are.

	//Size is inherent, depending on the x upper bound and the x lower bound as well as subdivision size

	shared_ptr<Node<type>> front = nullptr;														//We're using a queue form for values
	shared_ptr<Node<type>> back = nullptr;
};

template<class type>
graph<type>::graph() {
	dx = 1.0;
	remainder = 0.0;
}
//Basic population/depopulation of the graph.
template<class type>
void graph<type>::push_back(type item) { //Add an item to end of the linked list
	auto temp = make_shared<Node<type>>();
	temp->data = item;
	if (front != nullptr) {
		back->next = temp;
		back = temp;
	}
	else {
		front = temp;
		back = temp;
	}
	size++;
}
template<class type>
void graph<type>::push_back(vector<type> list) {
	for (type a : list) {
		add(a);
	}
}

template<class type>
void graph<type>::clear()
{
	front = nullptr;
	back = nullptr;
	size = 0;
}

template<class type>
void graph<type>::pop() {
	front = front->next;
	size--;
}
template<class type>
void graph<type>::pop(float step) {
	for (float i = 0; i < step; i += dx) {
		pop();
	}
}
template<class type>
void graph<type>::pop(int idx) {
	for (int i = 0; i < idx; i++) {
		pop();
	}
}

template<class type>
void graph<type>::setdx(float newdx) {

}

template<class type>
ostream& operator<<(ostream& out, const graph<type>& g) {
	idx = 0;
	while()
}
#pragma once
#include <memory>
#include <vector>
#include "utils.h"
#include <ostream>
#include <chrono>

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
using std::endl;
using std::runtime_error;
using namespace std::chrono;

template<class type>
struct Node {
	type data;
	shared_ptr<Node<type>> next = nullptr;
	shared_ptr<Node<type>> previous = nullptr; //Needed for chapter modifying, mainly
};

template<class type>
class graph;

template<class type>
ostream& operator<<(ostream& out, const graph<type>& g);

template<class type>
class graph {
public:
	graph();

	void add(type i);
	void remove();

	vector<type> getPoints(); // Returns a vector of all points in the graph
	vector<type> getPoints(int start, int stop); //Returns a vector of all points between the two specified indices
	vector<type> getPoints(type start, type stop); //Returns a vector of all points between the two specified objects

	friend ostream& operator<<<>(ostream& out, const graph<type>& g);
private:
	int size; //How many elements the graph holds
	float dx; //How much the x axis increases per value
	float remainder; //Marks how much further past the last value but not quite to the next value we are.
	int subDivSize; //How many elements are between subdivision headers.

	void push_back(type obj); //Add a new element to the queue
	bool pop(); //Remove an element from the queue

	bool empty();

	vector<shared_ptr<Node<type>>> root; // Vector of subdivision "chapter" headers. Bookmarks specific places in the queue.

	shared_ptr<Node<type>> front = nullptr;
	shared_ptr<Node<type>> back = nullptr;
};

template<class type>
graph<type>::graph() {
	size = 0;
	dx = 1.0;
	remainder = 0.0;
	subDivSize = 100;
}
template<class type>
void graph<type>::push_back(type obj) {
	auto temp = make_shared<Node<type>>();
	temp->data = obj;
	if (!empty()) { //Add object
		temp->previous = back;
		back->next = temp;
		back = temp;
	}
	else { //Add object
		front = temp;
		back = temp;
	}

	size++;

	if (size % subDivSize == 0) { //Add new chapter header
		root.push_back(temp);
	}
}
template<class type>
bool graph<type>::pop() {
	if (!empty()) { //If there is a value to remove
		if (size % subDivSize == 0) { //If we're about to make it smaller than the subdivision
			root.pop_back();
		}

		front = front->next; //Move forward.
		front->previous = nullptr; //Delete the first value

		for (shared_ptr<Node<type>> obj : root) { //For each chapter heading, move it one object further.
			obj = obj->next;
		}

		size--;

		return true;
	}
	else {
		return false;
	}
}
template<class type>
bool graph<type>::empty() {
	return front == nullptr;
}
template<class type>
vector<type> graph<type>::getPoints() {
	vector<type> list;
	auto temp = front;
	while (front != nullptr) {
		list.push_back(temp->data);
		temp = temp->next;
	}
	return list;
}
template<class type>
vector <type> graph<type>::getPoints(int start, int stop) {
	if (stop <= start) {
		throw runtime_error("Invalid range!");
	}
	vector<type> list;
	auto temp = front;
	int idx = start;
	int subDivNum = floor(start / subDivSize) - 1;

	if (subDivNum > 0) {
		idx = idx % subDivSize;
		temp = root[subDivNum];
	}
	for (int i = 0; i < idx; i++) {
		temp = temp->next;
	}

	for (int i = 0; i < stop - start; i++) {

	}
}
template<class type>
vector <type> graph<type>::getPoints(type start, type stop) {

}

//Shortcut names

template<class type>
void graph<type>::add(type i) {
	push_back(i);
}
template<class type>
void graph<type>::remove() {
	pop();
}

template<class type>
ostream& operator<<(ostream& out, const graph<type>& g) {
	auto temp = g.front;
	auto start = high_resolution_clock::now();
	while (temp != nullptr) {
		out << temp->data << " ";
		temp = temp->next;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	out << endl << "Executed in " << duration.count() << " microseconds" << endl;

	out << "Chapter headings: ";
	start = high_resolution_clock::now();
	for (int i = 0; i < floor(g.size / g.subDivSize); i++) {
		out << g.root[i]->data << " ";
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	out << endl << "Executed in " << duration.count() << " microseconds" << endl;

	return out;
}
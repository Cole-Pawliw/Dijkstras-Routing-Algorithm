#include "city.h"
#include <vector>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;
using std::vector;

edge::edge() {
	vertices[0] = nullptr;
	vertices[1] = nullptr;
	length = -1;
}

edge::edge(City& first, City& second, int len) {
	vertices[0] = &first;
	vertices[1] = &second;
	length = len;
}

edge::edge(const edge& src) {
	vertices[0] = src.vertices[0];
	vertices[1] = src.vertices[1];
	length = src.length;
}

edge& edge::operator= (const edge& rhs) {
	struct edge *clone = new edge();
	clone->vertices[0] = rhs.vertices[0];
	clone->vertices[1] = rhs.vertices[1];
	clone->length = rhs.length;

	return *clone;
}

others::others() {
	location = nullptr;
	distance = -1;
	hops = -1;
}

others::others(City& place, int dis, int jumps) {
	location = &place;
	distance = dis;
	hops = jumps;
}

others::others(const others& src) {
	location = src.location;
	distance = src.distance;
	hops = src.hops;
	path = src.path;
}

others& others::operator= (const others& rhs) {
	struct others *clone = new others();
	clone->location = rhs.location;
	clone->distance = rhs.distance;
	clone->hops = rhs.hops;
	clone->path = rhs.path;

	return *clone;
}

City::City() {
	for (int i = 0; i < 3; i++) {
		code[i] = 0;
	}
}

City::City(const char *name) {
	complete_list.reserve(100);
	for (int i = 0; i < 3; i++) {
		code[i] = name[i];
	}
}

City::City(City& src) {
	for (int i = 0; i < 3; i++) {
		code[i] = src.getCode()[i];
	}
	for (int i = 0; i < (int)src.get_connections().size(); i++) {
		connections.push_back(src.get_connections()[i]);
	}
	for (int i = 0; i < (int)src.get_list().size(); i++) {
		complete_list.push_back(src.get_list()[i]);
	}
}

City& City::operator= (City& rhs) {
	City *clone = new City();
	for (int i = 0; i < 3; i++) {
		clone->code[i] = rhs.getCode()[i];
	}
	for (int i = 0; i < (int)rhs.get_connections().size(); i++) {
		clone->connections.push_back(rhs.get_connections()[i]);
	}
	for (int i = 0; i < (int)rhs.get_list().size(); i++) {
		clone->complete_list.push_back(rhs.get_list()[i]);
	}

	return *clone;
}

char* City::getCode() {
	return code;
}

void City::add_connection(struct edge& to_add) {
	connections.push_back(&to_add);
}

void City::find_others() {
	vector<struct others*> unused;
	unused.reserve(100);
	struct others *to_add = new others(*this, 0, 0);
	to_add->path = "YYC";
	unused.push_back(to_add);


	while (unused.size()) {
		int current = 0;

		//Select the city in unused with the shortest distance
		for (int i = 0; i < (int)unused.size(); i++) {
			if (unused[i]->distance < unused[current]->distance) {
				current = i;
			}
		}

		//Find lowest distances between current unused and the shortest distance connections
		for (int i = 0; i < (int)unused[current]->location->connections.size(); i++) {
			int skip = 0, vertex;
			//Finds the right index of vertices to use
			if (strcmp(unused[current]->location->connections[i]->vertices[0]->getCode(),
					unused[current]->location->getCode()) == 0) {
				vertex = 1;
			} else {
				vertex = 0;
			}

			//Checks if the current connection has already been added to complete_list
			for (int j = 0; j < (int)complete_list.size(); j++) {

				if (strcmp(unused[current]->location->connections[i]->vertices[vertex]->getCode(),
						complete_list[j]->location->getCode()) == 0) {
					skip = 1;
				}
			}

			//Skips the current iteration if the connection isn't needed
			if (skip) {continue;}

			//Finding if the connection has been found before, and updating the distance if the new one is shorter
			for (int j = 0; j < (int)unused.size(); j++) {
				if (strcmp(unused[j]->location->getCode(),
						unused[current]->location->connections[i]->vertices[vertex]->getCode()) == 0) {
					if (unused[current]->location->connections[i]->length + unused[current]->distance < unused[j]->distance) {
						unused[j]->distance = unused[current]->location->connections[i]->length + unused[current]->distance;
						unused[j]->hops = unused[current]->hops + 1;
						unused[j]->path = unused[current]->path + "-->" + unused[j]->location->getCode();
					}
					skip = 1;
					break;
				}
			}
			if (skip) {continue;}

			//In the last case, if the city does not exist in the list, add it to the list with the current foudn distance
			to_add = new others(*(unused[current]->location->connections[i]->vertices[vertex]),
					unused[current]->location->connections[i]->length + unused[current]->distance,
					unused[current]->hops + 1);

			to_add->path = unused[current]->path + "-->" + to_add->location->getCode();

			unused.push_back(to_add);
		}

		complete_list.push_back(unused[current]);
		unused.erase(unused.begin() + current);
	}
}

vector<struct others*> City::get_list() {
	return complete_list;
}

vector<struct edge*> City::get_connections() {
	return connections;
}

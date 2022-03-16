#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include "city.h"

using namespace std;
using std::vector;

int main(void) {
	string src, dest, filename;
	int dist;
	vector<City*> cities;
	vector<struct edge*> edges;

	cout << "Enter the name of the map file:" << endl;
	cin >> filename;

	ifstream file(filename);

	while (file >> src >> dest >> dist) {
		City *tomatoTown = nullptr, *tiltedTowers = nullptr;
		struct edge *bridge;
		for (int i = 0; i < (int)cities.size(); i++) {
			if (strcmp(cities[i]->getCode(), src.c_str()) == 0) {
				tomatoTown = cities[i];
			}
			if (strcmp(cities[i]->getCode(), dest.c_str()) == 0) {
				tiltedTowers = cities[i];
			}
		}

		if (tomatoTown == nullptr) {
			tomatoTown = new City(src.c_str());
			cities.push_back(tomatoTown);
		}
		if (tiltedTowers == nullptr) {
			tiltedTowers = new City(dest.c_str());
			cities.push_back(tiltedTowers);
		}

		bridge = new edge(*tomatoTown, *tiltedTowers, dist);
		edges.push_back(bridge);

		tomatoTown->City::add_connection(*bridge);
		tiltedTowers->City::add_connection(*bridge);
	}

	City *calgary;
	for (int i = 0; i < (int)cities.size(); i++) {
		if (strcasecmp(cities[i]->getCode(), "YYC") == 0) {
			calgary = cities[i];
			break;
		}
	}

	calgary -> find_others();
	vector<struct others*> calgary_dist = calgary->get_list();

	cout << "Destination Cost Hops Shortest Path" << endl;
	for (int i = 0; i < (int)calgary_dist.size(); i++) {
		cout << calgary_dist[i]->location->getCode() << "         "
			<< calgary_dist[i]->distance << "   "
			<< calgary_dist[i]->hops << "     "
			<< calgary_dist[i]->path << endl << endl;
	}

	return 0;
}


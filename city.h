#include <string>
#include <vector>

#ifndef CITY_H
#define CITY_H

using std::vector;
using std::string;

class City;

struct edge {
	City* vertices[2];
	int length;
	edge();
	edge(City& first, City& second, int len);
	edge(const edge& src);
	edge& operator= (const edge& rhs);
};

struct others {
	City *location;
	int distance, hops;
	others(City& place, int dis, int jumps);
	string path;

	others();
	others(const others& src);
	others& operator= (const others& rhs);
};

class City {
private:
	char code[3];
	vector<struct edge*> connections;
	vector<struct others*> complete_list;
public:
	City();
	City(const char *name);
	City(City& src);
	City& operator= (City& rhs);

	char* getCode();
	void add_connection(struct edge& to_add);
	void find_others();
	vector<struct others*> get_list();
	vector<struct edge*> get_connections();
};

#endif

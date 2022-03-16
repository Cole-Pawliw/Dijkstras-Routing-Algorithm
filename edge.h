#include "city.h"

#ifndef EDGE_H
#define EDGE_H

class Edge {
private:
	City vertices[2];
	int length;
public:
	Edge() {}
	Edge(City& one, City& two, int len): vertices[0](one), vertices[1](two), length(len);

	void setFirst(City& src);
	void setSecond(City& src);
	void setLength(int l);

	City& getFirst();
	City& getSecond();
	int getLength();
};

#endif

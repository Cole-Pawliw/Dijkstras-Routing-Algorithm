#include "edge.h"
#include "city.h"

void Edge::setFirst(City& src) {
	first = src;
}

void Edge::setSecond(City& src) {
	second = src;
}

void Edge::setLength(int l) {
	length = l;
}

City& Edge::getFirst() {
	return ;
}

City& Edge::getSecond() {
	return second;
}

int Edge::getLength() {
	return length;
}

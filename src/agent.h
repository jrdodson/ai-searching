#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <functional>
#include "searcher.h"
#include "informed.h"
#include "uninformed.h"
#include <string>

#define DEPTH 'd'
#define BREADTH 'b'
#define UNIFORM 'u'
#define GREEDY 'g'
#define ASTAR 'a'

//represents an intelligent agent
class agent {
public:
	agent() {}
	~agent();
	void error();
	bool search(Node*, Node*, char);
	Node* findNode(std::string);
	void makeMap(char*);
	void printMap();
private:
	Searcher* searcher;
	std::vector<Node*>Map;
};

#endif

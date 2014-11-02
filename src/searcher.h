#ifndef SEARCHER_H
#define SEARCHER_H

#include "node.h"
#include <set>
#include <vector>
#include <iostream>

class Searcher {
public:
	Searcher(){};
	
	Node* findNode(std::string n, std::vector<Node*> map) {
		std::vector<Node*>::iterator it;
		Node* temp = new Node();
		for(it = map.begin(); it!= map.end(); it++) {
			temp = *it;
			if(temp->name == n) {
				return temp;
			}
		}
	}	

	void traceback(Node* n) {
		if(n->parent) {
			traceback(n->parent);
		}
		std::cout << n->name << " ";
	}
	
	virtual bool search(Node*, Node*, std::vector<Node*>) = 0;

protected:
	std::set<Node*> explored;

};

#endif

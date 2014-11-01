#include "uninformed.h"

using namespace std;

/*Depth First Implementation */

DepthFirstSearcher::~DepthFirstSearcher() {
	while(!stk.empty()) {
		Node* temp = stk.top();
		stk.pop();
		delete temp;
	}
}

bool DepthFirstSearcher::search(Node* source, Node* dest, std::vector<Node*>map) {
	Node* current = source;
	Node* temp = new Node();

	stk.push(current);
	while(!stk.empty()) {
		current=stk.top();
		stk.pop();
		if(*current == *dest) {
			traceback(current);
			cout << endl;
			delete temp, current;
			return true;
		}
		if(explored.find(current) == explored.end()) {explored.insert(current);}
		std::vector<Link>::iterator nit;
		for(nit=current->neighborList.begin(); nit!=current->neighborList.end(); nit++) {
			temp = findNode(nit->name, map);
			if(explored.find(temp)==explored.end()) {
				temp->parent = current;
				stk.push(temp);
			}
		}
	}
	return false;
}

/* Breadth First Implementation */

BreadthFirstSearcher::~BreadthFirstSearcher() {
	while(!que.empty()) {
		Node* temp = que.front();
		que.pop();
		delete temp;
	}
}

bool BreadthFirstSearcher::search(Node* source, Node* dest, std::vector<Node*>map) {
	Node* current = source;
	Node* temp = new Node();

	que.push(current);
	while(!que.empty()) {
		current=que.front();
		que.pop();
		if(*current == *dest) {
			traceback(current);
			cout << endl;
			delete temp, current;
			return true;
		}
		if(explored.find(current) == explored.end()) {explored.insert(current);}
		std::vector<Link>::iterator nit;
		for(nit=current->neighborList.begin(); nit!=current->neighborList.end(); nit++) {
			temp = findNode(nit->name, map);
			if(explored.find(temp)==explored.end()) {
				temp->parent = current;
				que.push(temp);
			}
		}
	}
	return false;
}


/* Uniform Cost Implementation & helpers */

UniformCostSearcher::~UniformCostSearcher() {
	multiset<Node*, GComparator>::iterator it;
	for(it = gset.begin(); it!= gset.end(); it++) {
		Node* temp = *it;
		delete temp;
	}
}

Node* UniformCostSearcher::popSet() {
	multiset<Node*, GComparator>::iterator it;
	it = gset.begin();
	return *it;
}

bool UniformCostSearcher::compareMultisetNodes(Node* n) {
	multiset<Node*, GComparator>::iterator it = gset.find(n);
	Node* temp = (it == gset.end() ? NULL : *it);
	if(temp && temp->getG() < n->getG()) {
		gset.erase(it);
		return true;
	}
	return false;
}

bool UniformCostSearcher::search(Node* source, Node* dest, std::vector<Node*>map) {
	Node* current = source;
	Node* temp = new Node();

	gset.insert(current);

	while(!gset.empty()) {
		current = popSet();
		gset.erase(gset.begin());

		if(*current == *dest) {
			traceback(current);
			cout << endl;
			delete temp, current;
			return true;
		}

		if(explored.find(current) == explored.end()) {explored.insert(current);}
		std::vector<Link>::iterator nit;
		for(nit=current->neighborList.begin(); nit!=current->neighborList.end(); nit++) {
			temp = findNode(nit->name, map); //grab node
			
			//be sure to copy values to new node if node 
			// already exists - prevent heap corruption
			if(gset.find(temp) != gset.end()) {
				temp = new Node();
				*temp = *findNode(nit->name, map);
			}

			temp->setG(nit->cost+current->getG()); //set g() to new value

			if(explored.find(temp)==explored.end()) {
				temp->parent = current;
				gset.insert(temp);
			}
			else if(compareMultisetNodes(temp)) {
				temp->parent = current;
				gset.insert(temp);
			}
		}
	}
	return false;
}
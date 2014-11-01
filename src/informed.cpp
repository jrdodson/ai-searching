#include "informed.h"
using namespace std;

GreedySearcher::~GreedySearcher() {
	while(!hpq.empty()) {
		hpq.pop();
	}
}

bool GreedySearcher::search(Node* source, Node* dest, vector<Node*> map) {
	Node* current = new Node();
	Node* temp = new Node();
	current = source;
	hpq.push(current);
	
	while(!hpq.empty()) {
		current = hpq.top();
		hpq.pop();

		//check to see if we've made it
		if(*current == *dest) {
			traceback(current);
			cout << endl;
			delete temp, current;
			return true;
		}

		//else mark as explored and expand
		explored.insert(current);
		std::vector<Link>::iterator nit;
		for(nit=current->neighborList.begin(); nit!=current->neighborList.end(); nit++) {
			temp = findNode(nit->name, map);

			//if we haven't been here yet, update our G and F values
			if(temp && explored.find(temp) == explored.end()) {
				temp->parent = current;
				hpq.push(temp);
			}
		}
	}
	return false;
}


AStarSearcher::~AStarSearcher() {
	while(!fpq.empty()) {
		fpq.pop();
	}
}

//iterate through set and compare values
bool AStarSearcher::findOnSet(Node* n) {
	Node* found = new Node();
	set<Node*>::iterator it = explored.find(n);
	if(it != explored.end()) {
		found = *it;
		return found->getF() <= n->getF();
	}
	return false;
}

//clone our queue and dequeue our clone and compare values
// return true if current node is better than candidate
bool AStarSearcher::findOnQueue(Node* n) {
	priority_queue<Node*, vector<Node*>, FComparator> clone = fpq;
	Node* found = new Node();
	while(!clone.empty()) {
		found = clone.top();
		clone.pop();
		if(found->name == n->name &&
			(found->getF() <= n->getF() || found->getG() <= n->getG())) {
			return true;
		}
	}
	return false;
}

bool AStarSearcher::search(Node* source, Node* dest, std::vector<Node*>map) {
	//initial setup, etc.
	Node* current = new Node();
	Node* temp = new Node();

	current = source;
	current->setG(0);
	current->setF();

	fpq.push(current);

	while(!fpq.empty()) {
		//pop off our pq based on our f()
		current = fpq.top();
		fpq.pop();

		//check to see if we've made it
		if(*current == *dest) {
			traceback(current);
			cout << endl;
			delete temp, current;
			return true;
		}
		//else mark as explored and expand
		explored.insert(current);
		std::vector<Link>::iterator nit;
		for(nit=current->neighborList.begin(); nit!=current->neighborList.end(); nit++) {
			temp = findNode(nit->name, map);

			//check to see if we already have this node in our queue
			// altering values of items already in the queue causes a heap corruption
			// quick workaround is to make a copy
			if(findOnQueue(temp)) {
				temp = new Node();
				*temp = *findNode(nit->name, map);
			}
			
			//if we haven't been here yet, update our G and F values
			if(temp && explored.find(temp) == explored.end()) {
				temp->parent = current; //set parent
				temp->setG(nit->cost + current->getG()); //make our g() the sum of the unit cost + current g()
				temp->setF(); //update f() explicitly 

				//look for duplicates and make sure this node is better than its previous appearances 
				if(findOnSet(temp) || findOnQueue(temp)) {
					continue; //if not better, disregard
				}
				//if it is better, add it
				else {fpq.push(temp);}
			}
		}
	}
	return false;
}

#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

//represents a state for any given node
class State {
public:
	State() : h(0), g(0) {};
	State(int hval) : h(hval), g(0) {}
	int h;
	int g;
	State& operator=(State& s) {
		this->h = s.h;
		this->g = s.g;
		return *this;
	}
};

//represents a link between nodes based 
//on neighbor name and cost to neighbor
struct Link {
	std::string name;
	int cost;
};

//Encapuslates node data for each searcher
class Node {
public:
	Node() : f(0), parent(NULL) {}
	Node(std::string n, int hval) : f(0), name(n), state(hval), parent(NULL) {}
	
	//helpful operators
	bool operator==(Node& n) {return this->name==n.name;}
	Node& operator=(Node& n) {
		this->f = n.getF();
		this->state = n.state;
		this->name = n.name;
		this->parent = n.parent;
		this->neighborList =n.neighborList;
		return *this;
	}

	//cost helper functions
	int getG() {return state.g;}
	int getF() {return f;}
	int getH() {return state.h;}
	void setG(int gval) {state.g = gval;}
	void setF() {f=state.g+state.h;}

	//other necessary properties
	std::string name;
	std::vector<Link> neighborList;
	Node* parent;
private:
	State state;
	int f;
};


//a few functors for f(), g(), and g(), respectively
class FComparator {
public:
	bool operator()(Node* n1, Node* n2) {
		return (n1->getF() > n2->getF());
	}
};
class GComparator {
public:
	bool operator()(Node* n1, Node* n2) {
		return(n1->getG() < n2->getG());
	}
};
class HComparator {
public:
	bool operator()(Node* n1, Node* n2) {
		return(n1->getH() < n2->getH());
	}
};

#endif
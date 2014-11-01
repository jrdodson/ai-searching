#include "agent.h"
using namespace std;

bool agent::search(Node* source, Node* dest, char flag) {
	//cout << flag << endl;	
	switch(flag) {
	case DEPTH: searcher = new DepthFirstSearcher(); break;
	case BREADTH: searcher = new BreadthFirstSearcher(); break;
	case UNIFORM: searcher = new UniformCostSearcher(); break;
	case GREEDY: searcher = new GreedySearcher(); break;
	case ASTAR: searcher = new AStarSearcher(); break;
	default: error();
	};

	return searcher->search(source, dest, Map);
}

//in case our flag is invalid
void agent::error() {
	cout << "Invalid input" << endl;
	exit(1);
}

//cleanup
agent::~agent() {
	delete searcher;
}	

//for debugging, etc.
void agent::printMap() {
	vector<Node*>::iterator it;
	Node* node = new Node();
	for(it = Map.begin(); it != Map.end(); it++) {
		node = *it;
		cout << node->name << " -> ";
		vector<Link>::iterator lit;
		for(lit = node->neighborList.begin(); lit != node->neighborList.end(); lit++) {
			cout << lit->name << " (" << lit->cost <<") ";
		}
		cout << endl;
	}
}

//add cities to our map
// with an ugly parsing function
// <City> <Heuristic> <Neighbor> <Cost> <Neighbor> <Cost> ...  
void agent::makeMap(char* argv) {
	ifstream in(argv);
	if(in.fail()) {error();}
	string stemp;
	int itemp;

	while(!in.eof()) {
		string line;
		getline(in, line);
		stringstream ss(line);
		ss >> stemp; ss >> itemp;
		Node* node = new Node(stemp, itemp);
		while(ss >> stemp && ss >> itemp) {
			Link link;
			link.name = stemp; link.cost = itemp;
			node->neighborList.push_back(link);
		}
		Map.push_back(node);
	}
}

Node* agent::findNode(std::string n) {
	std::vector<Node*>::iterator it;
	Node* temp = new Node();
	for(it = Map.begin(); it!= Map.end(); it++) {
		temp = *it;
		if(temp->name == n) {
			return temp;
		}
	}
}

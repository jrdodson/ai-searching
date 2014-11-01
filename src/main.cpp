#include "agent.h"
#include <cstdlib>
#include <string>

using namespace std;

void error() {
	cout << "usage: <program> <file> <search>\nplease input valid file\n"
		<< "d (depth) b (breadth) u (uniform cost) g (greedy) a (astar)\n";
	exit(1);
}

int main(int argc, char** argv) {
	agent a;	
	if(argc != 3) {error();}
	a.makeMap(argv[1]);
	a.printMap(); cout << endl << endl;
	Node* source = a.findNode("Arad");
	Node* dest = a.findNode("Bucharest");
	a.search(source, dest, *argv[2]);
	return 0;
}

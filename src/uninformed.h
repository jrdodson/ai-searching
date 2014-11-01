#include "searcher.h"
#include <stack>
#include <queue>

/* Uninformed Searches */
/* Inherits from base class Searcher */

class DepthFirstSearcher : public Searcher {
public:
	DepthFirstSearcher() : Searcher() {}
	~DepthFirstSearcher();
	bool search(Node*, Node*, std::vector<Node*>);
private:
	std::stack<Node*>stk;
};

class BreadthFirstSearcher : public Searcher {
public:
	BreadthFirstSearcher() : Searcher() {}
	~BreadthFirstSearcher();
	bool search(Node*, Node*, std::vector<Node*>);
private:
	std::queue<Node*>que;
};

class UniformCostSearcher : public Searcher {
public:
	UniformCostSearcher() : Searcher() {}
	~UniformCostSearcher();
	bool search(Node*, Node*, std::vector<Node*>);
private:
	bool compareMultisetNodes(Node*);
	Node* popSet();
	std::multiset<Node*, GComparator>gset;
};
#include "searcher.h"
#include <queue>
#include <vector>

/* Informed Searches */
/* Inherits from base class Searcher */

class AStarSearcher : public Searcher{
public:
	AStarSearcher() : Searcher() {};
	~AStarSearcher();
	bool search(Node*, Node*, std::vector<Node*>);
private:
	bool findOnSet(Node*);
	bool findOnQueue(Node*);
	std::priority_queue<Node*, std::vector<Node*>, FComparator> fpq;
};

class GreedySearcher : public Searcher {
public:
	GreedySearcher() : Searcher() {};
	~GreedySearcher();
	bool search(Node*, Node*, std::vector<Node*>);
private:
	std::priority_queue<Node*, std::vector<Node*>, HComparator> hpq;
};
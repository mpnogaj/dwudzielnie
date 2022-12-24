#include <map>
#include <set>
#include <ostream>
#pragma once

using namespace std;

class Graph
{
private:
	map<int, set<int>> mEdges;
	map<int, bool> mColors;
public:
	Graph();
	~Graph();
	void AddEdge(int a, int b);
	bool IsBigraph();
	void PrintGraph(ostream& outputStream);
	void PrintSets(ostream& outputStream);
};
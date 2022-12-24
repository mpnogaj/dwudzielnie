#include "graph.h"
#include <queue>

Graph::Graph()
{
	this->mEdges = map<int, set<int>>();
	this->mColors = map<int, bool>();
}

Graph::~Graph()
{
	this->mEdges.clear();
	this->mColors.clear();
}

void Graph::AddEdge(int a, int b)
{
	this->mEdges[a].insert(b);
	this->mEdges[b].insert(a);
}

bool Graph::IsBigraph()
{
	queue<int> q;
	this->mColors.clear();
	for (const auto &[vertex, _] : this->mEdges)
	{
		if (this->mColors.count(vertex) != 0)
			continue;
		this->mColors[vertex] = true;
		q.push(vertex);
		while (!q.empty())
		{
			const int &p = q.front();
			bool nextColor = !this->mColors[p];
			for (const int &x : this->mEdges[p])
			{
				if (this->mColors.count(x) != 0)
				{
					if (this->mColors[x] != nextColor)
					{
						this->mColors.clear();
						return false;
					}
					continue;
				}
				this->mColors[x] = nextColor;
				q.push(x);
			}
			q.pop();
		}
	}
	return true;
}

void Graph::PrintGraph(ostream &outputStream)
{
	for (const auto &[vertex, edges] : this->mEdges)
	{
		outputStream << vertex << ":";
		for (const int &x : edges)
			outputStream << " " << x;
		outputStream << endl;
	}
}

void Graph::PrintSets(ostream &outputStream)
{
	outputStream << "Grupa 1:";
	for (const auto &[vertex, color] : this->mColors)
		if (color)
			outputStream << " " << vertex;
	outputStream << endl
				 << "Grupa 2:";
	for (const auto &[vertex, color] : this->mColors)
		if (!color)
			outputStream << " " << vertex;
	outputStream << endl;
}

#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <deque>

// define
#define VERTEX_MAX_SIZE 20000
#define EDGE_MAX_SIZE 300000

#define debug_m 1

// struct
struct NODE
{
	int u, v, w;
};

struct WEIGHT
{
	WEIGHT()
		: v(0)
		, w(INT_MAX)
	{
		
	}
	int v, w;
};

struct PqCmp
{
	bool operator()(WEIGHT a, WEIGHT b)
	{
		if (a.w > b.w)
			return true;
		else
			return false;
	}
};

// global
int distArr[VERTEX_MAX_SIZE + 2] = { 0, };

// mehtod
void CalcuateDijkstra(std::vector<std::vector<NODE>>& src, int startV, int endV);

int main()
{
	//init
	std::ios::sync_with_stdio(false);

	// input
	int Vcnt = 0; // vertext
	int Ecnt = 0; // edge
	int startV = 0;
	(void)scanf("%d %d %d", &Vcnt, &Ecnt, &startV);

	std::vector<std::vector<NODE>> inputLists;
	inputLists.resize(Vcnt + 1);
	for (int e = 0; e < Ecnt; e++)
	{
		NODE inputNode;
		(void)scanf("%d %d %d", &inputNode.u, &inputNode.v, &inputNode.w);
		inputLists[inputNode.u].push_back(inputNode);
	}

	for (int v = 1; v <= Vcnt; v++)
		distArr[v] = INT_MAX;

	// calc
	CalcuateDijkstra(inputLists, startV, Vcnt);

	// print
	for (int i = 1; i <= Vcnt; i++)
	{
		if (INT_MAX == distArr[i])
			printf("INF\n");
		else
			printf("%d\n", distArr[i]);
	}

	return 0;
}

void CalcuateDijkstra(std::vector<std::vector<NODE>>& src, int startV, int endV)
{
	std::priority_queue<WEIGHT, std::vector<WEIGHT>, PqCmp> priQue;

	// init
	for (int i = 1; i <= endV; i++)
	{
		WEIGHT Vinfo;
		Vinfo.v = i;

		if (i == startV)
		{
			Vinfo.w = 0;
			distArr[i] = 0;
		}

		priQue.push(Vinfo);
	}
	
	// calc
	int calcCnt = 0;
	while (!priQue.empty())
	{
		WEIGHT curV = priQue.top();
		priQue.pop();
		calcCnt++;

		if (INT_MAX == curV.w)
			break;
		
		std::vector<NODE> curNode = src[curV.v];
		for (int i = 0; i < curNode.size(); i++)
		{
			NODE adjNode = curNode[i];
			if (distArr[adjNode.v] > (adjNode.w + distArr[curV.v]))
			{
				distArr[adjNode.v] = adjNode.w + distArr[curV.v];
		
				WEIGHT info;
				info.v = adjNode.v;
				info.w = distArr[adjNode.v];
				priQue.push(info);
			}
		}
	}
}
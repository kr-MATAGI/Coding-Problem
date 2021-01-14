#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>

//max size
#define N_MAX_SIZE 800
#define E_MAX_SIZE 200000
#define C_MAX_SIZE 1000
#define MUST_VERTEX_SIZE 2

//debug
#define debug_m 0

// struct
struct NODE
{
	NODE()
		: to(0)
		, dist(INT_MAX)
	{
	}

	int to;
	int dist;
};

struct WEIGHT
{
	WEIGHT()
		: v(0)
		, w(INT_MAX)
	{

	}

	bool operator()(WEIGHT a, WEIGHT b)
	{
		if (a.w > b.w)
			return true;
		else
			return false;
	}

	int v, w;
};

// global
int distArr[N_MAX_SIZE + 1];

// method
int CalcDijkstra(std::vector<std::vector<NODE>>& src, const int mustVertex[], const int NCnt, const int ECnt);

int main()
{
	/// init
	std::ios::sync_with_stdio(false);
	for (int i = 0; i < N_MAX_SIZE + 1; i++)
	{
		distArr[i] = INT_MAX;
	}

	/// input
	int N = 0; // 정점의 개수
	int E = 0; // 간선의 개수
	(void)scanf("%d %d", &N, &E);

	std::vector<std::vector<NODE>> inputLists;
	inputLists.resize(N + 1);
	for (int e = 0; e < E; e++)
	{
		NODE input;
		int from = 0;
		(void)scanf("%d %d %d", &from, &input.to, &input.dist);
		inputLists[from].push_back(input);

		// 양방향
		NODE another;
		another.to = from;
		another.dist = input.dist;
		inputLists[input.to].push_back(another);
	}

	/// 반드시 거쳐야 하는 두 개의 서로 다른 정점
	int mustVertex[MUST_VERTEX_SIZE] = { 0, };
	(void)scanf("%d %d", &mustVertex[0], &mustVertex[1]);

	/// Dijkstra Function
	const int answer_1 = CalcDijkstra(inputLists, mustVertex, N, E);

	int temp = mustVertex[0];
	mustVertex[0] = mustVertex[1];
	mustVertex[1] = temp;
	const int answer_2 = CalcDijkstra(inputLists, mustVertex, N, E);
	const int finalAns = answer_1 < answer_2 ? answer_1 : answer_2;

	/// print answer
	if (INT_MAX == distArr[N] || INT_MAX == finalAns)
		printf("-1\n");
	else
		printf("%d\n", finalAns);

	return 0;
}

/// Method
int CalcDijkstra(std::vector<std::vector<NODE>>& src, const int mustVertex[], const int NCnt, const int ECnt)
{
#if debug_m
	printf("\n-----[%s] ----- \n", __FUNCTION__);
#endif
	int retValue = 0;

	/*
	* 1 -> mustVertex[0]
	* mustVertex[0] -> mustVertex[1]
	* mustVertex[1] -> NCnt
	*/
	std::vector<int> startList;
	startList.push_back(1);
	startList.push_back(mustVertex[0]);
	startList.push_back(mustVertex[1]);
	startList.push_back(NCnt); // end vertex

	for (int s = 0; s < startList.size() - 1; s++)
	{
		std::priority_queue<WEIGHT, std::vector<WEIGHT>, WEIGHT> priQue;
		int startV = startList[s];
		int endV = startList[s + 1];
#if debug_m
		printf("--startV : %d, endV : %d \n", startV, endV);
#endif

		// init
		for (int i = 0; i <= NCnt; i++)
		{
			distArr[i] = INT_MAX;
		}

		for (int i = 1; i <= NCnt; i++)
		{
			WEIGHT vertex;
			vertex.v = i;

			if (i == startV)
			{
				vertex.w = 0;
				distArr[i] = 0;
			}

			priQue.push(vertex);
		}

		// calc
		while (!priQue.empty())
		{
			WEIGHT curVertex = priQue.top();
			priQue.pop();

			if (INT_MAX == curVertex.w)
				break;

			std::vector<NODE> curVertexInfo = src[curVertex.v];
			std::vector<NODE>::const_iterator iter;
			for (iter = curVertexInfo.begin(); iter != curVertexInfo.end(); ++iter)
			{
				NODE node = *iter;
				if (distArr[node.to] > (node.dist + distArr[curVertex.v]))
				{
					distArr[node.to] = node.dist + distArr[curVertex.v];

					WEIGHT pushInfo;
					pushInfo.v = node.to;
					pushInfo.w = distArr[node.to];
					priQue.push(pushInfo);
				}
			}
		}

		retValue += distArr[endV];
#if debug_m
		printf(">> distArr[endV] : %d, retValue : %d \n", distArr[endV], retValue);
#endif
	}

	return retValue;
}
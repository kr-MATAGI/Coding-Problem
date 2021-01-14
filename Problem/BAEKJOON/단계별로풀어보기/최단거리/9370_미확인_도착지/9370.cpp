#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
#include <algorithm>

// max size
#define TEST_CASE_MAX 100
#define N_MAX_SIZE 2000
#define M_MAX_SIZE 50000
#define T_MAX_SIZE 100

// debug
#define debug_m 0

// struct
struct NODE
{
	NODE(int _ver = 0, int _dis = INT_MAX)
		: vertex(_ver)
		, dist(_dis)
	{

	}

	inline bool operator() (NODE a, NODE b)
	{
		if (a.dist > b.dist)
			return true;
		else
			return false;
	}

	int vertex, dist;
};

// global
int distArr[N_MAX_SIZE + 1];

// method
int DijkstraFuc(std::vector<std::vector<NODE>>& src, int NCnt, int ECnt, int S /*출발지*/, int E /*목적지*/);

int main()
{
	// init
	std::ios::sync_with_stdio(false);

	// input
	int testCase = 0;
	(void)scanf("%d", &testCase);

	std::vector<std::vector<int>> printList;
	for (int test = 0; test < testCase; test++)
	{
		int N, M, T; // 교차로, 도로, 목적지 후보의 개수
		(void)scanf("%d %d %d", &N, &M, &T);

		int S, G, H; // 출발지, g와 h 교차로 사이에 있는 도로
		(void)scanf("%d %d %d", &S, &G, &H);

		std::vector<std::vector<NODE>> inputLists;
		inputLists.resize(N + 1);
		for (int m = 0; m < M; m++)
		{
			int from, to, dist;
			(void)scanf("%d %d %d", &from, &to, &dist);

			// from -> to
			NODE f2t(to, dist);
			inputLists[from].push_back(f2t);

			// to -> from
			NODE t2f(from, dist);
			inputLists[to].push_back(t2f);
		}

		std::vector<int> destCandi;
		for (int t = 0; t < T; t++)
		{
			int x = 0; // 목적지 후보
			(void)scanf("%d", &x);
			destCandi.push_back(x);
		}

		// calc
		std::vector<int> tcAns;
		for (int dest : destCandi)
		{
			// 시작점에서 목적지까지 최단거리
			const int compare = DijkstraFuc(inputLists, N, M, S, dest);
			if (INT_MAX == compare)
				continue;

			int StoG = DijkstraFuc(inputLists, N, M, S, G);
			int StoH = DijkstraFuc(inputLists, N, M, S, H);

			int answer = 0;
			if (StoG < StoH)
			{
				answer = StoG;
				answer += DijkstraFuc(inputLists, N, M, G, H);
				answer += DijkstraFuc(inputLists, N, M, H, dest);
			}
			else
			{
				answer = StoH;
				answer += DijkstraFuc(inputLists, N, M, H, G);
				answer += DijkstraFuc(inputLists, N, M, G, dest);
			}

#if debug_m
			printf("dest : %d\nans_1 : %d\nans_2 : %d\ncompare : %d\n", dest, answer_1, answer_2, compare);
#endif
			if (answer <= compare && INT_MAX != compare)
				tcAns.push_back(dest);
		}
		std::sort(tcAns.begin(), tcAns.end());
		printList.push_back(tcAns);
	}

	// print
	for (auto print : printList)
	{
		for (int data : print)
		{
			printf("%d ", data);
		}
		printf("\n");
	}

	return 0;
}

/// Method
int DijkstraFuc(std::vector<std::vector<NODE>>& src, int NCnt, int ECnt, int S /*출발지*/, int E /*목적지*/)
{
	int retValue = 0;

	// init
	std::priority_queue<NODE, std::vector<NODE>, NODE> priQue;
	for (int i = 1; i <= NCnt; i++)
	{
		NODE node(i);
		distArr[i] = INT_MAX;

		if (i == S)
		{
			node.dist = 0;
			distArr[i] = 0;
		}

		priQue.push(node);
	}

	// calc
	while (!priQue.empty())
	{
		NODE cur = priQue.top();
		priQue.pop();

		if (INT_MAX == cur.dist)
			break;

		std::vector<NODE> curVertexInfo = src[cur.vertex];
		std::vector<NODE>::const_iterator iter;
		for (iter = curVertexInfo.begin(); iter != curVertexInfo.end(); ++iter)
		{
			NODE node = *iter;
			if (distArr[node.vertex] > (node.dist + distArr[cur.vertex]))
			{
				distArr[node.vertex] = node.dist + distArr[cur.vertex];

				NODE pushInfo;
				pushInfo.vertex = node.vertex;
				pushInfo.dist = distArr[node.vertex];
				priQue.push(pushInfo);
			}
		}
	}

	retValue += distArr[E];

	return retValue;
}
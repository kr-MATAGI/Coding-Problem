#include <iostream>
#include <vector>
#include <limits.h>

// max size
#define N_MAX_SIZE 500
#define M_MAX_SIZE 6000
#define W_MIN_VAL -10000
#define W_MAX_VAL 10000

// def
#define START_CITY 1
#define debug_m 1

// struct
struct NODE
{
	NODE(int _v = 0, int _w = INT_MAX)
		: v(_v)
		, w(_w)
	{

	}

	bool operator() (NODE lhs, NODE rhs)
	{
		if (lhs.w > rhs.w)
			return true;
		else
			return false;
	}

	int v, w;
};

// global
int distArr[N_MAX_SIZE + 1];

// method
int BellmanFordFunction(std::vector<std::vector<NODE>> src, int VCnt, int ECnt);

int main()
{
	// init
	std::ios::sync_with_stdio(false);

	// input
	int N = 0; // 도시의 개수(정점)
	int M = 0; // 버스 노선의 개수 (간선)
	(void)scanf("%d %d", &N, &M);

	std::vector<std::vector<NODE>> inputLists;
	inputLists.resize(N + 1);
	for (int m = 0; m < M; m++)
	{
		/**
		* 입력 c가 양수가 아닌 경우
		* c == 0 : 순간 이동
		* c < 0 : 타임 머신으로 시간을 돌아가는 경우
		*/
		int from, to, weight;
		from = to = weight = 0;
		(void)scanf("%d %d %d", &from, &to, &weight);

		NODE input(to, weight);
		inputLists[from].push_back(input);
	}

	// Bellman Ford
	BellmanFordFunction(inputLists, N, M);

	// print
	

	return 0;
}

/// METHOD
int BellmanFordFunction(std::vector<std::vector<NODE>> src, int VCnt, int ECnt)
{
	int retValue = -1;

	// init
	for (int i = 1; i <= VCnt; i++)
	{
		NODE initNode(i);

		if (i == START_CITY)
		{
			initNode.w = 0;
			distArr[START_CITY] = 0;
		}
	}

	// calc
	for (int city = 1; city <= VCnt; city++)
	{
		std::vector<NODE> cityInfo = src[city];
		for (NODE& adjCity : cityInfo)
		{
			if (distArr[adjCity.v] > (distArr[city] + adjCity.w))
			{
				distArr[adjCity.v] = distArr[city] + adjCity.w;
			}
		}
	}

#if debug_m
	for (int city = 1; city <= VCnt; city++)
		printf("city %d : %d \n", city, distArr[city]);
	printf("\n");
#endif

	return retValue;
}
#include <iostream>
#include <queue>
#include <string.h>
#include <limits.h>

// def
#define MAX_SIZE 1000
#define debug_m 0

// struct
struct Info
{
	Info(int _r = 0, int _c = 0, int _sc = 0, bool _isB = false)
	{
		r = _r;
		c = _c;
		score = _sc;
		isBroken = _isB;
	}
	int r;
	int c;
	int score;
	bool isBroken;
};

// global
char board[MAX_SIZE + 1][MAX_SIZE + 1];
bool visited[MAX_SIZE + 1][MAX_SIZE + 1][2]; // [][][0] : 부수적 없음, [][][1] : 부순적 있음
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // 상 하 좌 우

// method
bool CheckingValid(int n, int m, int N, int M);
int BFS(int N, int M);

int main()
{
	// 2206 - 벽 부수고 이동하기

	// init
	setbuf(stdout, NULL);

	for (int i = 0; i < MAX_SIZE + 1; i++)
	{
		memset(board[i], 0, sizeof(MAX_SIZE + 1));
	}

	// input
	int N, M;
	N = M = 0;
	(void)scanf("%d %d", &N, &M);

	for (int n = 0; n < N; n++)
	{
		char buf[MAX_SIZE + 1] = { 0, };
		(void)scanf("%s", &buf);
		memcpy(board[n], buf, sizeof(buf));
	}

	// bfs
	const int answer = BFS(N, M);

	// print
	printf("%d", answer);

	return 0;
}

bool CheckingValid(int n, int m, int N, int M)
{
	bool retValue = true;

	if ((0 > n || N <= n) || (0 > m || M <= m))
		retValue = false;

	return retValue;
}

int BFS(int N, int M)
{
	int retValue = INT_MAX;

	std::queue<Info> que;
	que.push(Info(0, 0, 1, false));
	visited[0][0][0] = visited[0][0][1] = true;

	while (!que.empty())
	{
		Info info = que.front();
		que.pop();

#if debug_m
		printf("\n[%s] { info (%d, %d), sc : %d, isBroken : %d}\n",
			__FUNCTION__, info.r, info.c, info.score, info.isBroken);
#endif

		if ((N - 1 == info.r) && (M - 1 == info.c))
		{
			retValue = retValue < info.score ? retValue : info.score;
		}

		for (int d = 0; d < 4; d++)
		{
			int nextR = info.r - direction[d][0];
			int nextC = info.c - direction[d][1];

			const bool bIsValid = CheckingValid(nextR, nextC, N, M);
			if (true == bIsValid)
			{
				const char board_data = board[nextR][nextC];
				if ('0' == board_data)
				{
					if (false == info.isBroken && false == visited[nextR][nextC][0])
					{
						que.push(Info(nextR, nextC, info.score + 1, false));
						visited[nextR][nextC][0] = true;
					}
					else if (true == info.isBroken && false == visited[nextR][nextC][1])
					{
						que.push(Info(nextR, nextC, info.score + 1, true));
						visited[nextR][nextC][1] = true;
					}
				}
				else
				{
					if (false == info.isBroken && false == visited[nextR][nextC][1])
					{
						que.push(Info(nextR, nextC, info.score + 1, true));
						visited[nextR][nextC][1] = true;
					}
				}
			}
		}
	}

	if (INT_MAX == retValue)
		retValue = -1;

	return retValue;
}
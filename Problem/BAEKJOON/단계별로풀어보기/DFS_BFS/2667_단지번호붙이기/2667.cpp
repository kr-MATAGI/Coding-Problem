#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

// def
#define DEBUG_MODE 0
#define MAX_SIZE 25
#define POS_PAIR std::pair<int,int>

// method
bool CheckingValidPos(int x, int y, int N);
int BFS_Search(int map[][MAX_SIZE + 1], int N, int x, int y);

// global
bool visited[MAX_SIZE + 1][MAX_SIZE + 1];

int main()
{
	// 2667 - 단지번호붙이기
	for (int i = 0; i < MAX_SIZE + 1; i++)
		memset(visited[i], false, sizeof(visited[i]) * sizeof(bool));

	int N = 0;
	(void)scanf("%d", &N);

	std::vector<int> answer;
	int boardMap[MAX_SIZE + 1][MAX_SIZE + 1] = { 0, };
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			int input = 0;
			(void)scanf("%1d", &input);

			boardMap[x][y] = input;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (false == visited[i][j] && 1 == boardMap[i][j])
				answer.push_back(BFS_Search(boardMap, N, i, j));
		}
	}

	// sort
	sort(answer.begin(), answer.end());

	printf("%d\n", answer.size());
	for (int data : answer)
		printf("%d\n", data);

	return 0;
}

bool CheckingValidPos(int x, int y, int N)
{
	bool retValue = true;

	if ((0 > x || N <= x) || (0 > y || N <= y))
		retValue = false;

	return retValue;
}

int BFS_Search(int map[][MAX_SIZE + 1], int N, int x, int y)
{
#if DEBUG_MODE
	printf("---%s---\n", __FUNCTION__);
#endif
	int houseCnt = 0;
	int direction[4][2] = { {-1, 0}, {1, 0}, {0,-1}, {0,1} }; //상 하 좌 우

	std::queue<std::pair<int, int>> que;
	que.push(POS_PAIR(x, y));
	visited[x][y] = true;

	while (!que.empty())
	{
		POS_PAIR curValue = que.front();
		que.pop();
		houseCnt++;

#if DEBUG_MODE
		printf("curValue : (%d, %d), houseCnt : %d\n", curValue.first, curValue.second, houseCnt);
#endif

		// 상 하 좌 우
		for (int i = 0; i < 4; i++)
		{
			int nearX = curValue.first - direction[i][0];
			int nearY = curValue.second - direction[i][1];

			const bool bIsValid = CheckingValidPos(nearX, nearY, N);
			if (true == bIsValid)
			{
				if (1 == map[nearX][nearY] && false == visited[nearX][nearY])
				{
					que.push(POS_PAIR(nearX, nearY));
					visited[nearX][nearY] = true;
				}
			}
			else
				continue;
		}
	}

	return houseCnt;
}
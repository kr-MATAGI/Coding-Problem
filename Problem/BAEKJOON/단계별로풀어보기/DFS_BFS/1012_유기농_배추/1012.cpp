#include <iostream>
#include <string.h>
#include <vector>
#include <queue>

// def
#define BOARD_MAX_SIZE 50
#define POS_PAIR std::pair<int, int>

// method
bool CheckingValid(int x, int y, int X, int Y);
void BFS_Search(int map[][BOARD_MAX_SIZE + 1], int X, int Y, int x, int y);

// global
bool visited[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1];

int main()
{
	// 1012 - 유기농 배추
	std::ios::sync_with_stdio(false);

	std::vector<int> answers;
	int testCase = 0;
	std::cin >> testCase;
	for (int t = 0; t < testCase; t++)
	{
		int answer = 0;

		// init
		int board[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1] = { 0, };

		for (int i = 0; i < BOARD_MAX_SIZE + 1; i++)
			memset(visited[i], false, sizeof(visited[i]) * sizeof(bool));

		

		// input
		int M, N, K;
		M = N = K = 0;
		std::cin >> M >> N >> K;

		for (int k = 0; k < K; k++)
		{
			int x, y;
			x = y = 0;
			std::cin >> x >> y;
			board[x][y] = 1;
		}

		// calc
		for (int m = 0; m < M; m++)
		{
			for (int n = 0; n < N; n++)
			{
				if (false == visited[m][n] && 1 == board[m][n])
				{
					BFS_Search(board, M, N, m, n);
					answer++;
				}
			}
		}

		answers.push_back(answer);
	}

	// print answer
	for (int ans : answers)
		printf("%d\n", ans);

	return 0;
}

bool CheckingValid(int x, int y, int X, int Y)
{
	bool retValue = true;

	if ((x < 0 || x >= X) || (y < 0 || y >= Y))
		retValue = false;

	return retValue;
}

void BFS_Search(int map[][BOARD_MAX_SIZE + 1], int X, int Y, int x, int y)
{
	std::queue<POS_PAIR> que;
	que.push(POS_PAIR(x, y));
	visited[x][y] = true;

	int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // 상 하 좌 우

	while (!que.empty())
	{
		POS_PAIR curValue = que.front();
		que.pop();

		for (int d = 0; d < 4; d++)
		{
			int nearX = curValue.first - direction[d][0];
			int nearY = curValue.second - direction[d][1];

			const bool bIsValid = CheckingValid(x, y, X, Y);
			if (true == bIsValid)
			{
				if (false == visited[nearX][nearY] && 1 == map[nearX][nearY])
				{
					que.push(POS_PAIR(nearX, nearY));
					visited[nearX][nearY] = true;
				}
			}
			else
				continue;
		}
	}
}
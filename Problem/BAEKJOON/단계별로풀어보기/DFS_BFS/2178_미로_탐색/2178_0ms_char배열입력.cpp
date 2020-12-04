#include <iostream>
#include <cstring>
#include <queue>

// def
#define BOARD_MAX_SIZE 100
#define POS_PAIR std::pair<int, int>
#define SCORE_PAIR std::pair<POS_PAIR, int>

// global
char board[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1];
bool visited[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1];
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // ╩С, го, аб, ©Л

// method
bool CheckingValid(int x, int y, int X, int Y);
int BFS(char board[][BOARD_MAX_SIZE + 1], int X, int Y);

int main()
{
	// 2178 - ╧л╥не╫╩Ж
	std::ios::sync_with_stdio(false);

	// input
	int N, M;
	N = M = 0;
	(void)scanf("%d %d", &N, &M);

	//printf("%d %d\n\n", sizeof(char), sizeof(int));

	for (int n = 0; n < N; n++)
	{
		char buf[BOARD_MAX_SIZE + 1] = { '\0', };
		(void)scanf("%s", buf);
		memcpy(board[n], buf, strlen(buf));
	}

	// calc
	int answer = BFS(board, N, M);

	// print
	printf("%d", answer);

	return 0;
}

bool CheckingValid(int x, int y, int X, int Y)
{
	bool retValue = true;

	if ((x < 0 || x >= X) || (y < 0 || y >= Y))
		retValue = false;

	return retValue;
}


int BFS(char board[][BOARD_MAX_SIZE + 1], int X, int Y)
{
	int retValue = 0;

	// calc
	std::queue<SCORE_PAIR> que;
	que.push(SCORE_PAIR(POS_PAIR(0, 0), 1));

	while (!que.empty())
	{
		SCORE_PAIR curPos = que.front();
		que.pop();
		int curX = curPos.first.first;
		int curY = curPos.first.second;
		int score = curPos.second;

		if (curX == X - 1 && curY == Y - 1)
		{
			retValue = score;
			break;
		}

		for (int d = 0; d < 4; d++)
		{
			int nearX = curX - direction[d][0];
			int nearY = curY - direction[d][1];

			const bool bIsValid = CheckingValid(nearX, nearY, X, Y);
			if (true == bIsValid && false == visited[nearX][nearY])
			{
				if ('1' == board[nearX][nearY])
				{
					que.push(SCORE_PAIR(POS_PAIR(nearX, nearY), score + 1));
					visited[nearX][nearY] = true;
				}
			}
			else
				continue;
		}
	}

	return retValue;
}
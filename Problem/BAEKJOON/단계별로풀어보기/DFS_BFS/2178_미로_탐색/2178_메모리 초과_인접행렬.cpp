#include <iostream>
#include <queue>

// def
#define BOARD_MAX_SIZE 100
#define POS_PAIR std::pair<int, int>

// method
bool CheckingValid(int x, int y, int X, int Y);
int BFS(int board[][BOARD_MAX_SIZE + 1], int X, int Y);

int main()
{
	// 2178 - ╧л╥не╫╩Ж

	// init
	std::ios::sync_with_stdio(false);
	int board[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1] = { 0, };

	// input
	int N, M;
	N = M = 0;
	(void)scanf("%d %d", &N, &M);

	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			int input = 0;
			(void)scanf("%1d", &input);

			board[n][m] = input;
		}
	}

	// calc
	const int answer = BFS(board, N, M);

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


int BFS(int board[][BOARD_MAX_SIZE + 1], int X, int Y)
{
	int retValue = 0;

	// init
	int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // ╩С, го, аб, ©Л
	bool visited[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1] = { false, };
	int scoreBoard[BOARD_MAX_SIZE + 1][BOARD_MAX_SIZE + 1];

	for (int i = 0; i < BOARD_MAX_SIZE + 1; i++)
		for (int j = 0; j < BOARD_MAX_SIZE + 1; j++)
			scoreBoard[i][j] = 999;

	// calc
	std::queue<POS_PAIR> que;
	que.push(POS_PAIR(0, 0));
	scoreBoard[0][0] = 1;

	while (!que.empty())
	{
		POS_PAIR curPos = que.front();
		que.pop();
		visited[curPos.first][curPos.second] = true;

		for (int d = 0; d < 4; d++)
		{
			int nearX = curPos.first - direction[d][0];
			int nearY = curPos.second - direction[d][1];

			const bool bIsValid = CheckingValid(nearX, nearY, X, Y);
			if (true == bIsValid && false == visited[nearX][nearY])
			{
				if (1 == board[nearX][nearY])
				{
					que.push(POS_PAIR(nearX, nearY));
					scoreBoard[nearX][nearY] = scoreBoard[nearX][nearY] < scoreBoard[curPos.first][curPos.second] + 1
						? scoreBoard[nearX][nearY] : scoreBoard[curPos.first][curPos.second] + 1;
				}
			}
			else
				continue;
		}
	}

	retValue = scoreBoard[X - 1][Y - 1];

	return retValue;
}
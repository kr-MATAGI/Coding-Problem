#include <iostream>
#include <vector>
#include <queue>

// def
#define MAX_BOARD_SIZE 1000
#define POS_PAIR std::pair<int, int>
#define DAY_PAIR std::pair<POS_PAIR, int>
#define DEBUG_MODE 0

// struct
struct DATA
{
	DATA()
	{
		data = 0;
		visited = false;
	}
	int data;
	bool visited;
};

// global
/*
* 1 : 익은 토마토
* 0 : 익지 않은 토마토
* -1 : 토마토가 들어 있지 않은 칸
*/
std::vector<DATA> board[MAX_BOARD_SIZE + 1];

// 상 하 좌 우
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// method
bool Checking(int x, int y, int X, int Y);
int BFS_Function(int N, int M, int zeroCnt);

int main()
{
	// 7576 - 토마토
	std::ios::sync_with_stdio(false);

	// input
	int N, M;
	N = M = 0;
	(void)scanf("%d %d", &M, &N);

	int zeroCnt = 0;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			DATA tomato;
			(void)scanf("%d", &tomato.data);
			if (0 == tomato.data)
				zeroCnt++;

			board[n].push_back(tomato);
		}
	}

#if DEBUG_MODE
	printf("[%s] zeroCount : %d\n", __FUNCTION__, zeroCnt);
#endif

	// calc
	const int answer = BFS_Function(N, M, zeroCnt);
	printf("%d", answer);

	return 0;
}

bool Checking(int x, int y, int X, int Y)
{
	if ((x < 0 || x >= X) || (y < 0 || y >= Y))
		return false;

	return true;
}

int BFS_Function(int N, int M, int zeroCnt)
{
	int retValue = 0;

	if (0 == zeroCnt)
		return retValue;

	std::queue<DAY_PAIR> que;

	int row, col;
	row = col = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (1 == board[i][j].data)
			{
				que.push(DAY_PAIR(POS_PAIR(i, j), 0));
			}
		}
	}

#if DEBUG_MODE
	printf("[%s] start row : %d, col : %d \n", __FUNCTION__, row, col);
#endif

	int count = 0;
	int max = 0;
	while (!que.empty())
	{
		DAY_PAIR dayPair = que.front();
		que.pop();
		POS_PAIR pos = dayPair.first;
		int day = dayPair.second;
		max = max > day ? max : day;

		for (int d = 0; d < 4; d++)
		{
			int x = pos.first - direction[d][0];
			int y = pos.second - direction[d][1];

			const bool bIsValid = Checking(x, y, N, M);
			if (true == bIsValid)
			{
				if (false == board[x][y].visited && -1 != board[x][y].data)
				{
					que.push(DAY_PAIR(POS_PAIR(x, y), day + 1));
					board[x][y].visited = true;
					if (0 == board[x][y].data)
					{
						board[x][y].data = 1;
						count++;
					}
#if DEBUG_MODE
					printf("----pos (%d, %d, %d) | x : %d, y : %d, day+1 : %d ----\n",
						pos.first, pos.second, day, x, y, day + 1);
#endif
				}
			}
			else
				continue;
		}
	}

	if (count != zeroCnt)
		retValue = -1;
	else
		retValue = max;

	return retValue;
}
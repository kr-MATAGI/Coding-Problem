#include <iostream>
#include <vector>
#include <queue>

// def
#define MAX_BOARD_SIZE 1000
#define POS_PAIR std::pair<int, int>
#define DAY_PAIR std::pair<POS_PAIR, int>
#define DEBUG_MODE 0

// global
/*
* 1 : 익은 토마토
* 0 : 익지 않은 토마토
* -1 : 토마토가 들어 있지 않은 칸
*/
std::vector<int> board[MAX_BOARD_SIZE + 1];
bool visited[MAX_BOARD_SIZE + 1][MAX_BOARD_SIZE + 1];

// 상 하 좌 우
int direction[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// method
bool Checking(int x, int y, int X, int Y);
int BFS_Function(int N, int M, int zeroCnt, std::vector<POS_PAIR>& startList);

int main()
{
	// 7576 - 토마토
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	// input
	int N, M;
	N = M = 0;
	std::cin >> M >> N;

	int zeroCnt = 0;
	std::vector<POS_PAIR> startList;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			int tomato;
			std::cin >> tomato;

			if (0 == tomato)
				zeroCnt++;
			else if (1 == tomato)
				startList.push_back(POS_PAIR(n, m));

			board[n].push_back(tomato);
		}
	}

	// calc
	const int answer = BFS_Function(N, M, zeroCnt, startList);
	std::cout << answer;

	return 0;
}

bool Checking(int x, int y, int X, int Y)
{
	if ((x < 0 || x >= X) || (y < 0 || y >= Y))
		return false;

	return true;
}

int BFS_Function(int N, int M, int zeroCnt, std::vector<POS_PAIR>& startList)
{
	int retValue = 0;

	if (0 == zeroCnt)
		return retValue;

	std::queue<DAY_PAIR> que;
	for (POS_PAIR& data : startList)
	{
		que.push(DAY_PAIR(data, 0));
		visited[data.first][data.second] = true;
	}

	int count = 0;
	int max = 0;
	while (!que.empty())
	{
		DAY_PAIR dayPair = que.front();
		que.pop();

		POS_PAIR pos = dayPair.first;
		int day = dayPair.second;
		retValue = day;

		for (int d = 0; d < 4; d++)
		{
			int x = pos.first - direction[d][0];
			int y = pos.second - direction[d][1];

			const bool bIsValid = Checking(x, y, N, M);
			if (true == bIsValid)
			{
				if (false == visited[x][y] && -1 != board[x][y])
				{
					que.push(DAY_PAIR(POS_PAIR(x, y), day + 1));
					visited[x][y] = true;

					if (0 == board[x][y])
					{
						board[x][y] = 1;
						count++;
					}
				}
			}
			else
				continue;
		}
	}

	if (count != zeroCnt)
		retValue = -1;

	return retValue;
}
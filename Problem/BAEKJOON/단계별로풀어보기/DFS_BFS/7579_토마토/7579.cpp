#include <iostream>
#include <vector>
#include <queue>

// struct
struct POS
{
	POS()
	{
		h = x = y = 0;
	}
	POS(int _h, int _x, int _y)
	{
		h = _h;
		x = _x;
		y = _y;
	}
	int h;
	int x;
	int y;
};

// def
#define MAX_SIZE 100
#define PAIR std::pair<POS, int>

// global
// h, n, m
std::vector<int> board[MAX_SIZE + 1][MAX_SIZE + 1];
bool visited[MAX_SIZE + 1][MAX_SIZE + 1][MAX_SIZE + 1];

// À­Ãþ, ¾Æ·¡Ãþ, »ó ÇÏ ÁÂ ¿ì
int direction[6][3] = {
						{-1, 0, 0}, {1, 0, 0},
						{0, -1, 0}, {0, 1, 0},
						{0, 0, -1}, {0, 0, 1}
};

// method
bool Checking(int h, int x, int y, int H, int X, int Y);
int BFS(int H, int X, int Y, int zeroCnt, std::vector<POS>& startList);

int main()
{
	// 7569 - Åä¸¶Åä 3Â÷¿ø
	std::ios::sync_with_stdio(false);
	std::setbuf(stdout, NULL);

	int N; // ¼¼·Î
	int M; // °¡·Î
	int H; // Ãþ¼ö
	(void)scanf("%d %d %d", &M, &N, &H);

	// input
	std::vector<POS> startList;
	int zeroCount = 0;
	for (int h = 0; h < H; h++)
	{
		for (int n = 0; n < N; n++)
		{
			for (int m = 0; m < M; m++)
			{
				int input = 0;
				(void)scanf("%d", &input);

				if (1 == input)
				{
					POS temp(h, n, m);
					startList.push_back(temp);
				}
				else if (0 == input)
					zeroCount++;

				board[h][n].push_back(input);
			}
		}
	}

	// bfs
	const int answer = BFS(H, N, M, zeroCount, startList);

	// print
	printf("%d", answer);

	return 0;
}

bool Checking(int h, int x, int y, int H, int X, int Y)
{
	bool retValue = true;

	if ((h < 0 || h >= H) || (x < 0 || x >= X) || (y < 0 || y >= Y))
		retValue = false;

	return retValue;
}

int BFS(int H, int X, int Y, int zeroCnt, std::vector<POS>& startList)
{
	int retValue = 0;
	if (0 == zeroCnt)
		return retValue;

	// init
	std::queue<PAIR> que;
	for (POS& data : startList)
	{
		que.push(PAIR(data, 0));
		visited[data.h][data.x][data.y] = true;
	}

	int count = 0;
	while (!que.empty())
	{
		PAIR pair = que.front();
		que.pop();

		POS pos = pair.first;
		int day = pair.second;
		retValue = day;

		for (int d = 0; d < 6; d++)
		{
			int h = pos.h - direction[d][0];
			int x = pos.x - direction[d][1];
			int y = pos.y - direction[d][2];

			const bool bIsValid = Checking(h, x, y, H, X, Y);
			if (true == bIsValid)
			{
				if (false == visited[h][x][y] && -1 != board[h][x][y])
				{
					que.push(PAIR(POS(h, x, y), day + 1));
					visited[h][x][y] = true;

					if (0 == board[h][x][y])
					{
						board[h][x][y] = 1;
						count++;
					}
				}
			}
			else
				continue;
		}
	}

	// answer
	if (count != zeroCnt)
		retValue = -1;

	return retValue;
}
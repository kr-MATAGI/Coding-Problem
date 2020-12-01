#include <iostream>
#include <queue>

#define MAX_SIZE 10
#define MIN_SIZE 3

// def
struct POS
{
	POS()
	{
		count = 0;
	}
	int count;
	int rx, ry, bx, by;
};

// left, right, top, bottom
int dir[4][2] = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };

// board info
char board[MAX_SIZE + 1][MAX_SIZE + 1];
bool visited[MAX_SIZE + 1][MAX_SIZE + 1][MAX_SIZE+1][MAX_SIZE+1]; //rx, ry, bx, by

int main()
{
	int N, M;
	N = M = 0;
	std::cin >> N >> M;

	// input
	POS ballPos;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			char input = '\0';
			std::cin >> input;

			if ('R' == input)
			{
				ballPos.rx = n;
				ballPos.ry = m;
			}
			else if ('B' == input)
			{
				ballPos.bx = n;
				ballPos.by = m;
			}

			board[n][m] = input;
		}
	}

	// calc (BFS)
	std::queue<POS> que;
	que.push(ballPos);
	visited[ballPos.rx][ballPos.ry][ballPos.bx][ballPos.by] = true;

	const int answer = BFS(que);
	printf("%d\n", answer);


	return 0;
}

int BFS(std::queue<POS>& que)
{
	int answer = 999;

	while(!que.empty())
	{
		POS temp = que.front();
		que.pop();

		for (int r = 0; r < 4; r++)
		{
			while ('#' != temp[])
			{

			}
		}
	}

	if (10 < answer)
		answer = -1;

	return answer;
}
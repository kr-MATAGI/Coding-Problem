#include <iostream>
#include <queue>

// def
#define MAX_SIZE 100000
#define PAIR std::pair<int, int>
#define DEBUG_MODE 0

// global
bool visisted[MAX_SIZE + 1];

// method
int BFS(int N, int K);

int main()
{
	// 1697 - 숨바꼭질
	std::ios::sync_with_stdio(false);
	std::setbuf(stdout, NULL);

	int N = 0; // 수빈이 위치
	int K = 0; // 동생 위치
	(void)scanf("%d %d", &N, &K);

	const int answer = BFS(N, K);
	printf("%d", answer);

	return 0;
}


int BFS(int N, int K)
{
	int answer = 0;

	std::queue<PAIR> que;
	que.push(PAIR(N, 0));
	visisted[N] = true;

	while (!que.empty())
	{
		PAIR pair = que.front();
		que.pop();

		int value = pair.first;
		int score = pair.second;

#if DEBUG_MODE
		printf("[%s] { value : %d, score : %d }\n", __FUNCTION__, value, score);
#endif

		if (value == K)
		{
			answer = score;
			break;
		}

		if ((MAX_SIZE >= value - 1 && 0 <= value - 1) && false == visisted[value - 1])
		{
			que.push(PAIR(value - 1, score + 1));
			visisted[value - 1] = true;
		}

		if ((MAX_SIZE >= value + 1 && 0 <= value + 1) && false == visisted[value + 1])
		{
			que.push(PAIR(value + 1, score + 1));
			visisted[value + 1] = true;
		}

		if ((MAX_SIZE >= value * 2 && 0 <= value * 2) && false == visisted[value * 2])
		{
			que.push(PAIR(value * 2, score + 1));
			visisted[value * 2] = true;
		}
	}

	return answer;
}
#include <iostream>
#include <vector>
#include <string.h>

#define MAX_SIZE 8

void DFS(bool* visited, int N, int M, std::vector<int>& answer);

int main()
{
	int N, M;
	N = M = 0;
	std::cin >> N >> M;

	// DFS
	bool visisted[MAX_SIZE + 1] = { 0, };
	std::vector<int> answer;
	DFS(visisted, N, M, answer);

	return 0;
}

void DFS(bool* visited, int N, int M, std::vector<int>& answer)
{
	if (answer.size() == M)
	{
		for (int data : answer)
			std::cout << data << " ";
		std::cout << "\n";

		return;
	}

	for (int n = 1; n <= N; n++)
	{
		if (false == visited[n])
		{
			visited[n] = true;
			answer.push_back(n);
			DFS(visited, N, M, answer);
			answer.pop_back();
			visited[n] = false;
		}
	}
}
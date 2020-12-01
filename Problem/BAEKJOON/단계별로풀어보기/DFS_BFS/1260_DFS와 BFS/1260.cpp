#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

// def
#define N_MAX_SIZE 1000
#define M_MAX_SIZE 10000

// 0 : 비연결, 1 : 연결
bool adjArray[N_MAX_SIZE + 1][N_MAX_SIZE + 1] = { false, };
std::vector<int> inputVec;

// method
std::vector<int> DFS_Search(const int startV, const int NCnt);
std::vector<int> BFS_Search(const int startV, const int NCnt);

bool compare(int& a, int& b)
{
	return a > b;
}

int main()
{
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	// N : 정점의 수, M : 간선의 수, V : 탐색을 시작할 정점
	int N, M, V;
	N = M = V = 0;
	std::cin >> N >> M >> V;

	std::set<int> inputSet;
	for (int m = 0; m < M; m++)
	{
		int a, b;
		a = b = 0;
		std::cin >> a >> b;

		adjArray[a][b] = true;
		adjArray[b][a] = true;
		inputSet.insert(a);
		inputSet.insert(b);
	}
	for (int data : inputSet)
		inputVec.push_back(data);

	// DFS
	const std::vector<int> dfsAns = DFS_Search(V, N);

	// BFS
	const std::vector<int> bfsAns = BFS_Search(V, N);

	// print
	for (int data : dfsAns)
		std::cout << data << " ";
	std::cout << "\n";
	for (int data : bfsAns)
		std::cout << data << " ";

	return 0;
}


std::vector<int> DFS_Search(const int startV, const int NCnt)
{
	std::vector<int> answer;

	bool visited[N_MAX_SIZE + 1] = { false, };
	std::vector<int> stack;
	stack.push_back(startV);

	sort(inputVec.begin(), inputVec.end(), compare);

	while (!stack.empty())
	{
		int curValue = stack.back();
		stack.pop_back();

		if (false == visited[curValue])
		{
			answer.push_back(curValue);
		}
		visited[curValue] = true;

		for (int& idx : inputVec)
		{
			if (idx == curValue)
				continue;
			if (false == visited[idx] && true == adjArray[curValue][idx])
				stack.push_back(idx);
			else if (false == visited[idx] && true == adjArray[idx][curValue])
				stack.push_back(idx);
		}
	}

	return answer;
}


std::vector<int> BFS_Search(const int startV, const int NCnt)
{
	std::vector<int> answer;

	std::queue<int> que;
	que.push(startV);

	bool visited[N_MAX_SIZE + 1] = { false, };
	while (!que.empty())
	{
		int frontVal = que.front();
		que.pop();

		if (false == visited[frontVal])
			answer.push_back(frontVal);
		visited[frontVal] = true;

		const int inputVesSize = inputVec.size();
		for (int idx = inputVesSize - 1; idx >= 0; idx--)
		{
			int val = inputVec[idx];
			if (val == frontVal)
				continue;
			if (false == visited[val] && true == adjArray[frontVal][val])
				que.push(val);
			else if (false == visited[val] && true == adjArray[frontVal][val])
				que.push(val);
		}
	}

	return answer;
}
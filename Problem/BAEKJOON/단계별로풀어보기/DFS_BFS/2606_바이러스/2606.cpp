#include <iostream>
#include <vector>

// def
#define COM_MAX_COUNT 100
#define START_COM 1
#define DEBUG_MODE 0

// method
int Infection(std::vector<int> graph[])
{
	int answer = -1;
	
	bool visited[COM_MAX_COUNT + 1] = { false, };
	std::vector<int> stack;
	stack.push_back(START_COM);

#if DEBUG_MODE
	std::vector<int> vistedHistory;
#endif

	while (!stack.empty())
	{
		int curNode = stack.back();
		stack.pop_back();

#if DEBUG_MODE
		std::cout << "curNode : " << curNode << "\n";
		vistedHistory.push_back(curNode);
#endif
		answer++;
		visited[curNode] = true;
		
		std::vector<int>::iterator iter;
		for (iter = graph[curNode].begin(); iter != graph[curNode].end(); ++iter)
		{
			// not visted node
			if (false == visited[*iter])
			{
				visited[*iter] = true;
				stack.push_back(*iter);
			}
		}
	}

	return answer;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int comCnt = 0;
	int connCnt = 0;
	
	std::cin >> comCnt;	
	std::cin >> connCnt;

	std::vector<int> graphVec[COM_MAX_COUNT+1];

	for (int n = 0; n < connCnt; n++)
	{
		int a, b;
		a = b = 0;
		std::cin >> a >> b;

		// no direction
		graphVec[a].push_back(b);
		graphVec[b].push_back(a);
	}

	// calc
	int answer = Infection(graphVec);
	std::cout << answer;

	return 0;
}
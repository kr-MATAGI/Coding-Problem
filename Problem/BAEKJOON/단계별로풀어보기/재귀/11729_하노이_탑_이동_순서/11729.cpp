#include <iostream>
#include <vector>

// def
#define DEBUG_MODE 1

// method
void FromByTo(const int num, const int from, const int by, const int to, int& movedCount);

// global
int N;
std::vector<std::pair<int, int>> movedHistory;

int main()
{
	N = 0;
	std::cin >> N;

	/*
	* 원반 n개를 이동하는 문제는 원반 n-1개로 이동하는 문제로 세분화 되고,
	* n-1개를 이동하는 문제는 n-2개로 이동하는 문제로 세분화됨...
	* 즉, 원반 1개를 이동하는 문제로 세분화 됨.
	*/
	
	int movedCount = 0;
	FromByTo(N, 1, 2, 3, movedCount);

	// print
	printf("%d\n", movedCount);
	for (const auto& data : movedHistory)
	{
		printf("%d %d\n", data.first, data.second);
	}

	return 0;
}

void FromByTo(int num, int A, int B, int C, int& movedCount)
{
	// from에 있는 num개의 원반을 by를 거쳐 to로 옮긴다.
	movedCount++;

#if DEBUG_MODE 
	printf("----- num : %d, A : %d, B : %d, C : %d\n", num, A, B, C);
#endif

	if (1 == num)
	{
		movedHistory.push_back(std::pair<int, int>(A, C));

#if DEBUG_MODE
		printf("%d -> %d \n", A, C);
#endif
	}
	else
	{
		// num-1개를 A to B
		FromByTo(num - 1, A, C, B, movedCount);

		// 1개를 A to C
		movedHistory.push_back(std::pair<int, int>(A, C));
#if DEBUG_MODE
		printf("%d -> %d \n", A, C);
#endif

		// num-1개를 B to C
		FromByTo(num - 1, B, A, C, movedCount);
	}
}
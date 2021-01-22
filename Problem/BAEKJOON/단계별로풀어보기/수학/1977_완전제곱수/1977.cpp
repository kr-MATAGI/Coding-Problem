#include <iostream>
#include <limits.h>
#include <math.h>

// size
#define INPUT_MAX	10000

// macro
#define MIN(a,b) (a < b ? a : b)

int main()
{
	// 1977
	// init
	std::ios::sync_with_stdio(false);

	//input
	int M = 0;
	int N = 0;
	(void)scanf("%d\n%d", &M, &N);

	// calc
	int perfSquSum = 0;
	int minSquNum = INT_MAX;

	for (int m = M; m <= N; m++)
	{
		int sqrtNum = sqrt(m);
		if (sqrtNum * sqrtNum == m)
		{
			perfSquSum += m;
			minSquNum = MIN(minSquNum, m);
		}
	}

	// printf
	if (0 == perfSquSum)
		printf("-1\n");
	else
		printf("%d\n%d\n", perfSquSum, minSquNum);

	return 0;
}
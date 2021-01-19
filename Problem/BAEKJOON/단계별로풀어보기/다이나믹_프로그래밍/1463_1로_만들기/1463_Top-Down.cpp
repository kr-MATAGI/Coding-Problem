#include <iostream>
#include <algorithm>
#include <limits.h>

// size
#define INPUT_MAX	10000000

// macro
#define MIN(a, b) (a < b ? a : b)

// global
int dp[INPUT_MAX+1];

int main()
{
	// init
	std::ios::sync_with_stdio(false);
	std::fill(dp, dp + (INPUT_MAX + 1), INT_MAX);

	// input
	int input = 0;
	(void)scanf("%d", &input);

	// top-down
	dp[input] = 0;
	for(int i = input; i > 0; i--)
	{
		if (0 == (i % 3))
		{
			dp[i / 3] = MIN(dp[i / 3], dp[i] + 1);
		}
		if (0 == (i % 2))
		{
			dp[i / 2] = MIN(dp[i / 2], dp[i] + 1);
		}
		if (2 <= i)
		{
			dp[i - 1] = MIN(dp[i - 1], dp[i] + 1);
		}
	}

	// print
	printf("%d\n", dp[1]);

	return 0;
}
#include <iostream>
#include <algorithm>
#include <limits.h>

// debug
#define debug_m 0

// size
#define INPUT_MAX	10000000
#define DP_ARR_SIZE	3000000

// macro
#define MIN(a, b) (a < b ? a : b)

// global
int dp[INPUT_MAX + 1];

// method
#if debug_m
void PrintDPArray(int dp[], int input);
#endif

int main()
{
	// init
	std::ios::sync_with_stdio(false);

	// input
	int input = 0;
	(void)scanf("%d", &input);
	std::fill(dp, dp + (input + 1), INT_MAX);

	// bottom-up
	dp[0] = dp[1] = 0;
	for (int i = 1; i <= input; i++)
	{
		if (i * 2 <= input)
		{
			dp[i * 2] = MIN(dp[i * 2], dp[i] + 1);
		}
		if (i * 3 <= input)
		{
			dp[i * 3] = MIN(dp[i * 3], dp[i] + 1);
		}
		if (i + 1 <= input)
		{
			dp[i + 1] = MIN(dp[i + 1], dp[i] + 1);
		}
#if debug_m
		PrintDPArray(dp, input);
#endif
	}

	// print
	printf("%d\n", dp[input]);

	return 0;
}

void PrintDPArray(int dp[], int input)
{

	for (int i = 0; i <= input; i++)
	{
		if (0 == i)
		{
			printf("%d ", i);
		}
		else
		{
			if (INT_MAX == dp[i])
				printf("INF ");
			else
				printf("%d ", dp[i]);
		}
	}
	printf("\n");
}
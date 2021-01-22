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
	std::cin.tie(NULL);
	
	// input
	int input = 0;
	//(void)scanf("%d", &input);
	std::cin >> input;
	std::fill(dp, dp + (input + 1), INT_MAX);

	// bottom-up
	dp[0] = dp[1] = 0; // 0과 1의 연산의 횟수
	for (int i = 2; i <= input; i++)
	{
		dp[i] = dp[i - 1] + 1;

		if (0 == i % 2)
		{
			dp[i] = MIN(dp[i], dp[i / 2] + 1);
		}
		if (0 == i % 3)
		{
			dp[i] = MIN(dp[i], dp[i / 3] + 1);
		}

#if debug_m
		PrintDPArray(dp, input);
#endif
	}

	// print
	//printf("%d\n", dp[input]);
	std::cout << dp[input] << "\n";

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
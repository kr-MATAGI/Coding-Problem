#include <iostream>

#define MAX_SIZE 15

int main()
{
	int N = 0;
	std::cin >> N;

	int dp[MAX_SIZE + 1] = { 0, };
	for (int n = 0; n < N; n++)
	{
		int time, price;
		time = price = 0;
		std::cin >> time >> price;

		// 퇴사일 까지 최대값으로 채워주는 조건
		if (dp[n] > dp[n + 1])
			dp[n + 1] = dp[n];

		// 상담이 끝나는 날에 대한 값을 최대값으로 업데이트
		if ( (n+time <= N) && (dp[n + time] < dp[n] + price))
			dp[n + time] = dp[n] + price;
	}
	
	printf("%d\n", dp[N]);

	return 0;
}
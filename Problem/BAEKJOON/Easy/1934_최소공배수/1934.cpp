#include <iostream>

int main()
{
	// init
	std::ios::sync_with_stdio(false);

	// input
	int T = 0; // test case
	(void)scanf("%d", &T);

	for (int t = 0; t < T; t++)
	{
		int A, B;
		A = B = 0;
		(void)scanf("%d %d", &A, &B);

		// calc
		int gcd = 0;
		int lcm = 0;
		int bigger = A < B ? B : A;
		int smaller = A < B ? A : B;
		while (0 != smaller)
		{
			int temp = bigger % smaller;
			bigger = smaller;
			smaller = temp;
		}
		gcd = bigger;
		lcm = A * B / gcd;

		// print
		printf("%d\n", lcm);
	}

	return 0;
}
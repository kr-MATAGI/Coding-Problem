#include <iostream>

#define MAX_SIZE 100

int main()
{
	int testCase = 0;
	std::cin >> testCase;

	long long dpArr[MAX_SIZE + 1] = { 0, };
	dpArr[1] = 1;
	dpArr[2] = 1;
	dpArr[3] = 1;
	dpArr[4] = 2;

	/*
	* n번째 삼각형의 길이의 합은( n-1 ) + ( n -5 )
	* 
	*/
	for (int idx = 5; idx <= MAX_SIZE; idx++)
	{
		dpArr[idx] = dpArr[idx - 1] + dpArr[idx-5];
	}

	for (int tIdx = 0; tIdx < testCase; tIdx++)
	{
		int N = 0;
		std::cin >> N;

		std::cout << dpArr[N] << "\n";
	}


	return 0;
}
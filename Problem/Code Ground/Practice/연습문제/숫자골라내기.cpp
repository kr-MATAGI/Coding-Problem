#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>


struct INPUT
{
	INPUT()
		: inputNum(0)
		, count(0)
	{

	}
	int inputNum;
	int count;
};

int main()
{
	int testCase = 0;
	scanf("%d", &testCase);

	for( int tIdx = 0; tIdx < testCase; tIdx++ )
	{
		int inputCount = 0;
		scanf("%d", &inputCount);

		// set input
		std::vector<int> compareList;
		for( int inputIdx = 0; inputIdx < inputCount; inputIdx++ )
		{
			int inputNum = 0;
			scanf("%d", &inputNum);
			compareList.push_back(inputNum);
		}

		// XOR
		int result = 0;
		for( int idx = 0; idx < compareList.size(); idx++ )
		{
			result ^= compareList[idx];
		}

		// print Result
		printf("Case #%d\n%d\n", ( tIdx + 1 ), result);

	}


	return 0;
}
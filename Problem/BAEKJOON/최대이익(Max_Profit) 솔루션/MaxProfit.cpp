#include <iostream>

int main()
{
	int inputList[] = {
		10300, 9600, 9800,
		8200, 7800, 8300,
		9500, 9800, 10200, 9500
	};

	const int inputSize = sizeof(inputList) / sizeof(int);

	int maxProfit = 0;
	int minValue = inputList[0];
	for (int idx = 1; idx < inputSize; idx++)
	{
		const int profit = inputList[idx] - minValue;
		minValue = minValue > inputList[idx] ? inputList[idx] : minValue;

		maxProfit = maxProfit < profit ? profit : maxProfit;
	}

	std::cout << maxProfit << "\n";

	return 0;
}
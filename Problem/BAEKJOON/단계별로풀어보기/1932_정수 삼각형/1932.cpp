#include <iostream>
#include <vector>

#define MAX_SIZE 500

int main()
{
	int N = 0;
	std::cin >> N;

	std::vector<std::vector<int>> inputList;
	for (int n = 1; n <= N; n++)
	{
		std::vector<int> loop;
		for (int m = 1; m <= n; m++)
		{
			int input = 0;
			std::cin >> input;

			loop.push_back(input);
		}
		inputList.push_back(loop);
	}

	int curRow = inputList.size() - 2;
	int maxCol = N - 1;
	while (true)
	{
		if (0 > curRow)
		{
			break;
		}

		for (int i = 0; i < maxCol; i++)
		{
			int leftVal = inputList[curRow][i] + inputList[curRow + 1][i];
			int rightVal = inputList[curRow][i] + inputList[curRow + 1][i + 1];

			inputList[curRow][i] = leftVal > rightVal ? leftVal : rightVal;
		}

		curRow--;
		maxCol--;
	}

	std::cout << inputList[0][0] << "\n";


	return 0;
}
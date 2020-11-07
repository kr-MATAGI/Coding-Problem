#include <iostream>
#include <vector>

#define MAX_STEP_SIZE 300

int main()
{
	int N = 0;
	std::cin >> N;

	std::vector<int> inputList;
	for (int n = 0; n < N; n++)
	{
		int input = 0;
		std::cin >> input;
		inputList.push_back(input);
	}

	/*
	* 1. 계단은 한 번에 한 계단씩 또는 두 계단씩 오를 수 있다.
	* 즉, 한 계단을 밟으면서 이어서 다음 계단이나,
	* 다음 다음 계단으로 오를 수 있다.
	* 2. 연속된 세 개의 계단을 모두 밟아서는 안 된다.
	* 단, 시작점은 계단에 포함되지 않는다.
	* 3. 마지막 도착 계단은 반드시 밟아야 한다.
	*/

	int dpArr[MAX_STEP_SIZE + 1] = { 0, };
	dpArr[0] = inputList[0];
	dpArr[1] = inputList[1] > inputList[0] + inputList[1] ?
		inputList[1] : inputList[0] + inputList[1];
	dpArr[2] = inputList[2] + inputList[1] > inputList[2] + inputList[0] ?
		inputList[2] + inputList[1] : inputList[2] + inputList[0];

	for (int step = 3; step < N; step++)
	{
		int combo = inputList[step] + inputList[step - 1] + dpArr[step - 3];
		int notCombo = inputList[step] + dpArr[step - 2];
		dpArr[step] = combo > notCombo ? combo : notCombo;
	}

	std::cout << dpArr[N - 1] << "\n";

	return 0;
}
#include <iostream>
#include <string.h>

#define MAX_SIZE 15

bool Avaliable(int* board, int row);
void DFS(int* board, const int N, int row, int& answer);

int main()
{
	int board_row[MAX_SIZE + 1];
	memset(board_row, -1, MAX_SIZE + 1);


	int N = 0;
	std::cin >> N;

	int answer = 0;
	DFS(board_row, N, 0, answer);

	std::cout << answer << "\n";

	return 0;
}

void DFS(int* board, const int N, int row, int& answer)
{
	if (N == row)
	{
		answer++;
		return;
	}

	for (int col = 0; col < N; col++)
	{
		board[row] = col;
		const bool isAvaliable = Avaliable(board, row);
		if (true == isAvaliable)
		{
			DFS(board, N, row + 1, answer);
		}
	}
}

bool Avaliable(int* board, int row)
{
	bool retValue = true;

	for (int i = 0; i < row; i++)
	{
		// ¿­
		if ((board[i] == board[row]) ||
			(row - i == abs(board[i] - board[row])))
		{
			retValue = false;
			break;
		}
	}

	return retValue;
}
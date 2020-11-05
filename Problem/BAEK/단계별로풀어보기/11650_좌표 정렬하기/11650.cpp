#include <iostream>

// def
#define MAX_SIZE 100000

struct POINT
{
	int x;
	int y;
};

// method
void Swap(POINT* arr, int i, int j);
void QuickSort(POINT* arr, int start, int end);

int main()
{
	int N = 0;
	std::cin >> N;

	POINT ptList[MAX_SIZE + 1];
	for (int nIdx = 0; nIdx < N; nIdx++)
	{
		int x, y;
		x = y = 0;
		std::cin >> x >> y;

		POINT pt;
		pt.x = x;
		pt.y = y;
		ptList[nIdx] = pt;
	}


	return 0;
}

void Swap(POINT* arr, int i, int j)
{
	POINT temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void QuickSort(POINT* arr, int start, int end)
{
	POINT pivot = arr[start];
	int left = start + 1;
	int right = end;

	while (left <= right)
	{
		while (left <= end && arr[left].x < pivot.x)
		{
			if (arr[left].x == pivot.x)
			{
				if (arr[left].y > pivot.y)
					break;
				else
					left++;
			}
			else
				left++;
		}
	}
}
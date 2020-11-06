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

	QuickSort(ptList, 0, N - 1);

	for (int idx = 0; idx < N; idx++)
	{
		std::cout << ptList[idx].x << " " << ptList[idx].y << "\n";
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
	if (start >= end)
		return;

	POINT pivot = arr[start];
	int left = start + 1;
	int right = end;

	while (left <= right)
	{
		while (left <= end && 
				((arr[left].x < pivot.x) || (arr[left].x == pivot.x && arr[left].y < pivot.y)))
			left++;
		
		while (right > start &&
				(arr[right].x > pivot.x || (arr[right].x == pivot.x && arr[right].y > pivot.y)) )
			right--;

		if (left < right) // 교차가 안되었을 때는 left, right 교환
		{
			Swap(arr, left, right);
		}
		else { // 교차가 되었을 때는 pivot과 right 교환
			Swap(arr, start, right);
		}
	}

	QuickSort(arr, start, right-1);
	QuickSort(arr, right+1, end);
}
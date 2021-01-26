#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

// debug
#define debug_m 0

// define
#define MIN_VALUE -10000000000
#define MAX_VALUE 10000000000

// method
void Print(std::vector<long long> src, int heapSize);
void Swap(long long& lhs, long long& rhs);
void InsertProcMinHeap(std::vector<long long>& src, const int paramIdx);
long long DeleteProcMinHeap(std::vector<long long>& src, int& heapSize);

int main()
{
	// init
	std::ios::sync_with_stdio(false);

	// input
	int N, K;
	N = K = 0;
	(void)scanf("%d %d", &N, &K);

	std::vector<long long> inputLists;
	inputLists.resize(N + 1);
	std::fill(inputLists.begin(), inputLists.end(), MIN_VALUE - 1);

	for (int n = 1; n <= N; n++)
	{
		long long input = 0;
		(void)scanf("%lld", &input);
		inputLists[n] = input;

		// min heap's insert
		InsertProcMinHeap(inputLists, n);
	}

	// print
	long long answer = 0;
	int heapSize = N;
	for (int k = 0; k < K; k++)
	{
		answer = DeleteProcMinHeap(inputLists, heapSize);
	}
	printf("%lld\n", answer);

	return 0;
}

void Print(std::vector<long long> src, int heapSize)
{
	for (long long item : src)
	{
		printf("%lld ", item);
	}
	printf("heapSize : %d\n", heapSize);
}

void Swap(long long& lhs, long long& rhs)
{
	long long temp = lhs;
	lhs = rhs;
	rhs = temp;
}

void InsertProcMinHeap(std::vector<long long>& src, const int paramIdx)
{
#if debug_m
	printf("\n----[%s]----\n", __FUNCTION__);
#endif

	int curIdx = paramIdx;
	while (1 < paramIdx)
	{
		const int parentIdx = curIdx / 2;
		if (src[parentIdx] > src[curIdx])
		{
			Swap(src[parentIdx], src[curIdx]);
			curIdx = parentIdx;

#if debug_m
			Print(src, paramIdx);
#endif
		}
		else
			break;
	}
}

long long DeleteProcMinHeap(std::vector<long long>& src, int& heapSize)
{
#if debug_m
	printf("\n----[%s]----\n", __FUNCTION__);
#endif

	long long retValue = src[1];
	src[1] = MIN_VALUE - 1;
	Swap(src[1], src[heapSize]);
	heapSize--;

	int curIdx = 1;
	while (curIdx <= heapSize / 2)
	{
		const int leftChild = curIdx * 2;
		const int rightChild = leftChild + 1;

		int smallerChild = 0;
		if (curIdx * 2 + 1 <= heapSize)
		{
			if (src[leftChild] > src[rightChild])
				smallerChild = rightChild;
			else
				smallerChild = leftChild;
		}
		else
			smallerChild = leftChild;

		if (src[smallerChild] < src[curIdx])
		{
			Swap(src[smallerChild], src[curIdx]);
			curIdx = smallerChild;

#if debug_m
			Print(src, heapSize);
#endif
		}
		else
			break;
	}

#if debug_m
	printf("return : %lld\n", retValue);
#endif

	return retValue;
}
#include <iostream>
#include <algorithm>

#define MAX_SIZE 100000

struct Point {
	int x;
	int y;
};

bool compare(Point lhs, Point rhs)
{
	if (lhs.x == rhs.x)
	{
		return lhs.y < rhs.y;
	}

	return lhs.x < rhs.x;
}

int main()
{
	int N = 0;
	std::cin >> N;

	Point ptList[MAX_SIZE + 1];
	for (int nIdx = 0; nIdx < N; nIdx++)
	{
		int x, y;
		x = y = 0;
		std::cin >> x >> y;

		Point pt;
		pt.x = x;
		pt.y = y;
		ptList[nIdx] = pt;
	}

	std::sort(ptList, ptList + N, compare);

	for (int idx = 0; idx < N; idx++)
	{
		std::cout << ptList[idx].x << " " << ptList[idx].y << "\n";
	}

	return 0;
}
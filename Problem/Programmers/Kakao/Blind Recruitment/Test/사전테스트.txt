#include <iostream>
#include <vector>
#include <map>
using namespace std;


vector<int> solution(vector<vector<int>> v) {
	vector<int> ans;

	// x || y, count 
	map<int, int> xMap;
	map<int, int> yMap;
	for(auto data : v)
	{
		const int xVal = data[0];
		const int yVal = data[1];

		if(xMap.end() != xMap.find(xVal))
		{
			xMap[xVal]++;
		}
		else
		{
			xMap[xVal] = 0;
		}

		if(yMap.end() != yMap.find(yVal))
		{
			yMap[yVal]++;
		}
		else
		{
			yMap[yVal] = 0;
		}
	} //

	for(auto x : xMap)
	{
		if(0 == x.second)
		{
			ans.push_back(x.first);
			break;
		}
	}

	for(auto y : yMap)
	{
		if(0 == y.second)
		{
			ans.push_back(y.first);
			break;
		}
	}

	return ans;
}

int main()
{
	std::vector<vector<int>> vec;
	std::vector<int> xy;
	xy.push_back(1);
	xy.push_back(1);
	vec.push_back(xy);

	xy.erase(xy.begin());
	xy.push_back(2);
	xy.push_back(2);
	vec.push_back(xy);

	xy.erase(xy.begin());
	xy.push_back(1);
	xy.push_back(2);
	vec.push_back(xy);
	vector<int> ans = solution(vec);


	return 0;
}
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    // order, count
    unordered_map<string, int> savedList;

    for(string& order : orders)
    {
        sort(order.begin(), order.end());
        for(int i = 0; i < (1 << order.size()); i++)
        {
            //printf("{ ");
            string combiOrder;
            for(int j = 0; j < order.size(); j++)
            {
                if(0 != (i & (1 << j)))
                {
                    combiOrder += order[j];
                }
            }
            savedList[combiOrder]++;

            /*printf("%s %d", combiOrder.c_str(), savedList[combiOrder]);
            printf("}\n");*/
        }
    }
    
    for(int num : course)
    {
        vector<pair<string, int>> list;
        int max = -1;
        for(auto savedItem : savedList)
        {
            if(num == savedItem.first.size() && 2 <= savedItem.second)
            {
                list.push_back(savedItem);
                max = max < savedItem.second ? savedItem.second : max;
            }
        }

        for(auto data : list)
        {
            if(max == data.second)
            {
                answer.push_back(data.first);
            }
        }
    }
    sort(answer.begin(), answer.end());

    return answer;
}


int main()
{
    vector<string> orders;
    orders.push_back("XYZ");
    orders.push_back("XWY");
    orders.push_back("WXA");
    //orders.push_back("ADE");
    //orders.push_back("XYZ");
    //orders.push_back("XYZ");
    //orders.push_back("ACD");
    vector<int> course;
    course.push_back(2);
    course.push_back(3);
    course.push_back(4);
    vector<string> answer = solution(orders, course);

    for(string ans : answer)
    {
        printf("%s \n", ans.c_str());
    }

    return 0;
}
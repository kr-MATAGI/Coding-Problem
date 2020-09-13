#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#define BOX_MAX 1000000

int solution(vector<vector<int>> boxes) {
    int answer = -1;

    
    //item, count
    int boxArr[BOX_MAX + 1] = { 0, };
    int max = -1;
    for(int boxIdx = 0; boxIdx < boxes.size(); boxIdx++)
    {   
        int item_1 = boxes[boxIdx][0];
        int item_2 = boxes[boxIdx][1];
        max = max < item_1 ? item_1 : max;
        max = max < item_2 ? item_2 : max;

        boxArr[item_1]++;
        boxArr[item_2]++;
    }

    int sum = 0;
    for(int idx = 0; idx <= max; idx++)
    {
        if(0 != (boxArr[idx] % 2))
        {
            sum++;
        }
    }
    answer = sum / 2;

    return answer;
}


int main()
{
    vector<vector<int>> boxes;
    vector<int> box;
    
    box.push_back(1);
    box.push_back(2);
    boxes.push_back(box);
    box.erase(box.begin(), box.end());

    box.push_back(2);
    box.push_back(1);
    boxes.push_back(box);
    box.erase(box.begin(), box.end());

    box.push_back(3);
    box.push_back(3);
    boxes.push_back(box);
    box.erase(box.begin(), box.end());

    box.push_back(4);
    box.push_back(5);
    boxes.push_back(box);
    box.erase(box.begin(), box.end());

    box.push_back(5);
    box.push_back(6);
    boxes.push_back(box);
    box.erase(box.begin(), box.end());

    box.push_back(7);
    box.push_back(8);
    boxes.push_back(box);
    box.erase(box.begin(), box.end());

    int answer = solution(boxes);

    printf("%d\n", answer);

    return 0;
}
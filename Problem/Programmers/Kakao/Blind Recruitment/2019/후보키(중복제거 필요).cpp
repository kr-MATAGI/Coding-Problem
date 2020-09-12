#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

#define COLUMN_MAX 8
#define ROW_MAX 20

#define DEBUG_CODE 1

int solution(vector<vector<string>> relation) {
    int answer = 0;

    const int rowMaxSize = relation.size();
    const int columnMaxSize = relation[0].size();

    bool usedFlag[COLUMN_MAX + 1] = { 0, };
    for(int combIdx = 0; combIdx < (1 << columnMaxSize); combIdx++)
    {
        set<string> compareList;
        for(int row = 0; row < rowMaxSize; row++)
        {
            string madeStr;
            for(int col = 0; col < columnMaxSize; col++)
            {
                if(0 != (combIdx & (1 << col)))
                {
                    madeStr += relation[row][col];
                }
            }
#if DEBUG_CODE
            printf("%s \n", madeStr.c_str());
#endif
            compareList.insert(madeStr);
        }

        if(rowMaxSize == compareList.size())
        {
#if DEBUG_CODE
            printf("---->inserted !\n");
#endif
            answer++;
        }
#if DEBUG_CODE
        printf("-----\n");
#endif
    }

#if DEBUG_CODE
    printf("%s(%d) { answer : %d }\n", __FUNCTION__, __LINE__, answer);
#endif

    return answer;
}

int main()
{
#if 0
    int n = 6;
    int arr[6] = { 3,4,5,7,8,9 };

    for(int i = 0; i < (1 << n); i++) { // 부분집합의 개수 만큼 loop
        printf("{ ");
        for(int j = 0; j < n; j++) { // 배열 내 반복
            if(0 != (i & (1 << j)))
            {
                printf("%d ", arr[j]);
            }
        }
        printf("}\n");
    }
#endif

    vector<vector<string>> relation;
    vector<string> data;

    data.push_back("100");
    data.push_back("ryan");
    data.push_back("music");
    data.push_back("2");
    relation.push_back(data);
    data.erase(data.begin(), data.end());

    data.push_back("200");
    data.push_back("apeach");
    data.push_back("math");
    data.push_back("2");
    relation.push_back(data);
    data.erase(data.begin(), data.end());

    data.push_back("300");
    data.push_back("tube");
    data.push_back("computer");
    data.push_back("3");
    relation.push_back(data);
    data.erase(data.begin(), data.end());

    data.push_back("400");
    data.push_back("con");
    data.push_back("computer");
    data.push_back("4");
    relation.push_back(data);
    data.erase(data.begin(), data.end());

    data.push_back("500");
    data.push_back("muzi");
    data.push_back("music");
    data.push_back("3");
    relation.push_back(data);
    data.erase(data.begin(), data.end());

    data.push_back("600");
    data.push_back("apeach");
    data.push_back("music");
    data.push_back("2");
    relation.push_back(data);
    data.erase(data.begin(), data.end());

    const int answer = solution(relation);


    return 0;
}
#include <string>
#include <vector>
#include <string.h>

using namespace std;

#define N_MAX_SIZE 1000000000

vector<int> solution(int n) {
    vector<int> answer;

    string nStr = to_string(n);
    
    int plusCnt = 0;
    while(true)
    {
        if(1 == nStr.size())
        {
            answer.push_back(plusCnt);
            answer.push_back(atoi(nStr.c_str()));
            break;
        }

        std::vector<int> calcNumList;
        const int nStrSize = static_cast<int>(nStr.size());
        for(int idx = 0; idx < nStrSize; idx++)            
        {
            string leftStr = nStr.substr(0, idx+1);
            string rightStr = nStr.substr(idx + 1);
            if((1 != leftStr.size() &&'0' == leftStr[0]) || 
                (1 != rightStr.size() && '0' == rightStr[0]))
            {
                continue;
            }

            int leftNum = atoi(leftStr.c_str());
            int rightNum = atoi(rightStr.c_str());
            int sumNum = leftNum + rightNum;
            calcNumList.push_back(sumNum);
        }

        // search minum value
        int min = N_MAX_SIZE + 1;
        for(const int item : calcNumList)
        {
            min = min > item ? item : min;
        }
        nStr = to_string(min);
        
        plusCnt++;
    }

    return answer;
}
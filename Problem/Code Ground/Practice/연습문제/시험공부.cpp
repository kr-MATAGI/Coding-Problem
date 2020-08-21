#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

int main()
{
    setbuf(stdout, NULL);    

    int testCase = 0;
    scanf("%d", &testCase);

    for(int tIdx = 0; tIdx < testCase; tIdx++)
    {
        int NCnt = 0;
        int KCnt = 0;

        scanf("%d %d", &NCnt, &KCnt);

        // SET INPUT
        std::vector<int> inputList;
        inputList.reserve(NCnt);
        for(int nIdx = 0; nIdx < NCnt; nIdx++)
        {
            int inputValue = 0;
            scanf("%d", &inputValue);

            inputList.push_back(inputValue);
        }

        // CALCULATION
        std::sort(inputList.begin(), inputList.end());

        int result = 0;
        int resultCnt = 0;
        for(int nIdx = NCnt - 1; nIdx >= 0; nIdx--)
        {
            result += inputList[nIdx];
            resultCnt++;

            if( resultCnt == KCnt )
            {
                break;
            }
        }

        // PRINT
        printf("Case #%d\n%d\n", (tIdx+1), result);
    }

    return 0;
}
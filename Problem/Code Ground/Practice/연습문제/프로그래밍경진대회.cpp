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
        int result = 0;
        int NCnt = 0;
        scanf("%d", &NCnt);

        // SET INPUT
        std::vector<int> inputList;
        inputList.reserve(NCnt);
        for(int nIdx = 0; nIdx < NCnt; nIdx++)
        {
            int inputData = 0;
            scanf("%d", &inputData);

            inputList.push_back(inputData);
        }

        // CACULATION MAX
        std::sort(inputList.begin(), inputList.end());
        
        std::vector<int> maxCalcList(inputList);
        int maxValue = -1;
        for(int nIdx = 0; nIdx < NCnt; nIdx++)
        {
            maxCalcList.at(nIdx) = maxCalcList.at(nIdx) + (NCnt - nIdx);

            if( maxValue < maxCalcList.at(nIdx))
            {
                maxValue = maxCalcList.at(nIdx);
            }
        }

        // CALCULATION RESULT
        for(int nIdx = 0; nIdx < NCnt; nIdx++)
        {
            if( maxValue <= inputList.at(nIdx) + NCnt )
            {
                result++;
            }
        }

        // PRINT RESULT
        printf("Case #%d\n%d\n", (tIdx+1), result);
    }

    return 0;
}
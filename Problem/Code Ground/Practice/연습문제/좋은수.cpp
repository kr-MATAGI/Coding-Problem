#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

// Define
#define ABS_MAX_VALUE 2000000
#define DEBUG_CODE 0

// Global
bool g_GoodNumbFlag[ABS_MAX_VALUE * 2 + 1];

// Method
bool IsGoodNumber(const std::vector<int>& inputList, const int currIdx);

int main()
{
    setbuf(stdout, NULL);

    int testCase = 0;
    scanf("%d", &testCase);

    for(int tIdx = 0; tIdx < testCase; tIdx++)
    {
        memset(g_GoodNumbFlag, false, sizeof(g_GoodNumbFlag));
        int answer = 0;

        int N_input = 0;
        scanf("%d", &N_input);

        std::vector<int> inputList;
        inputList.reserve(N_input);
        for(int nIdx = 0; nIdx < N_input; nIdx++)
        {
            int inputValue = 0;
            scanf("%d", &inputValue);

            inputList.push_back(inputValue);
        }

        // Calc
        for(int nIdx = 0; nIdx < N_input; nIdx++)
        {
            const bool bIsGoodNumb = IsGoodNumber(inputList, nIdx);
            if( true == bIsGoodNumb )
            {
                #if DEBUG_CODE
                    printf("goodNmb : %d\n", inputList[nIdx]);
                #endif
                answer++;
            }
        }

        // Print
        printf("Case #%d\n%d\n", (tIdx+1), answer);
    }

    // debug
#if DEBUG_CODE
    for(int i = 0; i < ABS_MAX_VALUE * 2 + 1; i++)
    {
        if( g_GoodNumbFlag[i] == true )
        {
            printf("idx : %d true \n", i);
        }
    }
#endif

    return 0;
}

// Method Code
bool IsGoodNumber(const std::vector<int>& inputList, const int currIdx)
{
    bool retValue = false;

    const int inputListSize = static_cast<int>(inputList.size());
    for(int kIdx = 0; kIdx < currIdx; kIdx++)
    {
        const int rightValue = inputList[currIdx] - inputList[kIdx];
        if (true == g_GoodNumbFlag[rightValue + ABS_MAX_VALUE])
        {
            retValue = true;
            g_GoodNumbFlag[rightValue + ABS_MAX_VALUE] = true;
        }
    }

    for(int iIdx = 0; iIdx <= currIdx; iIdx++)
    {
        const int leftValue = inputList[currIdx] + inputList[iIdx];
        g_GoodNumbFlag[leftValue + ABS_MAX_VALUE] = true;
    }

    return retValue;
}
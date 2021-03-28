#include <iostream>
#include <vector>

#define N_MAX_SIZE 20
#define S_SUM_MAX 201

// typedef
typedef std::vector<std::vector<int>> INPUT_VEC;

// method
int CalcStartAndLink(const INPUT_VEC &src, const int N);

// main
int main()
{
    std::ios::sync_with_stdio(false);

    // input
    int N = 0; // 4<= N <= 20 (even)
    scanf("%d", &N);

    INPUT_VEC inputList;
    inputList.reserve(N);
    for (int nRow = 0; nRow < N; nRow++)
    {
        std::vector<int> colInput;
        colInput.reserve(N);
        for (int nCol = 0; nCol < N; nCol++)
        {
            int nInput = 0;
            scanf("%d", &nInput);
            colInput.push_back(nInput);
        }
        inputList.push_back(colInput);
    }

    // minmun calc
    int answer = CalcStartAndLink(inputList, N);

    // print
    printf("%d\n", answer);

    return 0;
}

int CalcStartAndLink(const INPUT_VEC &src, const int N)
{
    int retValue = 0;

    const int teamHumanCnt = N / 2;
    for (int i = 0; i < N; i++)
    {
        bool bIsChecked[N_MAX_SIZE + 1];
        std::fill(bIsChecked, bIsChecked + (N_MAX_SIZE + 1), false);
        
        bIsChecked[i] = true;
        int minValue = S_SUM_MAX;

        // start
        int startSum = 0;
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;

            if (false == bIsChecked[j])
            {
                for (int t = 0; t < teamHumanCnt; t++)
                {
                    bIsChecked[j] = true;
                    const int ijValue = src[i][j];
                    const int jiValue = src[j][i];
                    startSum += (ijValue + jiValue);
                }
            }
        }

        // link
        int linkSum = 0;
        for(int j = 0; j < N; j++)
        {
            if(i == j)
                continue;

            if(true == bIsChecked[j])
                continue;

            for(int k = 0; k < N; k++)
            {
                if(true == bIsChecked[k])
                    continue;
                    
                for(int t = 0; t < teamHumanCnt; t++)
                {
                    bIsChecked[j] = true;
                    bIsChecked[k] = true;
                    const int jkValue = src[j][k];
                    const int kjValue = src[k][j];
                    linkSum += (jkValue + kjValue);
                }
            }
        }

        int startLinkValue = std::abs(startSum - linkSum);
        minValue = minValue < startLinkValue ? minValue : startLinkValue;
        retValue = minValue;
    }

    return retValue;
}
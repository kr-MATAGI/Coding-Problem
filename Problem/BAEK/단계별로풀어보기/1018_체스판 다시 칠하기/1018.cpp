#include <iostream>
#include <string.h>

#define MAX_ARR_SIZE 50
#define BOARD_SIZE 8

int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    char inputArr[MAX_ARR_SIZE + 1][MAX_ARR_SIZE + 1];
    for(int idx = 0; idx < MAX_ARR_SIZE + 1; idx++)
    {
        memset(inputArr[idx], 0, MAX_ARR_SIZE+1);
    }
    for(int nIdx = 0; nIdx < N; nIdx++)
    {
        std::cin >> inputArr[nIdx];
    }

    int answerMin = BOARD_SIZE * BOARD_SIZE + 1;
    for(int rowS = 0; rowS < N-(BOARD_SIZE-1); rowS++)
    {
        for(int colS = 0; colS < M-(BOARD_SIZE-1); colS++)
        {
            int cntW = 0;
            int cntB = 0;
            for(int i = rowS; i < rowS + BOARD_SIZE; i++)
            {
                for(int j = colS; j < colS + BOARD_SIZE; j++)
                {
                    if( 0 == (i+j) % 2)
                    {
                        if(inputArr[i][j] == 'B')
                        {
                            cntW++;
                        }
                        else
                        {
                            cntB++;
                        }
                    }
                    else
                    {
                        if(inputArr[i][j] == 'B')
                        {
                            cntB++;
                        }
                        else
                        {
                            cntW++;
                        }
                    }
                }
            }
            answerMin = answerMin > cntB ? cntB : answerMin;
            answerMin = answerMin > cntW ? cntW : answerMin;
        }
    }

    std::cout << answerMin << std::endl;
    
    return 0;
}
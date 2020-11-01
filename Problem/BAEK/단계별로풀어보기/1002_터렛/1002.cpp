#include <iostream>
#include <math.h>
#include <vector>

int main()
{
    int testCase = 0;
    std::cin >> testCase;

    std::vector<int> answerList;
    for(int tIdx = 0; tIdx < testCase; tIdx++) 
    {        
        // https://mathbang.net/101
        int x_1, y_1, r_1;
        int x_2, y_2, r_2;
        x_1 = y_1 = r_1 = x_2 = y_2 = r_2 = 0;
        std::cin >> x_1 >> y_1 >> r_1 >> x_2 >> y_2 >> r_2;

        double d = 0.0; // 두 터렛 사이의 거리
        d = pow((x_2-x_1), 2) + pow((y_2 - y_1), 2);

        if( abs(r_2) < abs(r_1))
        {
            int temp = r_2;
            r_2 = r_1;
            r_1 = temp;
        }
        int plusR = r_1 + r_2;
        plusR *= plusR;
        int minusR = r_2 - r_1;
        minusR *= minusR;

        // printf("d : %lf plusR : %d minusR : %d \n", d, plusR, minusR);
        if(x_2 == x_1 && y_2 == y_1 && r_2 == r_1)
        {
            answerList.push_back(-1);
        }
        else if( minusR < d && d < plusR )
        {
            answerList.push_back(2);
        }
        else if( plusR == d || minusR == d )
        {
            answerList.push_back(1);
        }
        else if( plusR < d || d < minusR || 0 == d)
        {
            answerList.push_back(0);
        }
        else
        {
            answerList.push_back(-1);
        }
        
    }

    // print answers
    for(const int ans : answerList)
    {
        std::cout << ans << std::endl;
    }

    return 0;
}
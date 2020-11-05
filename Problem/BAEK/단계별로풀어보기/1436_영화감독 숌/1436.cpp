#include <iostream>

int main()
{
    /**
     * 간단하게 생각할 것, mod 연산활용
     */ 
    int N = 0;
    std::cin >> N;

    int count = 0;
    for (int number = 1; ;number++)
    {
        int tempNum = number;
        bool isFind = false;
        while (true)
        {
            if (666 == tempNum % 1000)
            {
                count++;
                if(N == count)
                {
                    isFind = true;
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (0 == tempNum / 10)
                {
                    break;
                }
                else
                {
                    tempNum /= 10;
                }
            }
        }

        if(true == isFind)
        {
            std::cout << number <<std::endl;
            break;
        }
    }

    return 0;
}
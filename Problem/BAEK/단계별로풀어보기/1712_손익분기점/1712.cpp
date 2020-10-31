#include <iostream>

int main()
{
    long long A = 0; // 고정비용
    long long B = 0; // 가변비용
    long long C = 0; // 책정가
    std::cin >> A >> B >> C;

    if ( B >= C)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        int answer = A / (C - B);
        std::cout << answer + 1 << std::endl;
    }

    return 0;
}

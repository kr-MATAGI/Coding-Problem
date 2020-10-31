#include <iostream>
#include <math.h>

int main()
{
    int R = 0;
    std::cin >> R;

    const double PI = std::acos(-1);
    double answer_1 = 0.0;
    double answer_2 = 0.0;

    answer_1 = R * R * PI;
    answer_2 = 4.0 * ((R*R) / 2.0);

    printf("%.6f\n%.6f\n", answer_1, answer_2);

    return 0;
}
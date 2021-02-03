#include <iostream>
#include <vector>

// size
#define INPUT_MAX_SIZE 1000000

// debug
#define debug_m 0

// method
long long Calc(const int src, const int B, const int C);

int main()
{
    // init
    std::ios::sync_with_stdio(false);

    // input
    int N = 0; // 시험장의 개수
    (void)scanf("%d", &N);

    std::vector<int> ALists;
    for (int n = 0; n < N; n++)
    {
        int A = 0; // 각 시험장마다 응시생 수
        (void)scanf("%d", &A);
        ALists.push_back(A);
    }

    int B, C; // 총, 부감독관이 한 시험장에서 감시할 수 있는 수
    B = C = 0;
    (void)scanf("%d %d", &B, &C);

    // calc
    /**
     * 각각의 시험장에 총 감독관은 오직 1명
     * 부감독관은 여러명 있어도 된다.
     * 총감독관 없이 부감독관만 있어도 되는가?
     * */
    long long answer = 0;
    for (int humman : ALists)
    {
        answer += Calc(humman, B, C);
    }

    // print
    printf("%lld\n", answer);

    return 0;
}

// mehtod
long long Calc(const int src, const int B, const int C)
{
    long long retValue = 0;

#if debug_m
    printf("src: %d, B: %d, C: %d\n", src, B, C);
#endif

    int data = src;
    if (B >= data)
        retValue = 1;
    else
    {
        data -= B;
        retValue += 1;

        retValue += data / C;
        const int modValue = data % C;
        if (0 != modValue)
            retValue += 1;
    }

    return retValue;
}
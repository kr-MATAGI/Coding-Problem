#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

/**
 * 두 점 사이의 거리
 * (x2 - x1)^2 + (y2 - y1)^2 = d^2
 */

// definition
int scoreArray[] = { 6, 13, 4, 18, 1 ,20,
                     5, 12, 9, 14, 11,
                     8, 16, 7, 19, 3,
                     17, 2, 15, 10, 6 };

enum AREAS_t
{
    e_OUT_BOUND = 0,
    e_SINGLE = 1,
    e_DOUBLE = 2,
    e_TRIPLE = 3,
    e_BULL = 4,
};

struct POINT_t
{
    POINT_t(int _x, int _y, AREAS_t _areas)
    : x_point(_x)
    , y_point(_y)
    , areas(_areas)
    {

    }

    int x_point;
    int y_point;
    AREAS_t areas;
};

struct DARTPAN_t
{
    DARTPAN_t(int _bull, int _ts, int _te, int _ds, int _de)
    : bull(_bull)
    , triple_start(_ts)
    , triple_end(_te)
    , double_start(_ds)
    , double_end(_de)
    {

    }

    int bull;
    int triple_start;
    int triple_end;
    int double_start;
    int double_end;
};

// global
DARTPAN_t g_dart(0, 0, 0, 0, 0);

// method
AREAS_t CalculateAreas(const int xValue, const int yValue);
int CalculateScore(POINT_t &rSrc);

int main()
{
    setbuf(stdout, NULL);

    int testCase = 0;
#if 0
/*
 * @Note : atan2() 함수로 구한 각도는 radian 단위를 사용하므로 180/pi 를 곱해야 '각도'가 나온다. 
 */
    const double deg = 180 / M_PI;
    const double angle = atan2(55, 0) * deg;

#endif
    scanf("%d", &testCase);

    for(int tIdx = 0; tIdx < testCase; tIdx++)
    {
        int result = 0;

        // SET INPUT
        int A_input = 0; // BULL's 반지름
        int B_input = 0; // TRIPLE's 시작구간 반지름
        int C_input = 0; // TRIPLE's 종료구간 반지름
        int D_input = 0; // DOUBLE's 시작구간 반지름
        int E_input = 0; // DOUBLE's 종료구간 반지름

        scanf("%d %d %d %d %d", &A_input, &B_input, &C_input, &D_input, &E_input);
        DARTPAN_t dartInput(A_input, B_input, C_input, D_input, E_input);
        g_dart = dartInput;

        int N_input = 0;
        scanf("%d", &N_input);

        for(int nIdx = 0; nIdx < N_input; nIdx++)
        {
            int x_input = 0;
            int y_input = 0;
            scanf("%d %d", &x_input, &y_input);

            // CALCULATION AREAS
            const AREAS_t calcAreas = CalculateAreas(x_input, y_input);
            POINT_t point(x_input, y_input, calcAreas);

            // CALCULATION SCORE
            const int calcScore = CalculateScore(point);
            result += calcScore;
        }        

        // PRINT
        printf("Case #%d\n%d\n", (tIdx+1), result);
    }

    return 0;
}


// method
AREAS_t CalculateAreas(const int xValue, const int yValue)
{
    AREAS_t retValue = AREAS_t::e_OUT_BOUND;

    // (0,0) ~ (xValue, yValue) 
    // (x2 - x1)^2 + (y2 - y1)^2 = d^2
    const double d_pow = sqrt((xValue * xValue) + (yValue * yValue));

    // Check Areas
    if( g_dart.bull >= d_pow )
    {
        retValue = AREAS_t::e_BULL;
    }
    else if( (g_dart.triple_start <= d_pow ) &&
             (g_dart.triple_end >= d_pow) )
    {
        retValue = AREAS_t::e_TRIPLE;
    }
    else if( (g_dart.double_start <= d_pow) &&
             (g_dart.double_end >= d_pow) )
    {
        retValue = AREAS_t::e_DOUBLE;
    }
    else if( g_dart.double_end < d_pow )
    {
        retValue = AREAS_t::e_OUT_BOUND;
    }
    else
    {
        retValue = AREAS_t::e_SINGLE;
    }

    return retValue;
}

int CalculateScore(POINT_t &rSrc)
{
    int retValue = 0;

    // check bull & out bound
    if( AREAS_t::e_BULL == rSrc.areas)
    {
        retValue = 50;
        return retValue;
    }
    else if( AREAS_t::e_OUT_BOUND == rSrc.areas )
    {
        retValue = 0;
        return retValue;
    }
    else
    {
        // calculate origin socre        
        const double angle_correction = 180 / M_PI;
        double angle = atan2((float)rSrc.y_point, (float)rSrc.x_point) * angle_correction;
        if( 0 > angle)
        {
            angle = 360 - (angle*(-1));
        }

        double startAngle = 0;
        double endAngle = 9;
        const int scoreArrSize = sizeof(scoreArray) / sizeof(int);
        for (int idx = 0; idx < scoreArrSize; idx++)
        {
            if( (startAngle <= angle) && (endAngle >= angle))
            {
                retValue = scoreArray[idx];
                break;
            }
            startAngle = endAngle;
            endAngle = startAngle + 18.0;
        }

        // check areas
        if( AREAS_t::e_DOUBLE == rSrc.areas )
        {
            retValue *= 2;
        }
        else if( AREAS_t::e_TRIPLE == rSrc.areas )
        {
            retValue *= 3;
        }
    }
    
    return retValue;
}
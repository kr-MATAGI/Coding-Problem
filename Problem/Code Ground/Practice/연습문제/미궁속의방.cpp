#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>

// Definition
#define DEBUG_CODE 0

// Move Direction
enum Move_t
{
    e_NOT = 0,
    e_UP = 1,
    e_DOWN = 2,
    e_LEFT = 3,
    e_RIGHT = 4,
};

struct Pos_t
{
    Pos_t(const int _row = 0, const int _col = 0)
    : row(_row)
    , col(_col)
    , currValue(1)
    , bIsUpRightSerarch(true)
    {
    }
    int row;
    int col;
    int currValue;
    bool bIsUpRightSerarch;
};

// Method
Move_t MoveTypeConvertCharToEnum(const char newValue);
void GetTurnningPointValueList(std::vector<int> &rDest, const int N_input);
Pos_t GetDestPositionInfo(Move_t moveType, const Pos_t &currPos);
uint64_t GetCalculatedValue(const std::vector<Move_t> &rSrc, const int N_input);

int main()
{
    setbuf(stdout, NULL);

    int testCase = 0;
    scanf("%d", &testCase);

    for (int tIdx = 0; tIdx < testCase; tIdx++)
    {
        // Set Input
        int N_input = 0;
        int K_input = 0;
        scanf("%d %d\n", &N_input, &K_input);

        std::vector<Move_t> moveDirList;
        moveDirList.reserve(K_input);
        for (int kIdx = 0; kIdx < K_input; kIdx++)
        {
            char moveDir = '\0';
            scanf("%c", &moveDir);

            const Move_t moveEnumType = MoveTypeConvertCharToEnum(moveDir);
            moveDirList.push_back(moveEnumType);
        }

        // Calculate Answer
        const uint64_t answer = GetCalculatedValue(moveDirList, N_input);

        // Print Answer
        printf("Case #%d\n%llu\n", (tIdx + 1), answer);
    }

    return 0;
}

// Method Code
Move_t MoveTypeConvertCharToEnum(const char newValue)
{
    Move_t retValue = Move_t::e_NOT;

    switch (newValue)
    {
    case 'U':
        retValue = Move_t::e_UP;
        break;

    case 'D':
        retValue = Move_t::e_DOWN;
        break;

    case 'L':
        retValue = Move_t::e_LEFT;
        break;

    case 'R':
        retValue = Move_t::e_RIGHT;
        break;

    default:
        retValue = Move_t::e_NOT;
        break;
    }

    return retValue;
}

void GetTurnningPointValueList(std::vector<int> &rDest, const int N_input)
{
    int turnningPointValue = 1;
    int plusValue = 0;
    bool bIsAdding = true;

    while (true)
    {
        // loop stop
        if ((N_input * N_input) == turnningPointValue)
        {
            rDest.push_back(turnningPointValue);    
            break;
        }

        if (N_input == plusValue)
        {
            bIsAdding = false;
        }

        if (true == bIsAdding)
        {
            plusValue++;
        }
        else
        {
            plusValue--;
        }
        rDest.push_back(turnningPointValue);

        turnningPointValue += plusValue;
    }

#if DEBUG_CODE
    std::cout << "trunning Point Value : ";
    for (const int value : rDest)
    {
        std::cout << "( " << value << " ), ";
    }
    std::cout << "Size : " << rDest.size() << std::endl;
#endif
}

Pos_t GetDestPositionInfo(Move_t moveType, const Pos_t &currPos)
{
    Pos_t destPos;

    if (Move_t::e_UP == moveType)
    {
        destPos.row = currPos.row - 1;
        destPos.col = currPos.col;
    }
    else if (Move_t::e_DOWN == moveType)
    {
        destPos.row = currPos.row + 1;
        destPos.col = currPos.col;
    }
    else if (Move_t::e_LEFT == moveType)
    {
        destPos.row = currPos.row;
        destPos.col = currPos.col - 1;
    }
    else if (Move_t::e_RIGHT == moveType)
    {
        destPos.row = currPos.row;
        destPos.col = currPos.col + 1;
    }
    else
    {
        // ERROR
    }

    if (true == currPos.bIsUpRightSerarch)
    {
        destPos.bIsUpRightSerarch = false;
    }
    else
    {
        destPos.bIsUpRightSerarch = true;
    }

#if DEBUG_CODE
    std::cout << "Dest Pos - row : " << destPos.row << ", col : " << destPos.col << std::endl;
#endif

    return destPos;
}

uint64_t GetCalculatedValue(const std::vector<Move_t> &rSrc, const int N_input)
{
    uint64_t retValue = 1;

    // Get turnning Point Value
    std::vector<int> turnningPointList;
    GetTurnningPointValueList(turnningPointList, N_input);
    const int turnningPtListSize = static_cast<int>(turnningPointList.size());

    Pos_t currPos;
#if DEBUG_CODE
    currPos.row = 0;
    currPos.col = 0;
    currPos.bIsUpRightSerarch = true;
    currPos.currValue = 1;
#endif

    for (const Move_t moveValue : rSrc)
    {
#if DEBUG_CODE
    std::cout << "----------" << std::endl;
    std::cout << "Current Pos - row : " << currPos.row << ", col : " << currPos.col << ", value : " << currPos.currValue 
            << ", UpRight : " << currPos.bIsUpRightSerarch << std::endl;
#endif

        Pos_t destPos = GetDestPositionInfo(moveValue, currPos);
        const int pointSum = destPos.row + destPos.col;
        if( 0 == (pointSum % 2) )
        {
            destPos.bIsUpRightSerarch = true;
        }
        else
        {
            destPos.bIsUpRightSerarch = false;
        }

        int calcResult = 0;
        if( (destPos.row == 0) && 
            (destPos.col == 0) )
        {
            calcResult = 1;
        }
        else if( (destPos.row == N_input - 1) &&
                (destPos.col == N_input - 1) )
        {
            calcResult = N_input * N_input;
        }
        else if( true == destPos.bIsUpRightSerarch )
        {
            if( pointSum >= N_input )
            {
                calcResult += turnningPointList[pointSum];
                calcResult += (N_input - 1);
                calcResult -= destPos.row;
            }
            else
            {
                calcResult += turnningPointList[pointSum];
                calcResult += destPos.col;
            }            
        }
        else
        {
            if( pointSum >= N_input )
            {
                calcResult += turnningPointList[pointSum];
                calcResult += (N_input - 1);
                calcResult -= destPos.col;
            }
            else
            {
                calcResult += turnningPointList[pointSum];
                calcResult += destPos.row;
            }
        }

        retValue += calcResult;

        destPos.currValue = calcResult;
        currPos = destPos;

#if DEBUG_CODE
        std::cout << "Current Pos - row : " << currPos.row << ", col : " << currPos.col << ", value : " << currPos.currValue 
            << ", Move Type : " << moveValue << ", result : " << retValue << std::endl;
#endif
    }

    return retValue;
}
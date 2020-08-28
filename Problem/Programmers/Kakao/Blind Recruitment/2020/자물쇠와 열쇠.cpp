#include <string>
#include <vector>
#include <string.h>

using namespace std;

#define DEBUG_LINE 1
#define MAX_ARR_SIZE 20
#define MAX_PADDING_SIZE 63

/**
 * 현재 79 점
 * 잠겨있는 자물쇠의 한 칸의 크기 => 1 x 1
 * 자물쇠는 N x N 의 정사각형 격자
 * 열쇠는 M x M 크기의 정사각형 격자
 *
 * 자물쇠는 홈이 파여있고, 열쇠 또한 홈과 돌기가 있다
 * 열쇠는 회전과 이동이 가능하며 자물쇠의 홈 부분에 돌기가 딱 맞게 되면 열린다.
 * 자물쇠 영역을 벗어난 부분의 열쇠의 홈은 영향 없는 부분
 * 열쇠의 돌기가 자물쇠의 돌기를 만나서는 안된다
 * 자물쇠의 모든 홈을 채워야 된다. (자물쇠는 비어있는 곳이 있으면 안된다)
 *
 * 3 <= M <= N <= 20
 * 0은 홈, 1은 돌기
 *
 * 열 수 있으면 true, 없으면 false
 */


void MakeRotatedKeyArr(const vector<vector<int>>& key, int arr[][MAX_ARR_SIZE + 1], const unsigned int size)
{
	for(unsigned int row = 0; row < size; row++)
	{
		for(unsigned int col = 0; col < size; col++)
		{
			arr[row][col] = key[row][col];
		}
	}
}

void MakeRotatedKeyArr(const int src[][MAX_ARR_SIZE + 1], int dest[][MAX_ARR_SIZE + 1], const unsigned int size)
{
	vector<int> numberSet;
	for(int col = 0; col < size; col++)
	{
		for(int row = (size - 1); row >= 0; row--)
		{
			numberSet.push_back(src[row][col]);
		}
	}

	int index = 0;
	for(int row = 0; row < size; row++)
	{
		for(int col = 0; col < size; col++)
		{
			dest[row][col] = numberSet[index];
			index++;
		}
	}
}

bool CheckFit(int keyArr[][MAX_ARR_SIZE + 1], int lockArr[][MAX_PADDING_SIZE + 1], int startRow, int startCol, int keySize,
	int insertStart, int insertEnd)
{
	bool retValue = true;

	std::vector<int> keyVector;
	for(int row = 0; row < keySize; row++)
	{
		for(int col = 0; col < keySize; col++)
		{
			keyVector.push_back(keyArr[row][col]);
		}
	}

	int copyArray[MAX_PADDING_SIZE + 1][MAX_PADDING_SIZE + 1] = { 0, };
	for(int row = 0; row < MAX_PADDING_SIZE + 1; row++)
	{
		memcpy(copyArray[row], lockArr[row], (MAX_PADDING_SIZE + 1) * sizeof(int));
	}

	int vecIdx = 0;
	for(int row = startRow; row < (startRow + keySize); row++)
	{
		for(int col = startCol; col < (startCol + keySize); col++)
		{
			copyArray[row][col] += keyVector[vecIdx];
			vecIdx++;
		}
	}

	// check lockArray's value is 1
	for(int row = insertStart; row <= insertEnd; row++)
	{
		for(int col = insertStart; col <= insertEnd; col++)
		{
			if(1 != copyArray[row][col])
			{
				retValue = false;
				return retValue;
			}
		}
	}

	return retValue;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = false;

	const unsigned int keyRowSize = key.size();
	const unsigned int keyColSize = keyRowSize;

	const unsigned int lockRowSize = lock.size();
	const unsigned int lockColSize = lockRowSize;

	// add padding to lock
	int paddingLockArr[MAX_PADDING_SIZE + 1][MAX_PADDING_SIZE + 1] = { 0, };
	const int insertStart = keyRowSize - 1;
	const int insertEnd = insertStart + (lockRowSize - 1);

	int lockRowIdx = 0;
	int lockColIdx = 0;
	for(int row = 0; row < MAX_PADDING_SIZE + 1; row++)
	{
		for(int col = 0; col < MAX_PADDING_SIZE + 1; col++)
		{
			if((insertStart <= row) && (insertEnd >= row))
			{
				if((insertStart <= col) && (insertEnd >= col))
				{
					paddingLockArr[row][col] = lock[lockRowIdx][lockColIdx];

					lockColIdx++;
					if(lockRowSize <= lockColIdx)
					{
						lockColIdx = 0;
						lockRowIdx++;
					}
				}
			}
		}
	}

	// make 4 direction Key Array
	// origin, once (한번 오른쪽), second (두번 오른쪽), thrid (세번 오른쪽)
	int originKeyArr[MAX_ARR_SIZE + 1][MAX_ARR_SIZE + 1] = { 0, };
	int onceKeyArr[MAX_ARR_SIZE + 1][MAX_ARR_SIZE + 1] = { 0, };
	int secondKeyArr[MAX_ARR_SIZE + 1][MAX_ARR_SIZE + 1] = { 0, };
	int thirdKeyArr[MAX_ARR_SIZE + 1][MAX_ARR_SIZE + 1] = { 0, };

	MakeRotatedKeyArr(key, originKeyArr, keyRowSize);
	MakeRotatedKeyArr(originKeyArr, onceKeyArr, keyRowSize);
	MakeRotatedKeyArr(onceKeyArr, secondKeyArr, keyRowSize);
	MakeRotatedKeyArr(secondKeyArr, thirdKeyArr, keyRowSize);

	// check and move accroding to keyArray and lockArray
	int startRow = 0;
	int startCol = 0;
	while(true)
	{
		if(insertEnd <= startRow)
		{
			if(insertStart <= startCol)
				break;
		}

		// origin
		const bool bIsRightOri = CheckFit(originKeyArr, paddingLockArr, startRow, startCol,
			keyRowSize, insertStart, insertEnd);
		// once
		const bool bIsRightOnce = CheckFit(onceKeyArr, paddingLockArr, startRow, startCol,
			keyRowSize, insertStart, insertEnd);

		// second
		const bool bIsRightSec = CheckFit(secondKeyArr, paddingLockArr, startRow, startCol,
			keyRowSize, insertStart, insertEnd);

		// thrid
		const bool bIsRightThr = CheckFit(thirdKeyArr, paddingLockArr, startRow, startCol,
			keyRowSize, insertStart, insertEnd);

		if( (true == bIsRightOri) || (true == bIsRightOnce) ||
			(true == bIsRightSec) || (true == bIsRightThr) )
		{
			answer = true;
			break;
		}
		else
		{
			startCol++;
			if(lockRowSize < startCol)
			{
				startCol = 0;
				startRow++;
			}
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> inputKey;

	// KeyInput
	vector<int> key_1;
	key_1.push_back(0);
	key_1.push_back(0);
	key_1.push_back(0);
	key_1.push_back(1);
	inputKey.push_back(key_1);
	inputKey.push_back(key_1);
	inputKey.push_back(key_1);
	inputKey.push_back(key_1);

	// LockInput
	vector<vector<int>> inputLock;
	vector<int> lock_1;
	lock_1.push_back(0);
	lock_1.push_back(1);
	lock_1.push_back(1);
	lock_1.push_back(1);

	inputLock.push_back(lock_1);
	inputLock.push_back(lock_1);
	inputLock.push_back(lock_1);
	inputLock.push_back(lock_1);
	
	bool answer = solution(inputKey, inputLock);

	printf("\n\n -- final answer : %d -- \n", answer);

	return 0;
}
#include string
#include vector
#include string.h

#define MAX_INPUT_SIZE 1000

int plusDuplicatedCount(int duplicatedCount)
{
	int retValue = 0;

	if(999 = duplicatedCount)
	{
		retValue += 3;
	}
	else if(99 = duplicatedCount)
	{
		retValue += 2;
	}
	else if(9 = duplicatedCount)
	{
		retValue += 1;
	}

	return retValue;
}

int solution(stdstring inputStr) {

	
	  문자 개수와 반복되는 값으로 표현하여 더 짧은 문자열로 줄여서 표현하는 알고리즘
	  문자열은 제일 앞부터 정해진 길이만큼 잘라야한다.
	  
	  exception)
	  a
	  aaaaaaaaaabbbbbbbbbb
	  aaaaaaaaaa
	 

	const unsigned int inputSize = inputStr.size();

	unsigned int maxSliceSize = inputStr.size()  2;
	if(1 == inputSize)
	{
		maxSliceSize = 1;
	}

	const unsigned int minSliceSize = 1;
	int resultArray[MAX_INPUT_SIZE + 1] = { 0, };
	for(unsigned int sliceCnt = maxSliceSize; sliceCnt = minSliceSize; sliceCnt--)
	{
		int subOffIdx = 0;
		int result = inputSize;  압축될 길이
		int findCnt = 0;  발견한 압축 가능 기준
		int duplicatedCnt = 0;  10a, 100a, 1000a 같은 경우

		 비교 기준이 되는 string
		stdstring compareStr = inputStr.substr(subOffIdx, sliceCnt);
		subOffIdx += sliceCnt;

		 연속된 3개 이상의 압축할 수 있는 문자열을 찾을 경우
		stdstring prevFoundStr;

		while(true)
		{
			 loop stop
			if(inputSize = subOffIdx)
			{
				result += plusDuplicatedCount(duplicatedCnt);
				duplicatedCnt = 0;

				break;
			}

			 compareStr 다음에 오는 string
			stdstring nextStr = inputStr.substr(subOffIdx, sliceCnt);
			subOffIdx += sliceCnt;

			 compareStr, nextStr 비교
			if(0 == strcmp(compareStr.c_str(), nextStr.c_str()))
			{
				 같을 경우
				result -= sliceCnt;

				 압축된 문자 앞에 붙는 숫자
				if(0 == strcmp(prevFoundStr.c_str(), nextStr.c_str()))
				{
					 Do Nothing (for debug log)
				}
				else
				{
					prevFoundStr = nextStr;
					findCnt++;
				}
				duplicatedCnt++;
			}
			else
			{
				compareStr = nextStr;

				result += plusDuplicatedCount(duplicatedCnt);
				duplicatedCnt = 0;
			}
		}

		 결과 저장
		resultArray[sliceCnt] = result + findCnt;
	}


	int answer = 1001;
	 가장 작은 값을 resultArray에서 찾는다
	for(int idx = maxSliceSize; idx  0; idx--)
	{
		answer = answer  resultArray[idx]  resultArray[idx]  answer;
	}

	return answer;
}

int main()
{
	stdstring inputData = aaaaaaaaaa;
	printf(inputData  %s Size  %un, inputData.c_str(), inputData.size());
	
	stdstring subStr = inputData.substr(0, 3);
	subStr = inputData.substr(1,3);

	int answer = solution(inputData);

	printf(answer  %dn, answer);

	return 0;
}
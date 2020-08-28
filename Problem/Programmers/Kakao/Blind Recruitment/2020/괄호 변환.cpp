#include <string>
#include <vector>

#define MAX_INPUT_SIZE 1000
#define MIN_INPUT_SIZE 2
#define DEBUG_LINE 0


/**
 * 괄호 개수는 맞지만 짝이 맞지않음
 * 소스 코드에 작성된 모든 괄호를 뽑아서
 * 올바른 순서대로 배치된 괄호 문자열을 알려주는 프로그램 작성 필요
 * 
 * 1.'(' 와 ')' 로만 이루어진 문자열이 있을 경우, '('의 개수와 ')'의 개수가 같다 -> 균형잡힌 괄호 문자열
 * 2.'(' 와 ')' 의 괄호의 짝도 모두 맞을 경우 -> 올바른 괄호 문자열 (1번 충족해야됨)
 * 
 * 균형잡힌 괄호 문자열은 올바른 괄호 문자열로 바꿀 수 있다.
 * 1) Empty할 경우 빈 문자열을 반환
 * 2) 문자열 w를 두 개의 균형잡힌 괄호 문자열로 만들 수 있다. (u와 v)
 *	  (단, u는 균형잡힌 문자열로 더 이상 분리할 수 없어야 하며, v는 빈 문자열이 될 수 있다)
 * 3) 문자열 u가 올바른 괄호 문자열 이라면 문자열 v에 대해 1단계부터 다시 수행
 *	3-1)수행한 결과 문자열을 u에 이어 붙인 후 반환
 * 4) 문자열 u가 올바른 괄호 문자열이 아니라면 아래 과정을 수행
 *	4-1) 빈 문자열에 첫 번째 문자로 '(' 를 붙인다.
 *	4-2) 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙인다
 *	4-3) ')'를 다시 붙인다
 *	4-4) u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙인다.
 *	4-5) 생성된 문자열을 반환
 */

bool isBalanceStringValue(std::string newValue)
{
	bool retValue = false;

	unsigned int leftGualCnt = 0;
	unsigned int rightGualCnt = 0;

	const unsigned int newValSize = newValue.size();
	for(unsigned int idx = 0; idx < newValSize; idx++)
	{
		if('(' == newValue[idx])
		{
			leftGualCnt++;
		}
		else if(')' == newValue[idx])
		{
			rightGualCnt++;
		}
	}

	if(leftGualCnt == rightGualCnt)
	{
		retValue = true;
	}

	return retValue;
}

bool isRightStringValue(std::string newValue)
{
	bool retValue = false;

	std::vector<char> compareVec;

	const unsigned int newValSize = newValue.size();
	for(unsigned int idx = 0; idx < newValSize; idx++)
	{
		/**
		 * Stack을 활용
		 * '('가 나올 때 저장하고, ')'가 나올 때 '('를 없앤다
		 */
		if('(' == newValue[idx])
		{
			compareVec.push_back('(');
		}
		else if(')' == newValue[idx])
		{
			if(false == compareVec.empty())
			{
				if('(' == compareVec.back())
				{
					compareVec.pop_back();
				}
			}
		}
	}

	if(true == compareVec.empty())
	{
		retValue = true;
	}

#if DEBUG_LINE
	printf("String : %s, isRightString : %d\n", newValue.c_str(), retValue);
#endif

	return retValue;
}

void makeDevidedString(std::string& rSrc, std::string& uString, std::string& vString)
{
	// make uString(균형잡힌 문자열), vString 
	const unsigned int sourceSize = rSrc.size();
	unsigned int leftGualCnt = 0;
	unsigned int rightGualCnt = 0;
	for(unsigned int idx = 0; idx < sourceSize; idx++)
	{
		if('(' == rSrc[idx])
		{
			leftGualCnt++;
		}
		else if(')' == rSrc[idx])
		{
			rightGualCnt++;
		}

		if(leftGualCnt == rightGualCnt)
		{
			for(unsigned int addIdx = 0; addIdx <= idx; addIdx++)
			{
				uString += rSrc[addIdx];
			}

			// vString
			for(unsigned int addIdx = idx + 1; addIdx <= sourceSize; addIdx++)
			{
				vString += rSrc[addIdx];
			}
			break;
		}
	}
#if DEBUG_LINE
	printf("made uString : %s |||| vString: %s\n", uString.c_str(), vString.c_str());
#endif
}

std::string makeRightString(std::string& pString)
{
	std::string retValue = "";

	bool bIsBalanceStr = isBalanceStringValue(pString);
	if(true == bIsBalanceStr)
	{
		bool bIsRightStr = isRightStringValue(pString);
		if(true == bIsRightStr)
		{
			retValue = pString;
#if DEBUG_LINE
			printf("bIsRightStr : %d, String : %s\n", bIsRightStr, pString.c_str());
#endif
		}
		else
		{
			std::string originStr = pString;

			std::string uString = "";
			std::string vString = "";
			makeDevidedString(originStr, uString, vString);

			bool uStringBool = isRightStringValue(uString);
			if(true == uStringBool)
			{
				// step 3
				uString += makeRightString(vString);
#if DEBUG_LINE
				printf("Step 3 > RightString Value : %d, uString : %s\n",
					uStringBool, uString.c_str());
#endif
				retValue = uString;
			}
			else
			{
				// step 4
				std::string emptyStr = "";
				emptyStr += '(';
				emptyStr += makeRightString(vString).c_str();
				emptyStr += ')';

#if DEBUG_LINE
				printf("step4 > emptyStr : %s\n", emptyStr.c_str());
#endif

				std::string converted_uStr = "";
				for(unsigned int idx = 0; idx < uString.size(); idx++)
				{
					if((0 == idx) || ((uString.size() - 1) == idx))
					{
						continue;
					}
					else
					{
						if('(' == uString[idx])
						{
							converted_uStr += ')';
						}
						else
						{
							converted_uStr += '(';
						}
					}
				}
				emptyStr += converted_uStr.c_str();
#if DEBUG_LINE
				printf("step4 > converted_uStr : %s => emptyStr : %s\n", 
					converted_uStr.c_str(), emptyStr.c_str());
#endif
				retValue = emptyStr;
			}
		}
	}

	return retValue;
}

std::string solution(std::string newValue) {
	std::string answer = "";

	if(true == newValue.empty())
	{
		return answer;
	}

	answer = makeRightString(newValue);

#if DEBUG_LINE
	printf("\n --final answer : %s --\n", answer.c_str());
#endif

	return answer;
}

int main()
{
	std::string inputData = ")(";

	printf("inputData : %s , Size : %u\n", inputData.c_str(), inputData.size());

	std::string answer = solution(inputData);

	return 0;
}
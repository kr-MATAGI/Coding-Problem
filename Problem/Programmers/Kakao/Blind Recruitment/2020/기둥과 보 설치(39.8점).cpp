#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <algorithm>

using namespace std;

#define N_MIN_SIZE 5
#define N_MAX_SIZE 100

#define TEST_CASE_1 1
#define TEST_CASE_2 0
#define TEST_CASE_3 0

#define DEBUG_CODE 1

enum BuildType
{
	e_KiDung = 0,
	e_Bo = 1,
	e_NONE = 2
};

enum BuildOrder
{
	e_Delete = 0,
	e_Install = 1
};

struct KiBo
{
	KiBo()
		: kidung(false)
		, bo(false)
		, kiExt(false)
		, boExt(false)
	{

	}
	bool kidung;
	bool kiExt;
	bool bo;
	bool boExt;
};

struct Installation
{
	int x;
	int y;
	BuildType type;
};

typedef std::pair<int, int> POSITION;

bool compare(Installation lhs , Installation rhs)
{
	if( lhs.x == rhs.x )
	{
		if(lhs.y == rhs.y)
		{
			return lhs.type < rhs.type;
		}
		else
		{
			return lhs.y < rhs.y;
		}
	}
	else
	{
		return lhs.x < rhs.x;
	}
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	map<POSITION, KiBo> mapInfo;
	int x_min = 1001;
	int x_max = -1;
	int y_min = 1001;
	int y_max = -1;
	for(const vector<int>& vectData : build_frame)
	{
		int posX = vectData[0];
		x_min = x_min > posX ? posX : x_min;
		x_max = x_max < posX ? posX : x_min;

		int posY = vectData[1];
		y_min = y_min > posY ? posY : y_min;
		y_max = y_max < posY ? posY : y_min;

		BuildType buildType = (BuildType)vectData[2];
		BuildOrder buildOrder = (BuildOrder)vectData[3];

		if( (BuildType::e_KiDung == buildType && (n < posX || n < posY) ) ||
			(BuildType::e_Bo == buildType && (n <= posX || n < posY)))
		{
#if DEBUG_CODE
			printf("ignore - (%d, %d), type : %d, order ; %d \n",
				posX, posY, buildType, buildOrder);
#endif
			continue;
		}
#if DEBUG_CODE
		printf("%s { x,y : (%d, %d), type : %d, order : %d }\n", 
			__FUNCTION__, posX, posY, buildType, buildOrder);
#endif

		POSITION inputPos;
		inputPos.first = posX;
		inputPos.second = posY;
		if(BuildOrder::e_Install == buildOrder)
		{
			if(BuildType::e_KiDung == buildType)
			{
				bool bIsInstall = false;
				if(0 == posY)
				{
					// 기둥이 바닥 위에 있거나
					bIsInstall = true;
				}
				else if(true == mapInfo[inputPos].boExt || true == mapInfo[inputPos].bo)
				{		
					// 보의 다른한쪽 끝 부분에 있거나
					bIsInstall = true;
				}
				else if(true == mapInfo[inputPos].kiExt)
				{
					// 다른 기둥 위에 있다
					bIsInstall = true;
				}

				if(true == bIsInstall)
				{
					KiBo currKidung;
					currKidung = mapInfo[inputPos];
					currKidung.kidung = true;
					mapInfo[inputPos] = currKidung;

					// 기둥은 위로 설치됨
					POSITION upKidungPos;
					upKidungPos.first = posX;
					upKidungPos.second = posY + 1;
					
					KiBo upKidungExt;
					upKidungExt = mapInfo[upKidungPos];
					upKidungExt.kiExt = true;
					mapInfo[upKidungPos] = upKidungExt;

#if DEBUG_CODE
					printf("-->Install Result { currPos : %d %d, 기둥확장 : %d %d }\n\n",
						inputPos.first, inputPos.second, upKidungPos.first, upKidungPos.second);
#endif
				}
			}
			else
			{
				// buildType == Bo
				bool bIsInstall = false;

				POSITION rightBoPos;
				rightBoPos.first = posX + 1;
				rightBoPos.second = posY;

				if(true == mapInfo[inputPos].kiExt ||
					true == mapInfo[rightBoPos].kiExt)
				{
					// 한쪽 끝 부분이 기둥 위에 있어야 한다
					bIsInstall = true;
				}
				else if(true == mapInfo[inputPos].boExt && true == mapInfo[rightBoPos].bo)
				{
					// 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 한다.
					bIsInstall = true;
				}

				if(true == bIsInstall)
				{
					KiBo currBo;
					currBo = mapInfo[inputPos];
					currBo.bo = true;
					mapInfo[inputPos] = currBo;

					// 보는 오른쪽으로 확장됨
					KiBo rightBoExt;
					rightBoExt = mapInfo[rightBoPos];
					rightBoExt.boExt = true;
					mapInfo[rightBoPos] = rightBoExt;

#if DEBUG_CODE
					printf("-->Install Result { currPos : %d %d, 보 확장 : %d %d }\n\n",
						inputPos.first, inputPos.second, rightBoPos.first, rightBoPos.second);
#endif
				}
			}
		}
		else
		{
			// Order : Delete
			// 현재 inpust을 삭제하고 모든 조건에 대해서 검사 후 잘 못 되었으면 Revert
			
			KiBo currKibo;
			currKibo = mapInfo[inputPos];

			POSITION upPos;
			POSITION rightPos;
			KiBo upKiBo;
			KiBo rightKiBo;
			if(BuildType::e_KiDung == buildType)
			{
				if(false == currKibo.kidung)
				{
					continue;
				}
				currKibo.kidung = false;

				// 위로 설치되는 기둥
				upPos.first = posX;
				upPos.second = posY + 1;
				upKiBo = mapInfo[upPos];
				upKiBo.kiExt = false;

				mapInfo[inputPos] = currKibo;
				mapInfo[upPos] = upKiBo;

#if DEBUG_CODE
				printf("-->Delete 기둥 : currPos (%d, %d), ext(%d, %d)\n",
					inputPos.first, inputPos.second, upPos.first, upPos.second);
#endif
			}
			else
			{
				// Type == Bo
				if(false == currKibo.bo)
				{	
					continue;
				}
				currKibo.bo = false;
				
				//오른쪽으로 설치되는 보
				rightPos.first = posX + 1;
				rightPos.second = posY;
				rightKiBo = mapInfo[rightPos];
				rightKiBo.boExt = false;

				mapInfo[inputPos] = currKibo;
				mapInfo[rightPos] = rightKiBo;

#if DEBUG_CODE
				printf("-->Delete 보 : currPos (%d, %d), ext(%d, %d)\n",
					inputPos.first, inputPos.second, rightPos.first, rightPos.second);
#endif
			}

			// 전체 검사
#if DEBUG_CODE
			printf("--All Check--\n");
#endif
			bool bIsOk = true;
			for(auto mapData = mapInfo.begin(); mapData != mapInfo.end(); mapData++)
			{
#if DEBUG_CODE
				printf("mapData (%d, %d) 기둥 : %d, 기둥확장 : %d, 보 : %d, 보 확장 : %d\n",
					(*mapData).first.first, (*mapData).first.second, 
					(*mapData).second.kidung, (*mapData).second.kiExt,
					(*mapData).second.bo, (*mapData).second.boExt);
#endif

				if(true == (*mapData).second.kidung)
				{
					if(0 != (*mapData).first.second && false == (*mapData).second.kiExt)
					{
						// 기둥이 바닥에 있지 않은데, 또 다른 기둥위에 있지 않음
#if DEBUG_CODE
						printf("기둥 Case 1\n");
#endif
						if(0 != (*mapData).first.second &&
							(true == (*mapData).second.boExt || (true == (*mapData).second.bo)))
						{
#if DEBUG_CODE
							printf("기둥 Case 2\n");
#endif
							continue;
						}

						bIsOk = false;
						break;
					}
				}

				if(true == (*mapData).second.bo)
				{
					POSITION boExtPos;
					boExtPos.first = (*mapData).first.first + 1; // X
					boExtPos.second = (*mapData).first.second; // Y

					// 한쪽 끝 부분이 기둥 위에 있지 않은상태 이거나 
					if( false == (*mapData).second.kiExt && false == mapInfo[boExtPos].kiExt)
					{
						// 양쪽 끝 부분이 다른 보에 연결되지 않음
						if( 0 == posX )
						{
#if DEBUG_CODE
							printf("보 Case_1 pos(%d, %d) { }\n",
								(*mapData).first.first, (*mapData).first.second);
#endif
							bIsOk = false;
							break;
						}
						else if(n == posX)
						{
#if DEBUG_CODE
							printf("보 Case_2 pos(%d, %d) { }\n",
								(*mapData).first.first, (*mapData).first.second);
#endif
							bIsOk = false;
							break;
						}
						else
						{
							if(true == (*mapData).second.boExt && true == mapInfo[boExtPos].bo)
							{
								continue;
							}
						}
#if DEBUG_CODE
						printf("보 Case_3 pos(%d, %d) { }\n",
							(*mapData).first.first, (*mapData).first.second);
#endif
						
						bIsOk = false;
						break;
					}
				}
			}// end check loop

			if(false == bIsOk)
			{
#if DEBUG_CODE
				printf("-->revert { type : %d, inputPos : %d, %d }\n\n",
					buildType, inputPos.first, inputPos.second);
#endif
				if(BuildType::e_KiDung == buildType)
				{
					currKibo.kidung = true;

					// 위로 설치되는 기둥
					upKiBo.kiExt = true;

					mapInfo[inputPos] = currKibo;
					mapInfo[upPos] = upKiBo;
				}
				else
				{
					// Type == Bo
					currKibo.bo = true;

					//오른쪽으로 설치되는 보
					rightKiBo.boExt = true;

					mapInfo[inputPos] = currKibo;
					mapInfo[rightPos] = rightKiBo;
				}
			}
		}
	}

	// Return Result
	std::vector<Installation> installationList;
	for(auto mapData = mapInfo.begin(); mapData != mapInfo.end(); mapData++)
	{
		bool bIsKidung = (*mapData).second.kidung;
		bool bIsBo = (*mapData).second.bo;
		
		if(true == bIsKidung || true == bIsBo)
		{
			Installation instData;

			instData.x = (*mapData).first.first;
			instData.y = (*mapData).first.second;
			if(true == bIsKidung)
			{
				instData.type = BuildType::e_KiDung;
				installationList.push_back(instData);
			}
		
			if(true == bIsBo)
			{
				instData.type = BuildType::e_Bo;
				installationList.push_back(instData);
			}
		}
	}
	sort(installationList.begin(), installationList.end(), compare);
	for(Installation& instVal : installationList)
	{
		std::vector<int> temp;
		temp.push_back(instVal.x);
		temp.push_back(instVal.y);
		temp.push_back(instVal.type);
		answer.push_back(temp);
	}
	
	return answer;
}

int main()
{
	int n = 5; // 벽면의 크기 ( n * n )

	/*
	* 기둥은 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나, 또는 다른 기둥 위에 있어야 한다.
	* -> [0,x]의 경우 이거나 설치부분이 보 이거나,  [ 설치 - 1, x ] 가 기둥이어야 한다
	* 보는 한쪽 끝 부분이 기둥 위에 있거나, 또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 한다.
	* -> 설치부분이 기둥이거나, [ ?, 설치 -1], [?, 설치 + 1]이 보 여야 한다
	*/

	/*
	* build frame의 세로(행) 길이는 1 이상 1000 이하
	* build frame의 가로(열) 길이는 4
	* build frame의 원소 [x, y, a, b]
	* x,y는 기둥, 보를 설치 또는 삭제할 교차점의 좌표 [가로, 세로]
	* a는 구조물의 종류, 0은 기둥, 1은 보
	* b는 구조물을 설치, 삭제 0은 삭제, 1은 설치
	* 벽면에 벗어나게 기둥, 보를 설치하는 경우는 없음
	* 바닥에 보를 설치하는 경우 없음
	*/


	vector<vector<int>> buildFrame;
	vector<int> input;
#if TEST_CASE_1
	input.push_back(1);
	input.push_back(0);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(2);
	input.push_back(1);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(2);
	input.push_back(2);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(5);
	input.push_back(0);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());


	input.push_back(5);
	input.push_back(1);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(4);
	input.push_back(2);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(3);
	input.push_back(2);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
	input.push_back(1);
	input.push_back(2);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
	input.push_back(2);
	input.push_back(0);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
	input.push_back(2);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
	input.push_back(4);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
	input.push_back(3);
	input.push_back(1);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
	input.push_back(4);
	input.push_back(1);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);
#endif

#if TEST_CASE_2
	input.push_back(0);
	input.push_back(0);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(2);
	input.push_back(0);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(4);
	input.push_back(0);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(0);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(2);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(3);
	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(2);
	input.push_back(0);
	input.push_back(0);
	input.push_back(0);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(1);
	input.push_back(1);
	input.push_back(1);
	input.push_back(0);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());

	input.push_back(2);
	input.push_back(2);
	input.push_back(0);
	input.push_back(1);
	buildFrame.push_back(input);

	input.erase(input.begin(), input.end());
#endif

	/*
	* return 하는 배열은 가로 3인 2차원 배열, 각 구조물의 좌표를 담고 있어야 한다.
	* return 하는 배열의 원소는 [x, y, a] 형식
	* x,y는 기둥, 보의 교차점 [가로, 세로]
	* 기둥, 보는 교차점 좌표를 기준으로 오른쪽 혹은 위쪽 방향으로 설치
	* a는 구조물의 종류
	* return 하는 배열은 x좌표 기준으로 오름차순 정렬하며, x좌표가 같을 경우 y좌표 기준으로 오름차순 정렬
	* x,y좌표가 모두 같은 경우 기둥이 보보다 앞에
	*/
	vector<vector<int>> answer = solution(n, buildFrame);

	// answer printf
	printf("\n -- Answer (Size : %d ) -- \n", answer.size());
	for(int i = 0; i < answer.size(); i++)
	{
		printf("[ %d, %d, %d ] \n", answer[i][0], answer[i][1], answer[i][2]);
	}

	return 0;
}
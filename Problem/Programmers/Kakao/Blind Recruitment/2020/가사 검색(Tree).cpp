#include <string>
#include <vector>
#include <string.h>

using namespace std;

#define MAX_WORDS_SIZE 100000
#define MAX_WORD_LENGTH 10000
#define A_to_Z_SIZE 26 
#define DEBUG_CODE 1

/**
 * 노래 가사에 사용된 단어들 중에 특정 키워드가 몇 개 포함되어 있는지
 * 와일드카드 문자 중 하나인 '?'가 포함된 패턴 형태의 문자열 (글자 하나를 의미함)
 * words : 가사에 사용된 모든 단어들이 담긴 배열
 * queries : 찾고자 하는 키워드
 * answer : 각 키워드 별로 매치된 단어가 몇 개인지 순서대로 배열에 담아 반환
 * 
 * a -> 97, z : 122
 * 
 * Tree를 통한 Search 코드 점수
 * 정확성 23.5 (테스트 케이스 14번 틀림), 효율성 15.0 합계 38.5
 * -> Trie(트라이 구조)로 수정 필요
 */

struct wordNode
{
public:
	wordNode()
		: value(0)
		, alphabet(0)
		, depth(0)
	{
		memset(pNext, NULL, sizeof(pNext));
	}

public:
	int value;
	char alphabet;
	int depth;
	wordNode* pNext[A_to_Z_SIZE + 2];
};

class WordTree
{
public:
	WordTree();

public:
	wordNode* node;
};

WordTree::WordTree()
{
	// init node
	node = NULL;

	// make root
	wordNode* newNode = new wordNode();

	node = newNode;

#if DEBUG_CODE
	printf("Made Root Node ! \n");
#endif
}

void MakeWordsTree(std::vector<std::string>& words, WordTree& rDest)
{
	const unsigned int wordListSize = words.size();
	for(unsigned int wordsIdx = 0; wordsIdx < wordListSize; wordsIdx++)
	{
		const std::string &currStr = words[wordsIdx];
#if DEBUG_CODE
		printf("currStr : %s \n", currStr.c_str());
#endif

		// Insert header
		wordNode* pHeader = rDest.node;

		const unsigned int strSize = currStr.size();
		for(unsigned int strIdx = 0; strIdx < strSize; strIdx++)
		{
			// -96해서 배열 1 ~ 26 까지 맞춤.
			char chAlpha = currStr[strIdx];
			int value = chAlpha - 96;

			wordNode* newNode = new wordNode();
			newNode->alphabet = chAlpha;
			newNode->value = value;
			newNode->depth = strIdx + 1;
			memset(newNode->pNext, NULL, sizeof(newNode->pNext));

			if(NULL == pHeader->pNext[value])
			{
				pHeader->pNext[value] = newNode;
				pHeader = pHeader->pNext[value];
			}
			else
			{
				pHeader = pHeader->pNext[value];
			}
		}

#if DEBUG_CODE
		printf("Inserted String to Tree ( %s ) ! \n", currStr.c_str());
#endif
	}
}

void DFS_Search(wordNode *pHeader, const std::string &query, int pos, const int depth, int &answer)
{
	if(pos > depth)
	{
		return;
	}
	
	const char ch = query[pos];
	if('?' == ch)
	{
#if DEBUG_CODE
		printf("{ ch : %c, pHeadr : %c, %d }\n", ch, pHeader->alphabet, pHeader->depth);
#endif
		if(pos == depth - 1) 
		{
			for(int idx = 0; idx < (A_to_Z_SIZE + 2); idx++)
			{
				bool isOk = true;
				wordNode* pNextNode = pHeader->pNext[idx];
				if(NULL != pNextNode)
				{
					for(int chIdx = 0; chIdx < (A_to_Z_SIZE + 2); chIdx++)
					{
						wordNode* pChildNode = pNextNode->pNext[chIdx];
						if(NULL != pChildNode)
						{
							isOk = false;
							break;
						}
					}
					if(true == isOk)
					{
						answer++;
					}
				}
				
			}
		}
		else
		{
			for(int idx = 0; idx < (A_to_Z_SIZE + 2); idx++)
			{
				wordNode* pNextNode = pHeader->pNext[idx];
				if(NULL != pNextNode)
				{
					DFS_Search(pNextNode, query, pos + 1, depth, answer);
				}
			}
		}
	}
	else
	{
#if DEBUG_CODE
		printf("{ ch : %c, pHeadr : %c, %d }\n", ch, pHeader->alphabet, pHeader->depth);
#endif
		wordNode* pNextNode = pHeader->pNext[ch - 96];

		if(NULL != pNextNode)
		{
			if(pos == depth - 1)
			{
				bool bIsAns = true;
				for(int idx = 0; idx < (A_to_Z_SIZE + 2); idx++)
				{
					if(NULL != pNextNode->pNext[idx])
					{
						bIsAns = false;
						break;
					}
				}
				if(true == bIsAns)
				{
					answer++;
				}
			}
			else
			{
				DFS_Search(pNextNode, query, pos + 1, depth, answer);
			}
		}
	}
}

int SearchQuery(std::string& query, const  WordTree &rSrc)
{
	wordNode* pHeader = rSrc.node;
	const int depth = query.size();
	int retValue = 0;

#if DEBUG_CODE
	printf("\n %s : %s \n\n", __FUNCTION__, query.c_str());
#endif

	DFS_Search(pHeader, query, 0, depth, retValue);

#if DEBUG_CODE
	printf("\n %s { query : %s, answer : %d}\n", __FUNCTION__, query.c_str(), retValue);
#endif
	
	return retValue;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;

	// Make Words Tree
	WordTree wordTree;
	MakeWordsTree(words, wordTree);

	// Search queries
	const unsigned int queryListSize = queries.size();
	for(unsigned int idx = 0; idx < queryListSize; idx++)
	{
		std::string query = queries[idx];

		const int retValue = SearchQuery(query, wordTree);
		answer.push_back(retValue);
	}

	return answer;
}

int main()
{
	vector<std::string> words;
	words.push_back("frodo");
	words.push_back("front");
	words.push_back("frost");
	words.push_back("frozen");
	words.push_back("frame");
	words.push_back("kakao");

	vector<std::string> queries;
	//queries.push_back("frodo");
	//queries.push_back("????o");
	//queries.push_back("fr???");
	//queries.push_back("fro??");
	//queries.push_back("fro???");
	//queries.push_back("pro?");
	queries.push_back("?????");

	std::vector<int> answer = solution(words, queries);
#if DEBUG_CODE
	printf("Returned the answer ! \n");
	for(int idx = 0; idx < answer.size(); idx++)
	{
		printf("query : %s, answer[%d] : %d \n", queries[idx].c_str(), idx, answer[idx]);
	}
#endif

	return 0;
}
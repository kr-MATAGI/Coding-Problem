#include <string>
#include <vector>
#include <sstream>
#include <string.h>

using namespace std;

// 정확 100점 효율 빵점 ㅋ....

struct Node
{
	Node()
		:lang()
		, front(-1)
		, junior(-1)
		, pizza(-1)
		, depth(0)
		, pLeft(NULL)
		, pRight(NULL)
	{
	}
	string lang;
	int front;
	int junior;
	int pizza;
	vector<string> score;

	int depth;
	Node* pLeft;
	Node* pRight;
};

class InfoTree
{
public:
	InfoTree(const string lang);
public:
	Node* root;
};

InfoTree::InfoTree(const string lang)
{
	root = NULL;
	Node* newNode = new Node();
	newNode->lang = lang;
	newNode->depth = 0;

	root = newNode;
}

void MakeTree(const vector<string>& rSrc, InfoTree& rDest)
{
	Node* pHeader = rDest.root;
	for(int idx = 1; idx < rSrc.size(); idx++)
	{
		Node* newNode = new Node();
		newNode->depth = idx;
		
		if(1 == idx)
		{
			if("frontend" == rSrc[idx])
			{
				newNode->front = true;
			}
			else
			{
				newNode->front = false;
			}
		}

		else if(2 == idx)
		{
			if("junior" == rSrc[idx])
				newNode->junior = true;
			else
				newNode->junior = false;
		}
		else if(3 == idx)
		{
			if("pizza" == rSrc[idx])
			{
				newNode->pizza = true;
			}
			else
			{
				newNode->pizza = false;
			}	
		}

		if(idx == 4)
		{
			pHeader->score.push_back(rSrc[idx]);
		}
		else if("frontend" == rSrc[idx] || "junior" == rSrc[idx] || "pizza" == rSrc[idx])
		{
			if(NULL == pHeader->pLeft)
			{
				pHeader->pLeft = newNode;
				pHeader = pHeader->pLeft;
			}
			else
			{
				pHeader = pHeader->pLeft;
			}
		}
		else
		{
			if(NULL == pHeader->pRight)
			{
				pHeader->pRight = newNode;
				pHeader = pHeader->pRight;
			}
			else
			{
				pHeader = pHeader->pRight;
			}
		}
	}

}

void DFS_Search(Node* pHeader, const vector<string>& queryList, const int idx, int& ans)
{
	if(pHeader->depth == 3)
	{
		int queryInt = atoi(queryList[idx].c_str());
		for(int idx = 0; idx < pHeader->score.size(); idx++)
		{
			int number = atoi(pHeader->score[idx].c_str());
			if(queryInt <= number)
			{
				//printf("pHeader.pizza %d score: %d\n", pHeader->pizza, number);
				ans++;
			}
		}
		return;
	}
	else if(queryList[idx] == "and")
	{
		if(NULL != pHeader)
			DFS_Search(pHeader, queryList, idx + 1, ans);
	}
	else if("-" == queryList[idx])
	{
		if( NULL != pHeader->pLeft)
			DFS_Search(pHeader->pLeft, queryList, idx+1, ans);
		if(NULL != pHeader->pRight)
			DFS_Search(pHeader->pRight, queryList, idx+1, ans);	
	}
	else if("frontend" == queryList[idx] || "junior" == queryList[idx] || "pizza" == queryList[idx])
	{
		if(NULL != pHeader->pLeft)
			DFS_Search(pHeader->pLeft, queryList, idx+1, ans);
	}
	else if("backend" == queryList[idx] || "senior" == queryList[idx] || "chicken" == queryList[idx])
	{
		if(NULL != pHeader->pRight)
			DFS_Search(pHeader->pRight, queryList, idx+1, ans);
	}
	
}

int SovleQuery(vector<string>& queryList, InfoTree& tree)
{
	int retValue = 0;

	Node* pHeader = tree.root;

	//printf("---%s \n", pHeader->lang.c_str());
	DFS_Search(pHeader, queryList, 2, retValue);

	return retValue;
}

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

	InfoTree cppTree("cpp");
	InfoTree javaTree("java");
	InfoTree pythonTree("python");

	for(const string& data : info)
	{
		stringstream strStream;
		strStream.str(data);
		vector<string> sliceStrList;
		while(!strStream.eof())
		{
			string temp;
			strStream >> temp;
			sliceStrList.push_back(temp);
		}

		if("cpp" == sliceStrList[0])
		{
			MakeTree(sliceStrList, cppTree);
		}
		else if("java" == sliceStrList[0])
		{
			MakeTree(sliceStrList, javaTree);
		}
		else
		{
			MakeTree(sliceStrList, pythonTree);
		}
	}

	// sovle Query
	for(const string& qData : query)
	{
		stringstream strStream;
		strStream.str(qData);

		vector<string> sliceQueryList;
		while(!strStream.eof())
		{
			string sliceQ;
			strStream >> sliceQ;
			sliceQueryList.push_back(sliceQ);
		}

		int result = 0;
		if("java" == sliceQueryList[0])
		{
			result = SovleQuery(sliceQueryList, javaTree);
		}
		else if("cpp" == sliceQueryList[0])
		{
			result = SovleQuery(sliceQueryList, cppTree);
		}
		else if("python" == sliceQueryList[0])
		{
			result = SovleQuery(sliceQueryList, pythonTree);
			
		}
		else if("-" == sliceQueryList[0])
		{
			result = SovleQuery(sliceQueryList, javaTree);
			result += SovleQuery(sliceQueryList, cppTree);
			result += SovleQuery(sliceQueryList, pythonTree);
		}
		answer.push_back(result);

		//printf("%s {query : %s, result : %d } \n", __FUNCTION__, qData.c_str(), result);
	}

	return answer;
}

int main()
{
	vector<string> info;
	info.push_back("java backend junior pizza 150");
	info.push_back("python frontend senior chicken 210");
	info.push_back("python frontend senior chicken 150");
	info.push_back("cpp backend senior pizza 260");
	info.push_back("java backend junior chicken 80");
	info.push_back("python backend senior chicken 50");

	vector<string> query;
	query.push_back("java and backend and junior and pizza 100");
	query.push_back("python and frontend and senior and chicken 200");
	query.push_back("cpp and - and senior and pizza 250");
	query.push_back("cpp and backend and senior and - 150");
	query.push_back("- and - and - and chicken 100");
	query.push_back("- and - and - and - 150");

	const vector<int> answer = solution(info, query);


	printf("\n\n----Ans----\n");
	for(int ans : answer)
	{
		printf("%d \n", ans);
	}

	return 0;
}
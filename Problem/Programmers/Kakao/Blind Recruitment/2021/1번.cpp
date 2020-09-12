#include <string>
#include <vector>

using namespace std;


string solution(string new_id) {
	string answer = "";

	bool oneMore = true;
	
	{
		string step_1 = "";
		for(int idx = 0; idx < new_id.size(); idx++)
		{
			if(65 <= new_id[idx] && 90 >= new_id[idx])
			{
				step_1 += (new_id[idx] + 32);
			}
			else
			{
				step_1 += new_id[idx];
			}
		}
		printf("%s (%d)\n", step_1.c_str(), step_1.size());

		string step_2 = "";
		for(int idx = 0; idx < step_1.size(); idx++)
		{
			if((97 <= step_1[idx] && 122 >= step_1[idx]) || (48 <= step_1[idx] && 57 >= step_1[idx]) ||
				'-' == step_1[idx] || '_' == step_1[idx] || '.' == step_1[idx])
			{
				step_2 += step_1[idx];
			}
		}
		printf("%s (%d)\n", step_2.c_str(), step_2.size());

		string step_3 = "";
		for(int idx = 0; idx < step_2.size(); idx++)
		{
			if('.' == step_2[idx])
			{
				step_3 += step_2[idx];
				for(int jdx = idx + 1; jdx < step_2.size(); jdx++)
				{
					if('.' == step_2[jdx])
					{
						idx++;
						continue;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				step_3 += step_2[idx];
			}
		}
		printf("%s (%d)\n", step_3.c_str(), step_3.size());

		string step_4 = "";
		if('.' == step_3[0])
		{
			step_4 = step_3.substr(1, step_3.size());
		}
		else
		{
			step_4 = step_3;
		}

		if('.' == step_4.back())
		{
			step_4.pop_back();
		}
		printf("%s (%d)\n", step_4.c_str(), step_4.size());

		string step_5 = "";
		if(true == step_4.empty())
		{
			step_5 += "a";
		}
		else
		{
			step_5 = step_4;
		}

		string step_6 = "";
		if(16 <= step_5.size())
		{
			step_6 = step_5.substr(0, 15);
			if('.' == step_6.back())
			{
				step_6.pop_back();
			}
		}
		else
		{
			step_6 = step_5;
		}
		printf("%s (%d)\n", step_6.c_str(), step_6.size());

		if(2 >= step_6.size())
		{
			answer = step_6;
			char lastCh = step_6[step_6.size() - 1];
			while(true)
			{
				if(answer.size() == 3)
				{
					break;
				}

				answer += lastCh;
			}
		}
		else
		{
			answer = step_6;
		}
	}
	printf("ans : %s (%d)\n", answer.c_str(), answer.size());


	return answer;
}


int main()
{
	 //차이 32

	int a = '0'; // 97
	int z = '9'; // 122
	int A = 'A'; // 65
	int Z = 'Z'; // 90

	std::string new_id = "abcdefghijklmn.p";
	printf("str size : %d\n", new_id.size());
	const string answer = solution(new_id);

	return 0;
}
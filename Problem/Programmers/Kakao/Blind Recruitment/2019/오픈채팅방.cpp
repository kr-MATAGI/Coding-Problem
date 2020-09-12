#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#define DEBUG_CODE 1

/**
* c++ 라이브러리에 sstream이라는 편한게 있다 이거 쓰면 subStr을 사용하지 않고 편하게 사용가능함!
*/

enum ACTION {
    e_Enter = 0,
    e_Leave = 1,
    e_Change = 2,
    e_NONE = 3
};

struct ConvertedLog
{
    ACTION action;
    string userId;
};

vector<string> solution(vector<string> record) {
    vector<string> answer;

    // id, nick
    unordered_map<string, string> userInfoMap;
    vector<ConvertedLog> convertedLogList;

    for(const string& log : record)
    {
        string userId;
        string nick;
        ACTION action = ACTION::e_NONE;

        switch(log[0])
        {
        case 'E':
            action = ACTION::e_Enter;
            userId = log.substr(6);
            break;

        case 'L':
            action = ACTION::e_Leave;
            userId = log.substr(6);
            break;

        case 'C':
            action = ACTION::e_Change;
            userId = log.substr(7);
            break;

        default:
            action = ACTION::e_NONE;
            break;
        }

#if DEBUG_CODE
        printf("%s(%d) { userId_nick : %s }\n", __FUNCTION__, __LINE__, userId.c_str());
#endif

        if(ACTION::e_Enter == action || ACTION::e_Change == action)
        {
            int spaceIdx = 0;
            for(int idx = 0; idx < userId.size(); idx++)
            {
                if(' ' == userId[idx])
                {
                    spaceIdx = idx;
                    break;
                }
            }

            nick = userId.substr(spaceIdx + 1);
            userId = userId.substr(0, spaceIdx);
#if DEBUG_CODE
            printf("%s(%d) { userId : %s, nick : %s }\n\n", __FUNCTION__, __LINE__,
                userId.c_str(), nick.c_str());
#endif
            unordered_map<string, string>::iterator iter = userInfoMap.find(userId);
            if(userInfoMap.end() != iter)
            {
                (*iter).second = nick;
            }
            else
            {
                userInfoMap[userId] = nick;
            }
        }
        else
        {
#if DEBUG_CODE
            printf("%s(%d) { Leave userId : %s }\n\n", __FUNCTION__, __LINE__, userId.c_str());
#endif
        }

        if(ACTION::e_Enter == action || ACTION::e_Leave == action)
        {
            ConvertedLog convertedLog;
            convertedLog.action = action;
            convertedLog.userId = userId;
            convertedLogList.push_back(convertedLog);
        }
    }

    // make answer
    for(ConvertedLog& log : convertedLogList)
    {
        string madeStr;
        string actionStr;
        switch(log.action)
        {
        case ACTION::e_Enter:
            actionStr = "들어왔습니다.";
            break;
        case ACTION::e_Leave:
            actionStr = "나갔습니다.";
            break;
        default:
            break;
        }

        madeStr = userInfoMap[log.userId];
        madeStr += "님이 ";
        madeStr += actionStr;

        answer.push_back(madeStr);
    }

    return answer;
}

int main()
{
    vector<string> record;
    record.push_back("Enter uid1234 Muzi");
    record.push_back("Enter uid4567 Prodo");
    record.push_back("Leave uid1234");
    record.push_back("Enter uid1234 Prodo");
    record.push_back("Change uid4567 Ryan");
    const vector<string> answer = solution(record);

    return 0;
}
#include string
#include vector
#include unordered_map
#include algorithm

#define DEBUG_CODE 1

using namespace std;

// 필요없는 코드라인 줄이는 연습 필요.

struct Answer
{
    int stage;
    double rate;
};

bool compare(Answer& lhs, Answer& rhs)
{
    if(lhs.rate == rhs.rate)
    {
        return lhs.stage  rhs.stage;
    }
    else
    {
        return lhs.rate  rhs.rate;
    }
}

vectorint solution(int N, vectorint stages) {
    vectorint answer;

     stage, userCount
    unordered_mapint, int arrivedUserList;
    unordered_mapint, int notClearedList;
    
     stage, fail rate
    unordered_mapint, double failRateList;
    vectorAnswer answerList;

    for(int idx = 1; idx = N; idx++)
    {
        arrivedUserList[idx] = 0;
        notClearedList[idx] = 0;
    }

    for(const int stage  stages)
    {
        notClearedList[stage]++;
        
        for(int idx = 1; idx = stage; idx++)
        {
            arrivedUserList[idx]++;
        }
    }

     calculated fail rate
    for(int idx = 1; idx = N; idx++)
    {
        if(0 == notClearedList[idx])
        {
            failRateList[idx] = 0.0;
        }
        else
        {
            failRateList[idx] = (double)notClearedList[idx]  (double)arrivedUserList[idx];
#if DEBUG_CODE
            printf(%s(%d) { stage  %d, notClearedList  %d, arrivedUserList  %d }n, __FUNCTION__, __LINE__, 
                idx, notClearedList[idx], arrivedUserList[idx]);
#endif
        }
    }

    for(const auto& data  failRateList)
    {
        Answer ans;
        ans.stage = data.first;
        ans.rate = data.second;
#if DEBUG_CODE
        printf(%s(%d) { stage  %d, rate  %f }n, __FUNCTION__, __LINE__, ans.stage, ans.rate);
#endif
        answerList.push_back(ans);
    }
    sort(answerList.begin(), answerList.end(), compare);

    for(const Answer& ans  answerList)
    {
        answer.push_back(ans.stage);
    }

    return answer;
}


int main()
{
     실패율 = 스테이지에 도달했으나 아직 클리어하지 못한 플레이어의 수  스테이지에 도달한 플레이어 수
    int N = 5;  스테이지의 개수
    vectorint stages;  각 사용자가 현재 도전중인 스테이지의 번호 (N+1)은 마지막 스테이지까지 클리어한 사용자
    stages.push_back(2);
    stages.push_back(1);
    stages.push_back(2);
    stages.push_back(6);
    stages.push_back(2);
    stages.push_back(4);
    stages.push_back(3);
    stages.push_back(3);

     실패율이 높은 스테이지 부터 내림차순으로 스테이지의 스테이지 번호가 담겨있느 배열을 return
     같은 실패율이라면 작은 번호의 스테이지가 먼저 오도록
    const vectorint answer = solution(N, stages);

    return 0;
}
#include <string>
#include <vector>

std::vector<int> solution(long long n) {
    std::vector<int> answer;

    char strBuffer[20] = { 0, };
    sprintf(strBuffer, "%lld", n);

    std::string inputStr = strBuffer;
    std::string answerStr;
    const int strSize = static_cast<int>(inputStr.size());
    for(int idx = (strSize - 1); idx >= 0; idx--)
    {
        answerStr = inputStr.at(idx);
        int convertedNumber = atoi(answerStr.c_str());

        answer.push_back(convertedNumber);
    }

    return answer;
}
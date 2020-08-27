#include <string>
#include <vector>


bool solution(std::string s) {
    bool answer = false;

    /**
     * a = 97
     * z = 122
     * A = 65
     * Z = 90
     * 0 = 48
     * 9 = 57
     */
    const int strSize = static_cast<int>(s.size());
    if((4 == strSize) || (6 == strSize))
    {
        for(int idx = 0; idx < strSize; idx++)
        {
            if((48 <= s[idx]) && (57 >= s[idx]))
            {
                continue;
            }
            else
            {
                return answer;
            }
        }
        answer = true;
    }

    return answer;
}
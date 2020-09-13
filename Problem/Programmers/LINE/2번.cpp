#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> solution(vector<int> ball, vector<int> order) {
    vector<int> answer;

    deque<int> ballQue;
    for(const int data : ball) 
    {
        ballQue.push_back(data);
    }
    queue<int> orderQue;
    for(const int data : order)
    {
        orderQue.push(data);
    }

    vector<int> waitList;
    while(true)
    {
        if(true == orderQue.empty())
        {
            break;
        }
        
        const int currOrder = orderQue.front();
        orderQue.pop();
        
        vector<int>::iterator iter;
        for(iter = waitList.begin(); iter != waitList.end(); )
        {
            if(ballQue.front() == *iter)
            {
                ballQue.pop_front();
                answer.push_back(*iter);
                iter = waitList.erase(iter);
                iter = waitList.begin();
                continue;
            }
            else if(ballQue.back() == *iter)
            {
                ballQue.pop_back();
                answer.push_back(*iter);
                iter = waitList.erase(iter);
                iter = waitList.begin();
                continue;
            }
            ++iter;
        }
        if(currOrder == ballQue.front() )
        {
            ballQue.pop_front();
            answer.push_back(currOrder);
        }
        else if(currOrder == ballQue.back())
        {
            ballQue.pop_back();
            answer.push_back(currOrder);
        }
        else
        {
            waitList.push_back(currOrder);
        }
    }

    return answer;
}

int main()
{
    vector<int> ball;
    ball.push_back(11);
    ball.push_back(2);
    ball.push_back(9);
    ball.push_back(13);
    ball.push_back(24);
 

    vector<int> order;
    order.push_back(9);
    order.push_back(2);
    order.push_back(13);
    order.push_back(24);
    order.push_back(11);
    
    vector<int> answer = solution(ball, order);


    return 0;
}
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define MAZE_MAX_SIZE 300
#define DIRECTION 4

void BFS_Search(vector<vector<int>>& maze, int& answer, queue<std::pair<int, int>>& que)
{
    const int rowMax = static_cast<int>(maze.size());
    const int colMax = static_cast<int>(maze[0].size());

    int dirX[] = { 0, 1, -1, 0};
    int dirY[] = { 1, 0, 0, -1};

    vector<pair<int, int>> passed;
    int front = -1;
    int rear = 0;
    que.push(pair<int, int>(0, 0));
    passed.push_back(pair<int, int>(0, 0));
    while(front < rear)
    {
        front++;
        int x = que.front().first;
        int y = que.front().second;
        que.pop();
        if(x == rowMax - 1 && y == rowMax - 1)
        {
            break;
        }

        for(int idx = 0; idx < 4; idx++)
        {
            int nextX = x + dirX[idx];
            int nextY = y + dirY[idx];

            if(nextX < 0 || nextX >= rowMax || nextY < 0 || nextY >= colMax)
            {
                // 이동 안됨
                continue;
            }

            if(maze[nextX][nextY] == 0 && 
                passed.end() == find(passed.begin(), passed.end(), pair<int, int>(nextX, nextY)) )
            {
                rear++;
                std::pair<int, int> pos;
                pos.first = nextX;
                pos.second = nextY;
                que.push(pos);
                passed.push_back(pos);
            }
        }
    }
    answer = passed.size() - 1;
}

int solution(vector<vector<int>> maze) {
    int answer = 0;


    queue<std::pair<int, int>> passedQue;
    BFS_Search(maze, answer, passedQue);

    return answer;
}
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> cards) {
    int answer = -1;

    vector<int> dealer;
    vector<int> player;

    double playerMoney = 0.0;
    int playerSum = 0;
    int dealerSum = 0;
    for(int idx = 0; idx < cards.size(); )
    {
        player.push_back(cards[idx]);
        playerSum += cards[idx];
        idx++;
        dealer.push_back(cards[idx]);
        dealerSum += cards[idx];
        idx++;

        player.push_back(cards[idx]);
        playerSum += cards[idx];
        idx++;
        dealer.push_back(cards[idx]);
        dealerSum += cards[idx];
        idx++;

        if(21 == playerSum)
        {
            if(playerSum > dealerSum)
            {
                playerMoney += 3.0;
            }
            else if(playerSum < dealerSum)
            {

            }
            break;
        }
        
        if(dealerSum == 1 || dealerSum >= 7)
        {
            while(true)
            {
                if(playerSum >= 17 || idx == cards.size() -1)
                    break;
                player.push_back(cards[idx]);
                playerSum += cards[idx];
                idx++;
            }
        }
        if(dealer.end() == find(dealer.begin(), dealer.end(), 4) ||
            dealer.end() == find(dealer.begin(), dealer.end(), 5) ||
            dealer.end() == find(dealer.begin(), dealer.end(), 6))
        {
            player.push_back(cards[idx]);
            playerSum += cards[idx];
            idx++;
        }
    }

    return answer;
}


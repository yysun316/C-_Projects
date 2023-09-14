#include "swiss.h"
#include "match.h"
#include <iostream>

// TASK 4: Implement the conversion constructor and destructor
// shallow copying the list here? I think is deep.
Swiss::Swiss(const int numRounds, const PlayerList &list) : numRounds(numRounds), curRound(0), list(list)
{
    this->list.sort();
}
Swiss::~Swiss()
{
    return;
}

// TASK 5: Implement the function to conduct the Swiss tournament
void Swiss::play()
{
    for (curRound = 1; curRound <= numRounds; curRound++)
    {
        PlayerList *ptr = new PlayerList[2 * curRound - 1];
        int listIndex = 0;
        int playerIndex = list.getNumPlayers() - 1;
        if (playerIndex >= 0)
        {
            ptr[listIndex].addPlayer(list.getPlayer(0));
            for (int curPlayerIndex = 0; curPlayerIndex < playerIndex; ++curPlayerIndex)
            {
                if (list.getPlayer(curPlayerIndex)->getScore() == list.getPlayer(curPlayerIndex + 1)->getScore())
                    ptr[listIndex].addPlayer(list.getPlayer(curPlayerIndex + 1));
                else
                    ptr[++listIndex].addPlayer(list.getPlayer(curPlayerIndex + 1));
            }
        }
        int curList = 0;
        for (; curList < listIndex; curList++)
        {
            int num = ptr[curList].getNumPlayers();
            if (num % 2)
            {
                ptr[curList + 1].addPlayer(ptr[curList].getPlayer(num - 1));
                ptr[curList + 1].sort();
                // ptr[curList].~PlayerList(); // can we call the destructor explicitly? no syntatical error wor!
                // ptr[curList] = *(ptr[curList].splice(0, num - 1)); // ml
                // PlayerList* a = ptr[curList].splice(0, num - 1); // ml
                // delete &(ptr[curList]); //we shd not write this because it'll delete the player object as the same time.
                // ptr[curList] = *a; // it's doing memberwise shallow copy i.e the ptr address is directly modified which causes ml
                // to solve this we need to del the list which is impossible.
                // delete a;
            }
        }
        for (curList = 0; curList <= listIndex; curList++)
        {
            int midIndex = ptr[curList].getNumPlayers() / 2;
            for (int leftIndex = 0, rightIndex = midIndex; leftIndex < midIndex; leftIndex++, rightIndex++)
            {
                Match x{ptr[curList].getPlayer(leftIndex), ptr[curList].getPlayer(rightIndex)};
                x.play();
            }
        }
        if (ptr[listIndex].getNumPlayers() % 2)
            ptr[listIndex].getPlayer(ptr[listIndex].getNumPlayers() - 1)->addScore(2);

        list.sort();
        printLeaderboard();
        // for (int i = 0; i <= listIndex; ++i)
        //     ptr[i].~PlayerList();
        delete[] ptr;
    }
}

#include <iostream>
#include <cstring>
#include "player.h"

// Task 1:
// deep copy
Player::Player(const char *const name, const int elo) : elo(elo), score(0)
{
    // if the name's length is not 0
    if (strlen(name))
    {
        this->name = new char[strlen(name) + 1],
        strcpy(this->name, name);
        return;
    }
    else {
        this->name = nullptr;
    }
}
Player::~Player()
{
    delete[] name;
    name = nullptr;
}

// Task 2: Implement the default constructor, copy constructor and destructor
PlayerList::PlayerList() : numPlayers(0), players(nullptr) {}
// different list pointing same objects
PlayerList::PlayerList(const PlayerList &list) : players(new Player *[list.numPlayers]), numPlayers(list.numPlayers)
{
    for (int i = 0; i < list.numPlayers; ++i)
        players[i] = list.players[i];
}
// don't delete objects but only the pointer list.
PlayerList::~PlayerList()
{
    delete[] players; 
    players = nullptr;
}

// TASK 3: Implement PlayerList insert, sort and splice
// increase the array size by allocating a new array.
void PlayerList::addPlayer(Player *const player)
{
    Player **temp = new Player *[++numPlayers]; //new array with extra number of player
    for (int i = 0; i < numPlayers - 1; ++i)
        temp[i] = players[i]; // copy the address list
    temp[numPlayers - 1] = player; // adding to the end.
    delete[] players; // delete the odd list
    players = temp; // assign the new list

    // for (int i = 0; i < numPlayers;++i)
    //     players[i]->print();
}

void PlayerList::sort()
{
    // bubble sort
    for (int i = 0; i < numPlayers - 1; ++i)
    { // for {0,1,2,3,4} it shd stop at 3
        bool swap = false;
        for (int j = 0; j < numPlayers - i - 1; ++j)
        {
            // The higher score, the smaller the index.
            if (players[j]->getScore() < players[j + 1]->getScore())
            { // first arrange with score
                Player *temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
                swap = true;
            }
            else if (players[j]->getScore() == players[j + 1]->getScore())
            { // if same score, the higher elo, the smaller the index
                if (players[j]->getELO() < players[j + 1]->getELO())
                {
                    Player *temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                    swap = true;
                }
            }
        }
        if (!swap) // array is already sorted
            return;
    }
}
// return a new dynamically allocated playerlist for valid indices
PlayerList *PlayerList::splice(const int startIndex, const int endIndex) const
{
    // invalid indices
    if (startIndex < 0 || endIndex > numPlayers || startIndex >= endIndex)
        return (new PlayerList);

    //valid indices
    PlayerList *temp = new PlayerList;
    temp->numPlayers = endIndex - startIndex; //0,3 means 3 ppl 1,3 means 2ppl
    temp->players = new Player *[endIndex - startIndex];
    for (int i = startIndex, j = 0; i < endIndex; ++i, ++j)
        temp->players[j] = players[i];

    return temp;
}

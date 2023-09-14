#include "hashtable.h"

BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth)
{
    unsigned long long hashValue = id % TABLE_SIZE;

    BoardHashNode *temp = table[hashValue];
    while (temp != nullptr && temp->id != id)
        temp = temp->next;
    if (temp == nullptr|| temp->depth < depth)
        return BoardOptimalMove();
    else
        return temp->optimalMove;
    // if (temp->depth >= depth)
}

void BoardHashTable::updateTable(const unsigned long long id, const int depth, const BoardOptimalMove &optimalMove)
{
    unsigned long long hashValue = id % TABLE_SIZE;

    if (getHashedMove(id,depth).score == ILLEGAL)
    {
        // we cannot find such hashmove or depth of the hashtable is not sufficient;
        BoardHashNode *temp = table[hashValue];
        while (temp != nullptr && temp->id != id)
            temp = temp->next;
        if (temp == nullptr)
        {
            temp = new BoardHashNode(id, depth, optimalMove);
            // insert at the beginning;
            BoardHashNode *ptr = table[hashValue];
            table[hashValue] = temp;
            temp->next = ptr;
        }
        else if (temp->depth < depth)
        {
            // update the depth and move;
            temp->depth = depth;
            temp->optimalMove = optimalMove;
        }
        else{
            // temp->depth >= depth
            // do nothing.
        }
    }
    else{
        // we find such hashmove or the depth of the hash table is sufficient; 
        // do nothing;
    }
}

void BoardHashTable::clearTable(){
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        // delete table[i];
        // table[i] = nullptr;
        BoardHashNode *curNode = table[i];
        BoardHashNode *preNode = nullptr;
        while (curNode != nullptr)
        {
            preNode = curNode;
            curNode = curNode->next;
            delete preNode;
        }
        table[i] = nullptr;
    }
}
/*
while
*/

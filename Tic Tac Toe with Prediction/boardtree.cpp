#include "boardtree.h"
#include "hashtable.h"

BoardTree::BoardTree(const Board &board) : root(new BoardNode{board}) {}

BoardTree::~BoardTree()
{
    delete root;
    root = nullptr;
}

BoardTree *BoardTree::getSubTree(const BoardCoordinate &coords)
{
    if (root->subTree[coords.row][coords.col].isEmpty())
    {
        Board temp = root->board;
        if (temp.play(coords))
        {
            root->subTree[coords.row][coords.col].root = new BoardNode{temp};
        }
    }
    return &(root->subTree[coords.row][coords.col]);
}

BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth)
{

    if (isEmpty())
    {
        return BoardOptimalMove(); // Returns a dummy illegal move
    }

    if (depth == 0 || root->board.isFinished())
    {
        return BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate(0, 0));
        // BoardOptimalMove move = BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate(0, 0));
        // BoardHashTable::getInstance().updateTable(root->board.getID(), depth, move);
        // return move;
    }
    
    if (BoardHashTable::getInstance().getHashedMove(root->board.getID(), depth).score != ILLEGAL)
    {
        return BoardHashTable::getInstance().getHashedMove(root->board.getID(), depth);
    }
    int estimatedScore;
    root->board.getCurPlayer() == X ? estimatedScore = -100000000 : estimatedScore = 100000000;
    BoardOptimalMove bestMove;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            BoardTree *subtree = getSubTree(BoardCoordinate(i, j));
            BoardOptimalMove childMove = subtree->getOptimalMove(depth - 1);

            if (childMove.score == ILLEGAL)
            {
                // If the move is illegal, the subtree corresponds to an invalid move/board, simply skip to the next subtree
                continue;
            }
            // parent node max/ min = child max/min;
            if (childMove.score > estimatedScore && root->board.getCurPlayer() == X ||
                childMove.score < estimatedScore && root->board.getCurPlayer() == O)
            {
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, BoardCoordinate(i, j));
            }
        }
    BoardHashTable::getInstance().updateTable(root->board.getID(), depth, bestMove);
    return bestMove;
}

BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta)
{
    if (isEmpty())
    {
        return BoardOptimalMove();
    }

    if (depth == 0 || root->board.isFinished())
    {
        return BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate(0, 0));
    }

    int estimatedScore;
    root->board.getCurPlayer() == X ? estimatedScore = -100000000 : estimatedScore = 100000000;
    BoardOptimalMove bestMove;
    bool breaker = false;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            BoardTree *subtree = getSubTree(BoardCoordinate(i, j));
            BoardOptimalMove childMove = subtree->getOptimalMoveAlphaBeta(depth - 1, alpha, beta);

            if (childMove.score == ILLEGAL)
            {
                continue;
            }
            if (childMove.score > estimatedScore && root->board.getCurPlayer() == X ||
                childMove.score < estimatedScore && root->board.getCurPlayer() == O)
            {
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, BoardCoordinate(i, j));
            }
            // ADDED: Update alpha and beta according to newest child score found
            if (root->board.getCurPlayer() == X) // max
            {
                if (childMove.score > beta) // alpha(-inf) > beta, no need check
                {
                    // Found a move that would be worse for O, so O will not consider this subtree
                    breaker = true;
                    break;
                }
                // Update the best move found by X
                alpha = (childMove.score > alpha) ? childMove.score: alpha;
                // alpha = childMove.score;
            }
            else // min
            {
                // Same logic but for current player O
                if (childMove.score < alpha) // beta < alpha, no need check;
                {
                    breaker = true;
                    break;
                }
                // beta = childMove.score;
                beta = (childMove.score < beta) ? childMove.score: beta;
            }
        }
        if (breaker)
            break;
    }
    return bestMove;
}

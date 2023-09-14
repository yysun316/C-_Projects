#include "board.h"
// score(score)
Board::Board(const int score[][BOARD_SIZE]) : cells(), score(), curPlayer(X), id(0)
{
    // this->score = score; direct assignment between arrays is not possible;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            this->score[i][j] = score[i][j];
        }
    }
}

bool Board::isFull() const
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (cells[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

bool Board::isFinished() const
{ // assume boardsize>1;
    if (isFull())
        return true;

    // check horizontal;
    //  111
    // Cell temp = cells[0][0];
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 1; col < BOARD_SIZE; ++col)
        {
            if (cells[row][0] != cells[row][col] || cells[row][0] == EMPTY)
            {
                // temp = cells[row + 1][0]; // check next row
                break;
            }
            if (col == BOARD_SIZE - 1)
                return true;
        }
    }

    // check vertical;
    // temp = cells[0][0];
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        for (int row = 1; row < BOARD_SIZE; ++row)
        {
            if (cells[0][col] != cells[row][col] || cells[0][col] == EMPTY)
            {
                // temp = cells[0][col + 1]; // check next row
                break;
            }
            if (row == BOARD_SIZE - 1)
                return true;
        }
    }

    for (int i = 0; i < BOARD_SIZE - 1; ++i)
    {
        if (cells[i][i] != cells[i + 1][i + 1] || cells[i][i] == EMPTY) // diagonal;
            break;
        else if (i == BOARD_SIZE - 2)
            return true;
    }

    for (int i = 0, j = BOARD_SIZE - 1; i < BOARD_SIZE - 1; ++i, --j)
    {
        if (cells[i][j] != cells[i + 1][j - 1] || cells[i][j] == EMPTY) // off-diagonal;
            break;
        else if (i == BOARD_SIZE - 2)
            return true;
    }
    return false;
}

int Board::getBoardScore() const
{
    // horizontal;
    // Cell temp = cells[0][0];
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 1; col < BOARD_SIZE; ++col)
        {
            if (cells[row][0] != cells[row][col] || cells[row][0] == EMPTY)
            {
                // temp = cells[row + 1][0]; // check next row
                break;
            }
            if (col == BOARD_SIZE - 1)
                return (cells[row][0] == X ? WIN_SCORE : -WIN_SCORE);
        }
    }

    // check vertical;
    // temp = cells[0][0];
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        for (int row = 1; row < BOARD_SIZE; ++row)
        {
            if (cells[0][col] != cells[row][col] || cells[0][col] == EMPTY)
            {
                // temp = cells[0][col + 1]; // check next row
                break;
            }
            if (row == BOARD_SIZE - 1)
                return (cells[0][col] == X ? WIN_SCORE : -WIN_SCORE);
        }
    }

    for (int i = 0; i < BOARD_SIZE - 1; ++i)
    {
        if (cells[i][i] != cells[i + 1][i + 1] || cells[i][i] == EMPTY) // diagonal;
            break;
        else if (i == BOARD_SIZE - 2)
            return (cells[i][i] == X ? WIN_SCORE : -WIN_SCORE);
    }

    for (int i = 0, j = BOARD_SIZE - 1; i < BOARD_SIZE - 1; ++i, --j)
    {
        if (cells[i][j] != cells[i + 1][j - 1] || cells[i][j] == EMPTY) // off-diagonal;
            break;
        else if (i == BOARD_SIZE - 2)
            return (cells[i][j] == X ? WIN_SCORE : -WIN_SCORE);
    }

    // calculate the score based on the current cells on the board;
    int score = 0;
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (cells[row][col] == X)
                score += getCellWeight(cells[row][col]) * this->score[row][col];
            else if (cells[row][col] == O)
                score -= getCellWeight(cells[row][col]) * this->score[row][col];
        }
    }
    return score;
}

bool Board::play(const BoardCoordinate &coords)
{
    if (!coords.isValid()) // check if out of bound;
        return false;
    if (cells[coords.row][coords.col] != EMPTY) // check if filled;
        return false;

    // Update the cells, curPlayer, id
    cells[coords.row][coords.col] = curPlayer;
    /*
    id = 0;
    for each cell {
    cellValue = 0 if cell is empty, 1 if cell is X, 2 if cell is 0;
    id += cellValue * (3 ^ (row * 3 + column));
    }
    */
    int cellValue;
    cellValue = id = 0;
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (cells[row][col] == EMPTY)
                continue;
            cells[row][col] == X ? cellValue = 1 : cellValue = 2;
            id += cellValue * pow(3, (row * BOARD_SIZE + col));
        }
    }
    curPlayer == X ? curPlayer = O : curPlayer = X;
    return true;
}
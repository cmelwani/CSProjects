/*
 * Comp 15 Recursion and Mazes Lab
 * 
 * A position in 2 dimensions:  row and column.
 *
 * Given a position, can compute position to the north, south, east,
 * or west, and can test whether the position is within some given
 * bounds. 
 *
 * (c) Mark A. Sheldon, Tufts University, Spring 2017.
 */
#ifndef POSITION_H
#define POSITION_H

struct Position {
        int row, col;
        Position()
        {
                row = col = 0;
        }
        Position(int r, int c)
        {
                row = r;
                col = c;
        }
        Position north()
        {
                return Position(row - 1, col);
        }
        Position south()
        {
                return Position(row + 1, col);
        }
        Position east()
        {
                return Position(row, col + 1);
        }
        Position west()
        {
                return Position(row, col - 1);
        }
        bool inBounds(int rowLimit, int colLimit)
        {
                return (0 < row) and (row < rowLimit)
                        and (0 < col) and (col < colLimit);
        }
};

#endif

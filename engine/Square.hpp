#pragma once

struct Square
{
    int row;
    int col;
};


inline bool operator==(const Square& a, const Square& b) {
    return a.row == b.row && a.col == b.col;
}
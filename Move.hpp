#pragma once

#include "Square.hpp"

enum class MoveFlag{
    Normal,
    PromotionQueen,
    PromotionRook,
    PromotionKnight,
    PromotionBishop,

    EnPassantCapture,
    EnPassantTarget,
};

struct Move{
    Square from;
    Square to;
    MoveFlag flag=MoveFlag::Normal;
};
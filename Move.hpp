#pragma once

#include "Input.hpp"

enum class MoveFlag{
    Normal,
    PromotionQueen,
    PromotionRook,
    PromotionKnight,
    PromotionBishop
};

struct Move{
    Square from;
    Square to;
    MoveFlag flag=MoveFlag::Normal;
};
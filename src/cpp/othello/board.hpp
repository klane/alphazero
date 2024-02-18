#pragma once

#include "../board.hpp"

namespace alphazero::othello {

const uint8_t NUM_DIRECTIONS = 8;
const uint8_t BOARD_SIZE = 8;
const uint8_t BOARD_SPACES = BOARD_SIZE * BOARD_SIZE;

const Position FULL_MASK = Position(BOARD_SPACES, 0xFFFFFFFFFFFFFFFF);
const Position EDGE_MASK = Position(BOARD_SPACES, 0x7E8181818181817E);
const Position CORNER_MASK = Position(BOARD_SPACES, 0x8100000000000081);
const Position LEFT_RIGHT_MASK = Position(BOARD_SPACES, 0x7E7E7E7E7E7E7E7E);
const Position TOP_BOTTOM_MASK = Position(BOARD_SPACES, 0x00FFFFFFFFFFFF00);
const Position INTERIOR_MASK = LEFT_RIGHT_MASK & TOP_BOTTOM_MASK;

const BoardPosition START_POSITIONS = {
    Position(BOARD_SPACES, 0x0000000810000000),
    Position(BOARD_SPACES, 0x0000001008000000),
};

const std::array<Position, NUM_DIRECTIONS> SHIFT_MASKS = {
    Position(BOARD_SPACES, 0x7F7F7F7F7F7F7F7F),
    Position(BOARD_SPACES, 0x007F7F7F7F7F7F7F),
    FULL_MASK,
    Position(BOARD_SPACES, 0x00FEFEFEFEFEFEFE),
    Position(BOARD_SPACES, 0xFEFEFEFEFEFEFEFE),
    Position(BOARD_SPACES, 0xFEFEFEFEFEFEFE00),
    FULL_MASK,
    Position(BOARD_SPACES, 0x7F7F7F7F7F7F7F00),
};

const std::array<uint8_t, NUM_DIRECTIONS> SHIFT_BITS = {
    1,
    BOARD_SIZE + 1,
    BOARD_SIZE,
    BOARD_SIZE - 1,
    1,
    BOARD_SIZE + 1,
    BOARD_SIZE,
    BOARD_SIZE - 1,
};

class Board: public alphazero::Board {
    public:
        Board();

        Position captured(Color player, Position move);
        void make_move(Color player, Position move);
        int player_corners(Color player);
        int player_edges(Color player);
        int player_frontier(Color player);
        int player_interior(Color player);
        int score(Color player);
        Position valid_moves(Color player);
};

Position shift(Position position, int direction);

}

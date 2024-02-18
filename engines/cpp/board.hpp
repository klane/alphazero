#pragma once

#include <array>
#include <vector>

#include <boost/dynamic_bitset.hpp>

namespace alphazero {

const uint8_t NUM_PLAYERS = 2;

using Position = boost::dynamic_bitset<>;
using PositionSet = std::vector<Position>;
using BoardPosition = std::array<Position, NUM_PLAYERS>;

enum Color: uint8_t {
    BLACK = 0,
    WHITE = 1
};

struct Coordinate {
    const uint8_t row;
    const uint8_t col;

    Coordinate(const uint8_t row, const uint8_t col) :
        row(row),
        col(col)
    {}
};

class Board {
    public:
        const uint8_t rows;
        const uint8_t cols;
        const BoardPosition start_positions;
        BoardPosition positions;

        Board(const uint8_t rows, const uint8_t cols);
        Board(
            const BoardPosition start_positions, const uint8_t rows, const uint8_t cols
        );

        Position empty();
        Position filled();
        Position get_position(Position::size_type index);
        bool is_full();
        int num_empty();
        int player_count(Color player);
        Position player_position(Color player);

        void make_move(Color player, Position move);
        void make_move(Color player, Position::size_type index);
        Board peek(Color player, Position move);
        void reset();
        Position valid_moves(Color player);
};

Coordinate position_to_coordinate(
    Position position, const uint8_t rows, const uint8_t cols
);

PositionSet split_position(Position position);

}

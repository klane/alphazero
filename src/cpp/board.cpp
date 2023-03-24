#include "board.hpp"

namespace alphazero {

Board::Board(const uint8_t rows, const uint8_t cols) :
    Board::Board({Position(rows * cols), Position(rows * cols)}, rows, cols)
{}

Board::Board(const BoardPosition start_positions, const uint8_t rows, const uint8_t cols) :
    rows(rows),
    cols(cols),
    start_positions(start_positions),
    positions(start_positions)
{}

Position Board::empty() {
    return filled().flip();
}

Position Board::filled() {
    return positions[BLACK] | positions[WHITE];
}

bool Board::is_full() {
    return filled().all();
}

void Board::make_move(Color player, Position move) {
    positions[player] |= move;
}

void Board::make_move(Color player, Position::size_type index) {
    Position move(rows * cols);
    move.set(index);
    make_move(player, move);
}

int Board::num_empty() {
    return empty().count();
}

Board Board::peek(Color player, Position move) {
    Board board(*this);
    board.make_move(player, move);
    return board;
}

int Board::player_count(Color player) {
    return positions[player].count();
}

Position Board::player_position(Color player) {
    return positions[player];
}

void Board::reset() {
    positions = start_positions;
}

Position Board::valid_moves(Color player) {
    return empty();
}

Coordinate position_to_coordinate(Position position, const uint8_t rows, const uint8_t cols) {
    const Position::size_type index = position.find_first();

    if (index == Position::npos)
        return Coordinate(-1, -1);

    return Coordinate((int) index / rows, index % cols);
}

PositionSet split_position(Position position) {
    PositionSet position_set;
    Position::size_type index = position.find_first();

    while (index != Position::npos) {
        Position temp(position.size());
        temp.set(index);
        position_set.push_back(temp);
        index = position.find_next(index);
    }

    return position_set;
}

}

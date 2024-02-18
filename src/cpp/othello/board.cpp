#include "board.hpp"

namespace alphazero::othello {

Board::Board() :
    alphazero::Board(START_POSITIONS, BOARD_SIZE, BOARD_SIZE)
{}

Position Board::captured(Color player, Position move) {
    Position captured(move), x(BOARD_SPACES), empty(BOARD_SPACES);
    Position current(positions[player]), opponent(positions[player ^ 1]);

    for (int dir=0; dir<NUM_DIRECTIONS; dir++) {
        x = shift(move, dir) & opponent;

        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;

        captured |= (shift(x, dir) & current).count() > 0 ? x : empty;
    }

    return captured;
}

void Board::make_move(Color player, Position move) {
    Position captured_position = captured(player, move);
    positions[player] |= captured_position;
    positions[player ^ 1] &= ~captured_position;
}

int Board::player_corners(Color player) {
    return (positions[player] & CORNER_MASK).count();
}

int Board::player_edges(Color player) {
    return (positions[player] & EDGE_MASK).count();
}

int Board::player_frontier(Color player) {
    Position current(positions[player]);
    Position opponent(positions[player ^ 1]);
    Position empty = (current | opponent) ^ FULL_MASK;
    Position frontier(BOARD_SPACES), x(BOARD_SPACES);

    for (int dir=0; dir<NUM_DIRECTIONS; dir++) {
        x = shift(empty, dir) & SHIFT_MASKS[dir];
        frontier |= x & current;
    }

    frontier &= ~CORNER_MASK;
    return frontier.count();
}

int Board::player_interior(Color player) {
    return (positions[player] & INTERIOR_MASK).count();
}

int Board::score(Color player) {
    int score = player_count(BLACK) - player_count(WHITE);
    return (player == BLACK) ? score : -score;
}

Position Board::valid_moves(Color player) {
    Position moves(BOARD_SPACES), x(BOARD_SPACES);
    Position current(positions[player]), opponent(positions[player ^ 1]);
    Position empty_cells(empty());

    for (int dir=0; dir<NUM_DIRECTIONS; dir++) {
        x = shift(current, dir) & opponent;

        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;
        x |= shift(x, dir) & opponent;

        moves |= shift(x, dir) & empty_cells;
    }

    return moves;
}

Position shift(Position position, int direction) {
    if (direction < NUM_DIRECTIONS / 2) {
        return (position >> SHIFT_BITS[direction]) & SHIFT_MASKS[direction];
    } else {
        return (position << SHIFT_BITS[direction]) & SHIFT_MASKS[direction];
    }
}

}

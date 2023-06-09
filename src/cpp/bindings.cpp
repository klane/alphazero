#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "board.hpp"

namespace py = pybind11;
using namespace alphazero;

PYBIND11_MODULE(alphazero_cpp, m) {
    py::enum_<Color>(m, "Color")
        .value("BLACK", Color::BLACK)
        .value("WHITE", Color::WHITE);

    py::class_<Coordinate>(m, "Coordinate")
        .def(py::init<const uint8_t, const uint8_t>())
        .def_readonly("row", &Coordinate::row)
        .def_readonly("col", &Coordinate::col);

    py::class_<Position>(m, "Position")
        .def(py::init<const uint8_t>())
        .def("all", &Position::all)
        .def("any", &Position::any)
        .def("count", &Position::count)
        .def("none", &Position::none)
        .def("reset", py::overload_cast<>(&Position::reset))
        .def("set", py::overload_cast<size_t, bool>(&Position::set), py::arg("n"), py::arg("val") = true)
        .def("size", &Position::size);

    py::class_<Board>(m, "Board")
        .def(py::init<const uint8_t, const uint8_t>())
        .def_readonly("rows", &Board::rows)
        .def_readonly("cols", &Board::cols)
        .def_readonly("start_positions", &Board::start_positions)
        .def("empty", &Board::empty)
        .def("filled", &Board::filled)
        .def("is_full", &Board::is_full)
        .def("num_empty", &Board::num_empty)
        .def("player_count", &Board::player_count)
        .def("player_position", &Board::player_position)
        .def("peek", &Board::peek)
        .def("make_move", &Board::make_move)
        .def("reset", &Board::reset)
        .def("valid_moves", &Board::valid_moves);

    m.def("position_to_coordinate", &position_to_coordinate);
    m.def("split_position", &split_position);
}

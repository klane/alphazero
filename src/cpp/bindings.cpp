#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "board.hpp"

namespace py = pybind11;
using namespace alphazero;

PYBIND11_MODULE(engine, m) {
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
        .def("capacity", &Position::capacity)
        .def("count", &Position::count)
        .def("find_first", &Position::find_first)
        .def("none", &Position::none)
        .def("reset", py::overload_cast<>(&Position::reset))
        .def("set", py::overload_cast<size_t, bool>(&Position::set), py::arg("n"), py::arg("val") = true)
        .def("size", &Position::size)
        .def("test", &Position::test)
        .def("to_ulong", &Position::to_ulong);

    py::class_<Board>(m, "Board")
        .def(py::init<const uint8_t, const uint8_t>())
        .def_readonly("rows", &Board::rows)
        .def_readonly("cols", &Board::cols)
        .def_readonly("start_positions", &Board::start_positions)
        .def("empty", &Board::empty)
        .def("filled", &Board::filled)
        .def("get_position", &Board::get_position)
        .def("is_full", &Board::is_full)
        .def("num_empty", &Board::num_empty)
        .def("player_count", &Board::player_count)
        .def("player_position", &Board::player_position)
        .def("peek", &Board::peek)
        .def("make_move", py::overload_cast<Color, Position>(&Board::make_move))
        .def("make_move", py::overload_cast<Color, Position::size_type>(&Board::make_move))
        .def("reset", &Board::reset)
        .def("valid_moves", &Board::valid_moves);

    m.def("position_to_coordinate", &position_to_coordinate);
    m.def("split_position", &split_position);
}

from __future__ import annotations
import typing
from . import othello
__all__ = ['Board', 'Color', 'Coordinate', 'Position', 'othello', 'position_to_coordinate', 'split_position']
class Board:
    def __init__(self, arg0: int, arg1: int) -> None:
        ...
    def empty(self) -> Position:
        ...
    def filled(self) -> Position:
        ...
    def get_position(self, arg0: int) -> Position:
        ...
    def is_full(self) -> bool:
        ...
    @typing.overload
    def make_move(self, arg0: Color, arg1: Position) -> None:
        ...
    @typing.overload
    def make_move(self, arg0: Color, arg1: int) -> None:
        ...
    def num_empty(self) -> int:
        ...
    def peek(self, arg0: Color, arg1: Position) -> Board:
        ...
    def player_count(self, arg0: Color) -> int:
        ...
    def player_position(self, arg0: Color) -> Position:
        ...
    def reset(self) -> None:
        ...
    def valid_moves(self, arg0: Color) -> Position:
        ...
    @property
    def cols(self) -> int:
        ...
    @property
    def rows(self) -> int:
        ...
    @property
    def start_positions(self) -> list[Position[2]]:
        ...
class Color:
    """
    Members:
    
      BLACK
    
      WHITE
    """
    BLACK: typing.ClassVar[Color]  # value = <Color.BLACK: 0>
    WHITE: typing.ClassVar[Color]  # value = <Color.WHITE: 1>
    __members__: typing.ClassVar[dict[str, Color]]  # value = {'BLACK': <Color.BLACK: 0>, 'WHITE': <Color.WHITE: 1>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class Coordinate:
    def __init__(self, arg0: int, arg1: int) -> None:
        ...
    @property
    def col(self) -> int:
        ...
    @property
    def row(self) -> int:
        ...
class Position:
    def __init__(self, arg0: int) -> None:
        ...
    def all(self) -> bool:
        ...
    def any(self) -> bool:
        ...
    def capacity(self) -> int:
        ...
    def count(self) -> int:
        ...
    def find_first(self) -> int:
        ...
    def none(self) -> bool:
        ...
    def reset(self) -> Position:
        ...
    def set(self, n: int, val: bool = True) -> Position:
        ...
    def size(self) -> int:
        ...
    def test(self, arg0: int) -> bool:
        ...
    def to_ulong(self) -> int:
        ...
def position_to_coordinate(arg0: Position, arg1: int, arg2: int) -> Coordinate:
    ...
def split_position(arg0: Position) -> list[Position]:
    ...

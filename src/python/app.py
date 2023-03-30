from itertools import product

import pygame as pg
from pygame import gfxdraw

from alphazero.engine import Board, Color, Position, split_position

CAPTION = 'AlphaZero'
PLAYER1_COLOR = pg.Color('black')
PLAYER2_COLOR = pg.Color('white')
MOVE_COLOR = pg.Color('green')
BOARD_COLOR = pg.Color('forestgreen')
GRID_COLOR = pg.Color('black')
BACKGROUND_COLOR = pg.Color('black')
GRAPH_LINE_COLOR = pg.Color('white')
TEXT_COLOR = pg.Color('black')


class App:
    def __init__(self, size: int) -> None:
        self.game = Board(8, 8)
        self.size = size
        self.running = True
        self.current_player = Color.BLACK

        cell_height = self.size // self.game.rows
        cell_width = self.size // self.game.cols
        self.move_radius = int(min(cell_height // 8, cell_width // 8))

        screen_size = size, size
        self.screen = pg.display.set_mode(screen_size)
        self.board = pg.Rect(0, 0, size, size)
        self.cells: list[pg.Rect] = []

        for r, c in product(range(self.game.rows), range(self.game.cols)):
            x = c * cell_width
            y = r * cell_height
            cell = pg.Rect(x, y, cell_width, cell_height)
            self.cells.append(cell)

    def draw_circle(self, position: Position, radius: int, color: pg.Color) -> None:
        x, y = self.cells[position.find_first()].center
        gfxdraw.aacircle(self.screen, x, y, radius, color)
        gfxdraw.filled_circle(self.screen, x, y, radius, color)

    def event_loop(self) -> None:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False
            elif event.type == pg.MOUSEBUTTONDOWN:
                pos = pg.mouse.get_pos()
                if self.board.collidepoint(pos):
                    print("Clicked on the board")
                    for i, c in enumerate(self.cells):
                        if c.collidepoint(pos):
                            print(f"Clicked on cell {i}")

    def render(self) -> None:
        pg.display.set_caption(CAPTION)
        self.screen.fill(BOARD_COLOR)

        for c in self.cells:
            pg.draw.rect(self.screen, BACKGROUND_COLOR, c, 2)

        for position in split_position(self.game.valid_moves(self.current_player)):
            self.draw_circle(position, self.move_radius, MOVE_COLOR)

        pg.display.update()

    def start(self) -> None:
        while self.running:
            self.event_loop()
            self.render()

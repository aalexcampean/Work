from Board.MyBoard import Board
from Game.MyGame import Game
from UI.Ui import UI

my_board = Board()

my_game = Game(my_board)

ui = UI(my_game)
ui.start()

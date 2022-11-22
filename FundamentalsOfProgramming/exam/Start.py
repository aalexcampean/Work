from Board.MyBoard import Board
from Game.MyGame import Game
from UI.Ui import UI
from jproperties import Properties

configs = Properties()
with open('settings.properties', 'rb') as config_file:
    configs.load(config_file)

dimensions = int(configs.get('dim').data)
nr_of_apples = int(configs.get('apple_count').data)

my_board = Board(dimensions, nr_of_apples)

my_game = Game(my_board)

ui = UI(my_game)
ui.start()

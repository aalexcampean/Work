from BoardLayer.Board import Board
from GameLayer.Game import Game
from StrategyLayer.Strategy import RandomMoveStrategy, SmartMoveStrategy
from UI.Ui import UI
from jproperties import Properties

configs = Properties()
with open('settings.properties', 'rb') as config_file:
    configs.load(config_file)

difficulty = configs.get('difficulty').data

my_board = Board()

if difficulty == 'Easy':
    the_strategy = RandomMoveStrategy()
elif difficulty == 'Medium':
    the_strategy = SmartMoveStrategy()

my_game = Game(my_board, the_strategy)

ui = UI(the_strategy, my_game)
ui.start()

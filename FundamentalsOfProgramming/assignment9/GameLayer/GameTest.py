import unittest
from BoardLayer.Board import Board
from GameLayer.Game import Game
from StrategyLayer.Strategy import RandomMoveStrategy


class GameTest(unittest.TestCase):

    def test_game(self):

        b = Board()
        s = RandomMoveStrategy()
        g = Game(b, s)

        self.assertEqual(g.check_if_game_is_won(4, 4, 'R'), False)
        self.assertEqual(g.human_move(4, 'R'), False)
        self.assertEqual(g.computer_move('Y', 'R'), False)
        self.assertEqual(b.is_free(5, 4), False)
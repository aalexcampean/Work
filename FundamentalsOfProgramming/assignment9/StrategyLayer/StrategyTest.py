import unittest

from BoardLayer.Board import Board
from StrategyLayer.Strategy import RandomMoveStrategy, SmartMoveStrategy


class StrategyTest(unittest.TestCase):

    def test_strategy(self):
        strategy1 = RandomMoveStrategy()
        strategy2 = SmartMoveStrategy()

        b = Board()

        for i in range(3):
            b.move(0, 'R')

        move1 = strategy2.next_move(b, 'Y', 'R')
        self.assertEqual(move1, (2, 0, 'Y'))

        for i in range(1, 4):
            b.move(i, 'Y')

        move2 = strategy2.next_move(b, 'Y', 'R')
        self.assertEqual(move2, (5, 4, 'Y'))

        move3 = strategy1.next_move(b, 'Y', 'R')
        self.assertEqual(move3[2], 'Y')
import unittest
from BoardLayer.Board import Board


class BoardTest(unittest.TestCase):

    def test_board(self):

        b = Board()

        self.assertEqual(b.nr_of_rows, 6)
        self.assertEqual(b.nr_of_columns, 7)
        self.assertEqual(b.get(1, 1), None)
        self.assertEqual(b.is_free(4, 4), True)

        m = b.move(4, 'R')
        n = 5, 4, 'R'

        self.assertEqual(b.get(5, 4), 'R')
        self.assertEqual(m, n)

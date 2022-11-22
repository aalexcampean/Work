from texttable import Texttable


class Board:
    def __init__(self):

        self._rows = 6
        self._columns = 7

        # Empty squares marked with None
        self._data = [[None for j in range(self._columns)] for i in range(self._rows)]

        # Count the number of unoccupied squares remaining
        self._empty_circles = self._columns

    @property
    def nr_of_rows(self):
        """
        Getter fot the number of rows
        :return:
        """
        return self._rows

    @property
    def nr_of_columns(self):
        """
        Getter fot the number of columns
        :return:
        """
        return self._columns

    def get(self, x, y):
        """
        Return symbol at position [x,y] on board
            None     -> empty circle
            'R', 'Y' -> the playing colors
        """
        return self._data[x][y]

    def is_free(self, x, y):
        """
        Checks if a given circle is free
        :param x: the x coordinate
        :param y: the y coordinate
        :return:
        """
        return self.get(x, y) is None

    def move(self, y, color):
        """
        This function makes a move by choosing the given column and placing the circle in the free slot
        of that column
        :param y: the y coordinate
        :param color: the color of the given payer
        :return: the x, y, color and make the move
        """

        not_full = False
        x = self._rows - 1
        while x >= 0 and not not_full:
            if self.is_free(x, y):
                not_full = True
            else:
                x -= 1

        if color not in ['R', 'Y']:
            raise Exception('Wrong color!')
        if not not_full:
            raise Exception('No more empty circles left on this row!')

        # Mark the new move on the board
        self._data[x][y] = color
        if x == 0:
            self._empty_circles -= 1
        return x, y, color

    def delete_move(self, x, y):
        """
        This function deletes a move, sets the value of that slot back to None
        :param x: the x coordinate
        :param y: the y coordinate
        :return:
        """
        self._data[x][y] = None

    def __str__(self):
        """
        The string representation of the game board
        :return:
        """
        t = Texttable()
        t.header(['A', 'B', 'C', 'D', 'E', 'F', 'G'])
        for row in range(6):
            row_data = []

            for index in self._data[row]:
                if index is None:
                    row_data.append(' ')
                elif index == 'R' or index == 'Y':
                    row_data.append(index)
            t.add_row(row_data)

        return t.draw()
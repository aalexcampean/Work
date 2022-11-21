from texttable import Texttable
from random import choice


class Board:
    def __init__(self):

        self._rows = 8
        self._columns = 9

        # Empty squares marked with None
        self._data = [[None for j in range(self._columns)] for i in range(self._rows)]
        for i in range(self._rows):
            self._data[i][0] = chr(65 + i)

        self.place_stars()
        self.place_endeavour()
        self.place_cruisers(3)


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

    @property
    def endeavour(self):
        """
        Getter for the current position of the endeavour
        :return:
        """
        for i in range(self._rows):
            for j in range(1, self._columns):
                if self.get(i, j) == 'E':
                    return i, j

    @property
    def nr_of_cruisers(self):
        """
        Getter fot the number of cruisers left in the game
        :return:
        """
        count = 0
        for i in range(self._rows):
            for j in range(1, self._columns):
                if self.get(i, j) == 'B':
                    count += 1
        return count - 1

    def get(self, x, y):
        """
        Return symbol at position [x,y] on board
            None     -> empty circle
            'R', 'Y' -> the playing colors
        """
        return self._data[x][y]

    def check_surroundings(self, x, y):
        """
        This function checks for the surroundings of a given place on the board to ensure that a star can
        be placed on that specific spot or not
        :param x: the x coordinate
        :param y: the y coordinate
        :return: true if it can be placed or false otherwise
        """
        if x == 0:
            if y == 1:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] is None and \
                        self._data[x + 1][y] is None and \
                        self._data[x + 1][y + 1] is None

            elif y == 8:
                return self._data[x][y] is None and \
                        self._data[x][y - 1] is None and \
                        self._data[x + 1][y] is None and \
                        self._data[x - 1][y - 1] is None

            else:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] is None and \
                        self._data[x][y - 1] is None and \
                        self._data[x + 1][y] is None and \
                        self._data[x + 1][y + 1] is None and \
                        self._data[x + 1][y - 1] is None

        elif x == 7:
            if y == 1:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] is None and \
                        self._data[x - 1][y] is None and \
                        self._data[x - 1][y + 1] is None

            elif y == 8:
                return self._data[x][y] is None and \
                        self._data[x][y - 1] is None and \
                        self._data[x - 1][y] is None and \
                        self._data[x - 1][y - 1] is None

            else:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] is None and \
                        self._data[x][y - 1] is None and \
                        self._data[x - 1][y] is None and \
                        self._data[x - 1][y + 1] is None and \
                        self._data[x - 1][y - 1] is None

        elif y == 1:
            return self._data[x][y] is None and \
                    self._data[x][y + 1] is None and \
                    self._data[x - 1][y] is None and \
                    self._data[x + 1][y] is None and \
                    self._data[x - 1][y + 1] is None and \
                    self._data[x + 1][y + 1] is None

        elif y == 8:
            return self._data[x][y] is None and \
                   self._data[x][y - 1] is None and \
                   self._data[x - 1][y] is None and \
                   self._data[x + 1][y] is None and \
                   self._data[x - 1][y - 1] is None and \
                   self._data[x + 1][y - 1] is None

        else:
            return self._data[x][y] is None and \
                    self._data[x][y + 1] is None and \
                    self._data[x][y - 1] is None and \
                    self._data[x - 1][y] is None and \
                    self._data[x + 1][y] is None and \
                    self._data[x - 1][y + 1] is None and \
                    self._data[x - 1][y - 1] is None and \
                    self._data[x + 1][y - 1] is None and \
                    self._data[x + 1][y + 1] is None

    def place_stars(self):
        """
        This function places randomly the stars on the board
        :return:
        """
        count = 0
        ok = False

        while not ok:
            i = choice([0, 1, 2, 3, 4, 5, 6, 7])
            j = choice([1, 2, 3, 4, 5, 6, 7, 8])

            if self.check_surroundings(i, j):
                self._data[i][j] = '*'
                count += 1

            if count == 10:
                ok = True

    def place_endeavour(self):
        """
        This function places randomly the endeavour on the board
        :return:
        """
        ok = False

        while not ok:
            i = choice([0, 1, 2, 3, 4, 5, 6, 7])
            j = choice([1, 2, 3, 4, 5, 6, 7, 8])

            if self._data[i][j] is None:
                self._data[i][j] = 'E'
                ok = True

    def place_cruisers(self, number_of_cruisers):
        """
        This function places randomly the cruisers on the board
        :return:
        """
        ok = False
        count = 0

        while not ok:
            i = choice([0, 1, 2, 3, 4, 5, 6, 7])
            j = choice([1, 2, 3, 4, 5, 6, 7, 8])

            if self._data[i][j] is None:
                self._data[i][j] = 'B'
                count += 1

            if count == number_of_cruisers:
                ok = True

    def move(self, x, y):
        """
        This function makes a move on the board
        :param x: the x coordinate of the endeavour
        :param y: the y coordinate of the endeavour
        :return: make the move and returns true if possible or does not and returns false if the move
        was made on a cruiser, meaning that the endeavour was destroyed and the game lost
        """

        i, j = self.endeavour

        if self._data[x][y] == 'B':
            return False

        self._data[i][j] = None
        self._data[x][y] = 'E'

        return True

    def fire(self, x, y):
        """
        This function fires at cruisers that are adjacent to the endeavour and destroys them. If one is
        destroyed, the others are rearranged
        :param x: the x coordinate of the cruiser
        :param y: the y coordinate of the cruiser
        :return: the fire action being made if the given cruiser is adjacent of nothing otherwise
        """
        i, j = self.endeavour

        if self.check_if_adjacent(x, y, i, j):
            self._data[x][y] = None
            self.place_cruisers(self.nr_of_cruisers - 1)

    def check_if_adjacent(self, x, y, i, j):
        """
        This function checks if the given coordinated of the cruiser are adjacent to the endeavour
        :param x: the x coordinate of the endeavour
        :param y: the x coordinate of the endeavour
        :param i: the x coordinate of the cruiser
        :param j: the x coordinate of the cruiser
        :return: true if it as adjacent or false otherwise
        """

        if x == i and abs(y - j) == 1:
            return True

        if y == j and abs(x - i) == 1:
            return True

        if abs(x - i) == abs(y - j) == 1:
            return True

        return False

    def __str__(self):
        """
        The string representation of the game board
        :return:
        """
        t = Texttable()
        t.header(['0', '1', '2', '3', '4', '5', '6', '7', '8'])
        for row in range(8):
            row_data = []

            for index in self._data[row]:
                if index is None:
                    row_data.append(' ')
                elif index in ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '*']:
                    row_data.append(index)
            t.add_row(row_data)

        return t.draw()

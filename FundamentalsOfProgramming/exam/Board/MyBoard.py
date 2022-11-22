from texttable import Texttable
from random import choice, randint


class Board:
    def __init__(self, dimension, nr_of_apples):

        self._dim = dimension
        self._apples = nr_of_apples

        # Empty squares marked with None
        self._data = [[None for j in range(self._dim)] for i in range(self._dim)]

        self._snake = []

        self.place_snake()
        self.place_apples()



    @property
    def dimension(self):
        """
        Getter for the dimension
        :return:
        """
        return self._dim

    @property
    def nr_of_apples(self):
        """
        Getter for the number of apples in the game
        :return:
        """
        return self._apples

    @property
    def snake(self):
        """
        Getter for the array that represents the snake
        :return:
        """
        return self._snake

    def set_value(self, x, y, value):
        """
        This fucntion sets a value to the given field indicated by it's indices
        """
        self._data[x][y] = value

    def get(self, x, y):
        """
        Return symbol at position [x,y] on board
            None     -> empty field
            '.', '*', '+' -> apple, body, head
        """
        return self._data[x][y]

    def check_surroundings(self, x, y):
        """
        This function checks for the surroundings of a given place on the board to ensure that an apple
        can be placed on that specific spot or not
        :param x: the x coordinate
        :param y: the y coordinate
        :return: true if it can be placed or false otherwise
        """
        if x == 0:
            if y == 0:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] != '.' and \
                        self._data[x + 1][y] != '.'

            elif y == self.dimension - 1:
                return self._data[x][y] is None and \
                        self._data[x][y - 1] != '.' and \
                        self._data[x + 1][y] != '.'

            else:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] != '.' and \
                        self._data[x][y - 1] != '.' and \
                        self._data[x + 1][y] != '.'

        elif x == self.dimension - 1:
            if y == 0:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] != '.' and \
                        self._data[x - 1][y] != '.'

            elif y == self.dimension - 1:
                return self._data[x][y] is None and \
                        self._data[x][y - 1] != '.' and \
                        self._data[x - 1][y] != '.'

            else:
                return self._data[x][y] is None and \
                        self._data[x][y + 1] != '.' and \
                        self._data[x][y - 1] != '.' and \
                        self._data[x - 1][y] != '.'

        elif y == 0:
            return self._data[x][y] is None and \
                    self._data[x][y + 1] != '.' and \
                    self._data[x - 1][y] != '.' and \
                    self._data[x + 1][y] != '.'

        elif y == self.dimension - 1:
            return self._data[x][y] is None and \
                   self._data[x][y - 1] != '.' and \
                   self._data[x - 1][y] != '.' and \
                   self._data[x + 1][y] != '.'

        else:
            return self._data[x][y] is None and \
                    self._data[x][y + 1] != '.' and \
                    self._data[x][y - 1] != '.' and \
                    self._data[x - 1][y] != '.' and \
                    self._data[x + 1][y] != '.'

    def place_apples(self):
        """
        This function places randomly the apples on the board
        :return:
        """
        count = 0
        ok = False

        while not ok:
            i = randint(0, self._dim - 1)
            j = randint(0, self._dim - 1)

            if self.check_surroundings(i, j):
                self._data[i][j] = '.'
                count += 1

            if count == self.nr_of_apples:
                ok = True

    def place_snake(self):
        """
        This function places randomly the snake on the board
        :return:
        """
        if self.dimension != 3:
            starting_row = self.dimension // 3
        else:
            starting_row = self.dimension // 3 - 1

        starting_column = self.dimension // 2

        # here we add the head of the snake and it's coordinates are added to the list of indices
        self._data[starting_row][starting_column] = '*'
        self._snake.append([starting_row, starting_column])

        # here we add the body of the snake and it's coordinates are added to the list of indices
        for i in range(starting_row + 1, starting_row + 3):
            self._data[i][starting_column] = '+'
            self._snake.append([i, starting_column])

    def move_up(self, nr_moves):

        if self.snake[0][0] - nr_moves < 0:
            return False

        ok = False
        for i in range(self.snake[0][0], self.snake[0][0] - nr_moves - 1, -1):
            if self.get(i, self.snake[0][1]) == '.':
                ok = True

        i = 0
        while i <= len(self.snake) - 1:

            if i == len(self.snake) - 1 and ok:
                self.set_value(self.snake[i][0], self.snake[i][1], '+')
                self._snake[i][0] -= nr_moves
                self.set_value(self.snake[i][0], self.snake[i][1], '+')
                self._snake.append([self._snake[i][0] + nr_moves, self._snake[i][1]])
                break

            else:
                self.set_value(self.snake[i][0], self.snake[i][1], None)
                self._snake[i][0] -= nr_moves

            if i == 0:
                self.set_value(self.snake[i][0], self.snake[i][1], '*')
            else:
                self.set_value(self.snake[i][0], self.snake[i][1], '+')
            i += 1

        #place another apple when one is eaten

        i = randint(0, self._dim - 1)
        j = randint(0, self._dim - 1)
        ok = True
        while ok:
            if self.check_surroundings(i, j):
                self._data[i][j] = '.'
                ok = False

        return True

    def move_down(self, nr_moves):
        i = 0
        while i <= len(self.snake) - 1:
            self.set_value(self.snake[i][0], self.snake[i][1], None)
            self._snake[i][0] += nr_moves
            if i == 0:
                self.set_value(self.snake[i][0], self.snake[i][1], '*')
            else:
                self.set_value(self.snake[i][0], self.snake[i][1], '+')
            i += 1

    # def move_left(self, nr_moves):
    #     i = 0
    #     while i <= len(self.board.snake) - 1:
    #         self.board._snake[i][1] -= nr_moves
    #         self.board._data[i][0][]
    #         i += 1
    #
    # def move_right(self, nr_moves):
    #     i = 0
    #     while i <= len(self.board.snake) - 1:
    #         self.board._snake[i][1] += nr_moves
    #         self.board._data[i][0][]
    #         i += 1

    def change_left(self):
        self.set_value(self.snake[0][0], self.snake[0][1], None)
        self.snake[0][1] -= 1
        self.set_value(self.snake[0][0], self.snake[0][1], '*')

        i = 1
        while i <= len(self.snake) - 1:

            self.set_value(self.snake[i][0], self.snake[i][1], None)
            self._snake[i][0] -= 1

            self.set_value(self.snake[i][0], self.snake[i][1], '+')
            i += 1

    def change_right(self):
        self.set_value(self.snake[0][0], self.snake[0][1], None)
        self.snake[0][1] += 1
        self.set_value(self.snake[0][0], self.snake[0][1], '*')

        i = 1
        while i <= len(self.snake) - 1:
            self.set_value(self.snake[i][0], self.snake[i][1], None)
            self._snake[i][0] -= 1

            self.set_value(self.snake[i][0], self.snake[i][1], '+')
            i += 1

    def __str__(self):
        """
        The string representation of the game board
        :return:
        """
        t = Texttable()
        for row in range(self.dimension):
            row_data = []

            for index in self._data[row]:
                if index is None:
                    row_data.append(' ')
                elif index in ['.', '+', '*']:
                    row_data.append(index)
            t.add_row(row_data)

        return t.draw()

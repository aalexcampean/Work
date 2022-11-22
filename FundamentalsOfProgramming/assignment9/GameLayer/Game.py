import copy


class Game:
    def __init__(self, my_board, strategy):
        self._board = my_board
        self._strategy = strategy

    @property
    def board(self):
        """
        Returns the board
        :return:
        """
        return self._board

    def human_move(self, y, color):
        """
        This function makes the human move
        :param y: the y coordinate
        :param color: the color of the player
        :return: true if the game has been won of false otherwise
        """
        params = self._board.move(y, color)
        return self.check_if_game_is_won(params[0], params[1], params[2])

    def computer_move(self, color, rival_color):
        """
        This function makes the computer move
        :param y: the y coordinate
        :param color: the color of the computer player
        :param rival_color: the color of the user player
        :return: true if the game has been won of false otherwise
        """
        params = self._strategy.next_move(self._board, color, rival_color)
        return self.check_if_game_is_won(params[0], params[1], params[2])

    def check_if_game_is_won(self, x, y, color):
        """
        This function checks if the game is can be one by a given player
        :param x: the x coordinate
        :param y: the y coordinate
        :param color: the color of the given player
        :return: true if won and false if no
        """
        return self.check_row(x, color) or self.check_column(y, color) or self.check_left_diagonal(x, y, color) or \
               self.check_right_diagonal(x, y, color)

    def check_row(self, x, color):
        """
        This function checks if the game can be won on the row
        :param x: the x coordinate
        :param color: the color of the given player
        :return: true if won and false if not
        """
        count = 1
        for y in range(self.board.nr_of_columns - 1):
            if self._board.get(x, y) == color == self.board.get(x, y + 1):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1

        return False

    def check_column(self, y, color):
        """
        This function checks if the game can be won on the column
        :param y: the y coordinate
        :param color: the color of the given player
        :return: true if won and false if not
        """
        count = 1
        for x in range(self.board.nr_of_rows - 1):
            if self.board.get(x, y) == color == self.board.get(x + 1, y):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1

        return False

    def check_left_diagonal(self, x, y, color):
        """
        This function checks if the game can be won on the (secondary diagonal) of the current position
        :param x: the x coordinate
        :param y: the y coordinate
        :param color: the color of the given player
        :return: true if the game has been won of false otherwise
        """
        i = copy.deepcopy(x)
        j = copy.deepcopy(y)
        while i < 5 and j > 0:
            i += 1
            j -= 1

        count = 1
        while i > 0 and j < 6:
            if self.board.get(i, j) == color == self.board.get(i - 1, j + 1):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1
            i -= 1
            j += 1

        return False

    def check_right_diagonal(self, x, y, color):
        """
        This function checks if the game can be won on the (main diagonal) of the current position
        :param x: the x coordinate
        :param y: the y coordinate
        :param color: the color of the given player
        :return: true if the game has been won of false otherwise
        """
        i = copy.deepcopy(x)
        j = copy.deepcopy(y)
        while i < 5 and j < 6:
            i += 1
            j += 1

        count = 1
        while i > 0 and j > 0:
            if self.board.get(i, j) == color == self.board.get(i - 1, j - 1):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1
            i -= 1
            j -= 1

        return False

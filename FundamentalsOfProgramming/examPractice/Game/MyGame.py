
class Game:
    def __init__(self, my_board):
        self._board = my_board

    @property
    def board(self):
        """
        Returns the board
        :return:
        """
        return self._board

    def make_a_move(self, x, y):
        """
        This is the function that makes a move if possible otherwise raises the specific exception
        :param x: the given x coordinate
        :param y: the given y coordinate
        :return: true if the desired move is a valid one and make the move or false in case of losing
        """
        i, j = self.board.endeavour

        if (x < 0 or x > 7) and (y < 1 or y > 8):
            raise Exception('INVALID MOVE')

        if self.board.get(x, y) == '*':
            raise Exception('INVALID MOVE! CANNOT MOVE OVER STARS')

        if not self.check_move_validity(x, y, i, j):
            raise Exception('INVALID MOVE! CAN ONLY MOVE ON COLUMN, ROW OR DIAGONAL!')

        if not self.check_for_stars(x, y, i, j):
            raise Exception('INVALID MOVE! CANNOT MOVE OVER STARS')

        return self._board.move(x, y)

    def fire(self, x, y):

        if (x < 0 or x > 7) and (y < 1 or y > 8):
            raise Exception('INVALID MOVE')

        if self.board.get(x, y) != 'B':
            raise Exception('THERE IS NO CRUISER IN THAT POSITION')

        self.board.fire(x, y)

        if self.board.nr_of_cruisers == 0:
            return False
        return True

    def check_move_validity(self, x, y, i, j):
        """
        This function checks if the given coordinates make up a valid move or not
        :param x: the given x coordinate
        :param y: the given y coordinate
        :param i: the x coordinate of the current E
        :param j: the y coordinate of the current E
        :return: true if the desired move is a valid one or false otherwise
        """
        return x == i or j == y or x + y == i + j or abs(x - y) == abs(i - j)

    def check_for_stars(self, new_x, new_y, current_x, current_y):
        """
        This function calls all functions that check if the move in question is a valid move or not
        :param new_x: the given x coordinate
        :param new_y: the given y coordinate
        meaning that there are no stars blocking the move
        :param current_x: the x coordinate of the current E
        :param current_y: the y coordinate of the current E
        :return: true if the move is a valid one or false otherwise
        """
        if new_x == current_x:
            return self.check_on_row(current_x, current_y, new_y)

        if new_y == current_y:
            return self.check_on_column(current_y, current_x, new_x)

        if new_x > current_x and new_y > current_y:
            return self.check_right_diagonal(current_x, current_y, new_x, new_y)

        elif new_x < current_x and new_y < current_y:
            return self.check_right_diagonal(current_x, current_y, new_x, new_y)

        elif new_x > current_x and new_y < current_y:
            return self.check_left_diagonal(current_x, current_y, new_x, new_y)

        elif new_x < current_x and new_y > current_y:
            return self.check_left_diagonal(current_x, current_y, new_x, new_y)

    def check_on_row(self, row, current_y, new_y):
        """
        This function checks for stars on the row
        :param row: the given row
        :param current_y: the y coordinate of the current E
        :param new_y: the given y coordinate
        :return: true if there are no stars on the row or false otherwise
        """

        for j in range(min(current_y, new_y), max(current_y, new_y) + 1):
            if self.board.get(row, j) == '*':
                return False

        return True

    def check_on_column(self, column, current_x, new_x):
        """
        This function checks for stars on the column
        :param column: the given column
        :param current_x: the x coordinate of the current E
        :param new_x: the given x coordinate
        :return: true if there are no stars on the column or false otherwise
        """

        for i in range(min(current_x, new_x), max(current_x, new_x) + 1):
            if self.board.get(i, column) == '*':
                return False

        return True

    def check_left_diagonal(self, current_x, current_y, new_x, new_y):
        """
        This function checks for stars on the left diagonal
        :param current_x: the x coordinate of the current E
        :param current_y: the y coordinate of the current E
        :param new_x: the given x coordinate
        :param new_y: the given y coordinate
        :return: true if there are no stars on the left diagonal or false otherwise
        """

        first_y = min(current_y, new_y)
        if first_y == current_y:
            first_x = current_x
            second_x = new_x
            second_y = new_y

        else:
            first_x = new_x
            second_x = current_x
            second_y = current_y

        for j in range(first_y, second_y):
            for i in range(first_x, second_x, -1):
                if self.board.get(i, j) == '*':
                    return False

        return True

    def check_right_diagonal(self, current_x, current_y, new_x, new_y):
        """
        This function checks for stars on the right diagonal
        :param current_x: the x coordinate of the current E
        :param current_y: the y coordinate of the current E
        :param new_x: the given x coordinate
        :param new_y: the given y coordinate
        :return: true if there are no stars on the right diagonal or false otherwise
        """

        first_x = min(current_x, new_x)
        if first_x == current_x:
            first_y = current_y
            second_x = new_x
            second_y = new_y

        else:
            first_y = new_y
            second_x = current_x
            second_y = current_y

        for i in range(first_x, second_x):
            for j in range(first_y, second_y):
                if self.board.get(i, j) == '*':
                    return False

        return True
import copy
import random

from BoardLayer.Board import Board


class Strategy:
    """
    This is the strategy
    """

    def next_move(self, board, color, rival_color):
        """
        Return the computer's next move
        """
        # TODO Acts like an abstract base class
        raise Exception('Subclass strategy in order to implement computer play!')


class RandomMoveStrategy(Strategy):
    def next_move(self, board, color, rival_color):
        """
        This strategy enables the computer to make a random but valid move
        :param board: the board
        :param color: the color of the computer player
        :param rival_color: the color of the user player
        :return: the x, y, color and the made move
        """
        # Store possible moves here
        available_moves = []

        for col in range(board.nr_of_columns):  # 0 - 4
            move = ()
            for row in range(board.nr_of_rows):  # 0 - 3

                if board.is_free(row, col) and row == 5:
                    move = (row, col)
                    available_moves.append(move)
                elif board.is_free(row, col) and not board.is_free(row + 1, col) and row < 5:
                    move = (row, col)
                    available_moves.append(move)

        # Pick one of the available moves
        this_move = random.choice(available_moves)
        return board.move(this_move[1], color)


class SmartMoveStrategy(Strategy):
    def next_move(self, board, color, rival_color):
        """
        This strategy enables the computer to win if having the chance, to block if the user can win
        or make a random move otherwise
        :param board: the board
        :param color: the color of the computer player
        :param rival_color: the color of the user player
        :return: the x, y, color and the made move
        """

        available_moves = []

        for col in range(board.nr_of_columns):  # 0 - 4
            move = ()
            for row in range(board.nr_of_rows):  # 0 - 3

                if board.is_free(row, col) and row == 5:
                    move = (row, col)
                    available_moves.append(move)
                elif board.is_free(row, col) and not board.is_free(row + 1, col) and row < 5:
                    move = (row, col)
                    available_moves.append(move)

        win = self.move_to_win(board, color, available_moves)
        block = self.move_to_block(board, rival_color, available_moves)
        random_move = random.choice(available_moves)[1]
        if win is not None:
            return board.move(win, color)
        elif block is not None:
            return board.move(block, color)
        else:
            return board.move(random_move, color)

    def move_to_win(self, board, color, available_moves):
        """
        This functions checks for winning moves
        :param board: the board
        :param color: the color of the computer
        :param available_moves: the available moves
        :return: the column of the winning move if any or None otherwise
        """

        b = copy.deepcopy(board)
        possible_win = False
        winning_move = ()
        for m in available_moves:
            params = b.move(m[1], color)
            if self.check_if_game_is_won(params[0], params[1], params[2], b):
                possible_win = True
                winning_move = m
                break
            else:
                b.delete_move(m[0], m[1])

        if possible_win:
            return winning_move[1]
        else:
            return None

    def move_to_block(self, board, rival_color, available_moves):
        """
        This functions checks for blocking moves
        :param board: the board
        :param rival_color: the color of the player
        :param available_moves: the available moves
        :return: the column of the blocking move if any or None otherwise
        """

        b = copy.deepcopy(board)
        possible_win = False
        blocking_move = ()
        for m in available_moves:
            params = b.move(m[1], rival_color)
            if self.check_if_game_is_won(params[0], params[1], params[2], b):
                possible_win = True
                blocking_move = m
                break
            else:
                b.delete_move(m[0], m[1])

        if possible_win:
            return blocking_move[1]
        else:
            return None

    def check_if_game_is_won(self, x, y, color, board):
        """
        This function checks if the game is can be one by the computer or is used to check if the game
        can be won by the player and if so to block him
        :param x: the x coordinate
        :param y: the y coordinate
        :param color: the color of the given player
        :param board: the board
        :return: true if yes and false if no
        """
        return self.check_row(x, color, board) or \
               self.check_column(y, color, board) or \
               self.check_left_diagonal(x, y, color, board) or \
               self.check_right_diagonal(x, y, color, board)

    def check_row(self, x, color, board):
        """
        This function checks if the game can be won on the row
        :param x: the x coordinate
        :param color: the color of the given player
        :param board: the board
        :return: true if the game has been won of false otherwise
        """
        count = 1
        for y in range(board.nr_of_columns - 1):
            if board.get(x, y) == color == board.get(x, y + 1):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1

        return False

    def check_column(self, y, color, board):
        """
        This function checks if the game can be won on the column
        :param y: the y coordinate
        :param color: the color of the given player
        :param board: the board
        :return: true if the game has been won of false otherwise
        """
        count = 1
        for x in range(board.nr_of_rows - 1):
            if board.get(x, y) == color == board.get(x + 1, y):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1

        return False

    def check_left_diagonal(self, x, y, color, board):
        """
        This function checks if the game can be won on the (secondary diagonal) of the current position
        :param x: the x coordinate
        :param y: the y coordinate
        :param color: the color of the given player
        :param board: the board
        :return: true if the game has been won of false otherwise
        """
        i = copy.deepcopy(x)
        j = copy.deepcopy(y)
        while i < 5 and j > 0:
            i += 1
            j -= 1

        count = 1
        while i > 0 and j < 6:
            if board.get(i, j) == color == board.get(i - 1, j + 1):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1
            i -= 1
            j += 1

        return False

    def check_right_diagonal(self, x, y, color, board):
        """
        This function checks if the game can be won on the main diagonal
        :param x: the x coordinate
        :param y: the y coordinate
        :param color: the color of the given player
        :param board: the board
        :return: true if the game has been won of false otherwise
        """
        i = copy.deepcopy(x)
        j = copy.deepcopy(y)
        while i < 5 and j < 6:
            i += 1
            j += 1

        count = 1
        while i > 0 and j > 0:
            if board.get(i, j) == color == board.get(i - 1, j - 1):
                count += 1
                if count == 4:
                    return True
            else:
                count = 1
            i -= 1
            j -= 1

        return False


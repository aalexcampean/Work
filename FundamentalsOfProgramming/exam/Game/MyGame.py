
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

    def direction(self, dir):

        if dir == 'left':
            self.board.change_left()

        elif dir == 'right':
            self.board.change_right()

    def make_a_move(self, nr_of_moves):
        """
        This is the function that makes a move if possible otherwise raises the specific exception
        """
        if nr_of_moves == '':
            nr_moves = 1
        else:
            nr_moves = int(nr_of_moves)

        if self.check_direction() == 'up':
            return self.board.move_up(nr_moves)

        elif self.check_direction() == 'down':
            return self.board.move_down(nr_moves)

        elif self.check_direction() == 'left':
            return self.board.move_left(nr_moves)

        elif self.check_direction() == 'right':
            return self.board.move_right(nr_moves)

    def check_direction(self):
        """
        This function checks the direction which the snake is facing in
        :return:
        """
        if self.board.snake[0][0] < self.board.snake[1][0] and self.board.snake[0][1] == self.board.snake[1][1]:
            return 'up'
        elif self.board.snake[0][0] > self.board.snake[1][0] and self.board.snake[0][1] == self.board.snake[1][1]:
            return 'down'
        elif self.board.snake[0][0] == self.board.snake[1][0] and self.board.snake[0][1] < self.board.snake[1][1]:
            return 'left'
        elif self.board.snake[0][0] == self.board.snake[1][0] and self.board.snake[0][1] > self.board.snake[1][1]:
            return 'right'


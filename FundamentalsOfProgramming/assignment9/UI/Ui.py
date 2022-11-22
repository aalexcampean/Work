
class UI:
    def __init__(self, the_strategy, my_game):
        self._strategy = the_strategy
        self._game = my_game

    def read_human_move(self):
        # TODO Add error handling
        coord = input('where to play>')
        if coord.upper() not in ['A', 'B', 'C', 'D', 'E', 'F', 'G']:
            raise Exception('No such column!')
        # Calculate column index from character's ASCII code
        col = ord(coord[0].lower()) - 97
        return col

    def start(self):
        done = False
        while not done:
            try:
                human_color = input('What color do you want to be? R/Y:').upper()
                if human_color == 'R':
                    computer_color = 'Y'
                    human_turn = True
                    done = True
                elif human_color == 'Y':
                    computer_color = 'R'
                    human_turn = False
                    done = True
                else:
                    raise Exception('No such color!')

            except Exception as input_ex:
                print(str(input_ex))

        finished = False

        while not finished:

            try:

                # Print the board state
                print(self._game.board)

                if self._game.board._empty_circles == 0:
                    print('Tie!')
                    done = True
                    return

                if human_turn:
                    coord = self.read_human_move()
                    if self._game.human_move(coord, human_color):
                        print('You win!')
                        print(self._game.board)
                        finished = True
                        done = True

                else:
                    if self._game.computer_move(computer_color, human_color):
                        print('You lose!')
                        print(self._game.board)
                        finished = True
                        done = True

                human_turn = not human_turn

            except Exception as game_ex:
                print(str(game_ex))

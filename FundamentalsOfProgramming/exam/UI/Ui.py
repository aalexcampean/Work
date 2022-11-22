
class UI:
    def __init__(self, my_game):
        self._game = my_game

    def split_command(self, command):
        """
        Split - command string into command word and parameters
        :return: (command_word, command_params)
        """
        # add 10, 2000, in, Salary
        # insert / remove / list
        # command_word = add / insert / remove / list
        # command_params = 10, 2000, in, Salary
        command = command.strip()
        tokens = command.split(' ', 1)
        command_word = tokens[0].strip().lower()
        command_params = tokens[1].strip() if len(tokens) == 2 else ''

        return command_word, command_params

    def print_menu(self):
        print('\n--------------MENU--------------\n')
        print('MOVE: move <nr of move>'.ljust(50) + 'move 3 - moves 3 fields// move - moves 1 field')
        print('CHANGE DIRECTIONS: left/right/up/down'.ljust(50) + 'left - turns to left')
        print('EXIT: exit')

    def start(self):
        command_dict = {'move': self._game.make_a_move,
                        'right': self._game.direction,
                        'left': self._game.direction
                        }

        print(self._game.board)
        self.print_menu()

        done = False
        while not done:
            command = input('command> ')
            try:
                cmd_word, cmd_params = self.split_command(command)

                if cmd_word == 'move':

                    if not command_dict[cmd_word](cmd_params):
                        print('\nYOU LOST! THE SNAKE WENT OUT OF THE BOARD!')
                        done = True
                    else:
                        print(self._game.board)

                elif cmd_word == 'left':
                    command_dict[cmd_word]('left')
                    print(self._game.board)

                elif cmd_word == 'right':
                    command_dict[cmd_word]('right')
                    print(self._game.board)

                elif cmd_word == 'exit':
                    done = True

                else:
                    print('bad command')

            except Exception as ex:
                print(str(ex))
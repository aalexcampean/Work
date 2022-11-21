
class UI:
    def __init__(self, my_game):
        self._game = my_game

    def cheat(self):
        print('\nYOU CHEATER')
        print(self._game.board)

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
        print('MOVE: warp <coordinates> (warp h3)')
        print('SHOOT: fire <coordinates> (fire a1)')
        print('CHEAT: cheat')
        print('EXIT: exit')

    def start(self):
        command_dict = {'warp': self._game.make_a_move,
                        'fire': self._game.fire,
                        'cheat': self.cheat,
                        }

        print(self._game.board)
        self.print_menu()

        done = False
        while not done:
            command = input('command> ')
            try:
                cmd_word, cmd_params = self.split_command(command)

                if cmd_word in command_dict:

                    if cmd_word == 'cheat':
                        command_dict[cmd_word]()

                    else:

                        row = ord(cmd_params[0].upper()) - 65
                        column = int(cmd_params[1])
                        if not command_dict[cmd_word](row, column):
                            if cmd_word == 'warp':
                                print('YOU LOSE! YOU WERE KILLED BY A CRUISER!')
                            elif cmd_word == 'fire':
                                print('YOU WIN! YOU RULE OVER THE GALAXY!')
                            done = True
                        else:
                            print(self._game.board)

                elif cmd_word == 'exit':
                    done = True

                else:
                    print('bad command')

            except Exception as ex:
                print(str(ex))
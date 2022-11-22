import random

from Entity.Player import Player
from Service.Player_Service import PlayerService


class Ui:

    def __init__(self, player_service: PlayerService, tournament):
        self._player_service = player_service
        self._tournament_workings = tournament()

    """
    
    Play functions 
    
    """

    def play_tournament(self, players_list):
        """
        This function is the one that keeps the tournament going, announces the last players, who won and who is in the qualifying round if any
        :param players_list: the initial list of players
        :return:
        """
        done = False
        while not done:

            if len(players_list) == 1:
                done = True
                print(f'\nTHIS TOURNAMENTS WINNER IS {str(players_list[0])} !!!')

            elif not(len(players_list) & (len(players_list) - 1)):

                while len(players_list) != 1:

                    if len(players_list) == 2:
                        print('\nLAST 2')
                        print('\n')
                        for p in players_list:
                            print(str(p))

                    elif len(players_list) == 4:
                        print('\nLAST 4')
                        print('\n')
                        for p in players_list:
                            print(str(p))

                    elif len(players_list) == 8:
                        print('\nLAST 8')
                        print('\n')
                        for p in players_list:
                            print(str(p))

                    elif len(players_list) == 16:
                        print('\nLAST 16')
                        print('\n')
                        for p in players_list:
                            print(str(p))

                    players_list = self.play_match(players_list).copy()

                    self._player_service.set_players_list(players_list)

            else:

                print('\nQUALIFYING ROUND')

                list_of_players_in_the_qualifying_round = self._tournament_workings.find_the_list_of_players_of_the_qualifying_round(players_list)

                print('\nTHE PLAYERS THAT PLAY IN THE QUALIFYING ROUND')
                print('\n')
                for p in list_of_players_in_the_qualifying_round:
                    print(str(p))

                for p1 in list_of_players_in_the_qualifying_round:
                    for p2 in players_list:
                        if p1.id == p2.id:
                            players_list.remove(p2)

                list_of_players_that_move_on = self.play_match(list_of_players_in_the_qualifying_round).copy()

                players_list += list_of_players_that_move_on

                print('\nTHE PLAYERS THAT GO INTO THE TOURNAMENT')
                print('\n')
                for p in players_list:
                    print(str(p))

    def play_match(self, list_of_players):
        """
        This function is the one that keeps the matches going. On each step there are a number of matches that need
        to be played in order for the tournament to work properly
        :param list_of_players: the list of players at this stage
        :return: the list of winning players of these matches
        """
        list_of_winning_players_this_round = []

        while len(list_of_players) != 0:
            player1, player2 = self._tournament_workings.pick_random(list_of_players)
            print('\n')
            print(f'Player 1: {player1}\n')
            print(f'Player 2: {player2}\n')
            p = input('Enter the wining player: ')

            if p == 'player1':

                id_here = player1.id
                name_here = player1.name
                strength_here = player1.playing_strength + 1

                list_of_winning_players_this_round.append(Player(id_here, name_here, strength_here))
                print(f'\nThis match was won by {str(player1)}')

            elif p == 'player2':

                id_here = player2.id
                name_here = player2.name
                strength_here = player2.playing_strength + 1

                list_of_winning_players_this_round.append(Player(id_here, name_here, strength_here))
                print(f'\nThis match was won by {str(player2)}')

        return list_of_winning_players_this_round

    """
    
    Display Functions
    
    """

    def display_all_players(self):
        """
        This function displays the the initila list of players in descending order based on their strength
        :return:
        """
        self._player_service.players.sort(key=lambda i: i.playing_strength, reverse=True)
        print('\n')
        if len(self._player_service) == 0:
            print('!!! There are no players !!!')
        else:
            print('Players:\n')
            for p in self._player_service.players:
                print(str(p))

    """

    Menu

    """

    def print_start(self):
        """
        The function that prints the menu
        :return:
        """
        print('\n')
        print('1: Display Players')
        print('2: Start Game')
        print('0: Exit')

    """

    Start

    """

    def start_ui(self):

        done = False
        while not done:

            self.print_start()
            x = input('Enter a command: ')

            try:
                if x == '1':
                    self.display_all_players()

                elif x == '2':

                    self.play_tournament(self._player_service.players)
                    done = True

                elif x == '0':
                    done = True
                    print('See you later :*')

                else:
                    print('??? Oh my god, what is that ???')

            except Exception as ex:
                print('\n' + str(ex))





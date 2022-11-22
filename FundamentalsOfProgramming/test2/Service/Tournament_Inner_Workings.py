import random


class TournamentWorkings:

    def find_closest_power_of_2(self, number):
        """
        This function finds the closest power of two smaller than the given number
        :param number: th number in question
        :return:
        """

        var1 = number - 1
        while var1 >= 2:
            if not(var1 & var1 - 1):
                return var1
            else:
                var1 -= 1

    def find_the_list_of_players_of_the_qualifying_round(self, list_of_players):
        """
        This function finds the plyers that will play in the qualifying round
        :param list_of_players: the initial list of players
        :return:
        """

        n = len(list_of_players) - self.find_closest_power_of_2(len(list_of_players))

        list_of_players_with_lowest_strength = list_of_players.copy()
        list_of_players_with_lowest_strength.sort(key=lambda i: i.playing_strength, reverse=False)

        index = 2 * n
        while index <= len(list_of_players_with_lowest_strength) - 1:
            list_of_players_with_lowest_strength.pop(index)

        return list_of_players_with_lowest_strength

    def pick_random(self, list_of_players):
        """
        This function picks 2 random players from a given list so that they can compete in the tournament
        :param list_of_players: the list of players in question
        :return: the 2 players
        """

        player1 = random.choice(list_of_players)
        list_of_players.remove(player1)

        player2 = random.choice(list_of_players)
        list_of_players.remove(player2)

        return player1, player2
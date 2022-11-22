from Entity.Player import Player, PlayerException


class PlayerRepositoryException(PlayerException):

    def __init__(self, msg):
        self._msg = msg


class PlayerRepository:

    def __init__(self, players_list):
        self._players = players_list

    @property
    def players(self):
        """
        list getter
        :return: the list of players
        """

        return self._players

    def set_players_list(self, new_list):
        """
        This is a setter so that the list of players that are still in the tournament can be updated
        :param new_list: the new lst of players
        :return:
        """

        self._players = new_list

    def delete_player(self, player_id):
        """
        This function deletes a client from the list of clients by searching the book by its id
        :param player_id: the id in question
        :return:
        """

        p = 0
        while p <= len(self._players) - 1:
            if self._players[p].id == player_id:
                del self._players[p]
            else:
                p += 1

    def update_player(self, player: Player):
        """
        This function updates the contents of a player besides its id
        :param player: the player in question
        :return:
        """

        p = 0
        while p <= len(self._players) - 1:
            if self._players[p].id == player.id:
                self._players[p] = player
            p += 1

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._players)

import copy
import random

from Entity.Player import Player
from Repository.Player_Repo import PlayerRepository


class PlayerService:
    """
    Class implements service-level functionalities for Client entity
    It requires a Client repository to work with
    """

    def __init__(self, players_repo: PlayerRepository):
        self._repo = players_repo

    @property
    def players(self):
        """
        list getter
        :return: the list of clients from the repo
        """

        return self._repo.players

    def set_players_list(self, new_list):
        """
        This is a setter so that the list of players that are still in the tournament can be updated
        :param new_list: the new lst of players
        :return:
        """

        self._repo.set_players_list(new_list)

    def delete(self, player_id):
        """
        This function calls the delete function from the repo, the function is added as a redo,
        and its inverse (add) as an undo in the operations history
        when deleting a client all rentals referencing that client, are deleted as well
        :param player_id: the id of the client in question
        :return:
        """

        self._repo.delete_player(player_id)

    def update(self, player: Player):
        """
        This function validates a given client and if it passes, the undo function from the repo is called
        the function is added as a redo with the given client, and its inverse (update with the old client)
        as an undo in the operations history
        :param player: the book in question
        :return:
        """

        self._repo.update_player(player)

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._repo)

class PlayerException(Exception):
    def __init__(self, msg):
        self._msg = msg


class Player:

    def __init__(self, player_id, player_name, playing_strength):

        if not isinstance(player_id, int):
            raise PlayerException('!!! Invalid id !!!')
        if not isinstance(player_name, str):
            raise PlayerException('!!! Invalid player name !!!')
        if not isinstance(playing_strength, int):
            raise PlayerException('!!! Invalid playing strength !!!')

        self._id = player_id
        self._name = self.split_name(player_name)
        self._strength = playing_strength

    def split_name(self, name):
        """
        This function splits the names, capitalizing the first letter of every name
        :param name: the name in question
        :return:
        """

        names = name.strip().split(' ')
        new_client_name = ''
        for n in range(len(names)):
            if names[n] != '':
                new_client_name += names[n].strip().capitalize() + ' '
        return new_client_name.strip()

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def playing_strength(self):
        return self._strength

    def __str__(self):
        """
        The string representation of a client object
        :return:
        """

        return f'Player Id: {self.id: <8} Player Name: {self.name: <15} Player Strength: {self.playing_strength}'
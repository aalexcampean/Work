from Entity.Client import Client, ClientException


class ClientRepositoryException(ClientException):

    def __init__(self, msg):
        self._msg = msg


class ClientRepository:

    # def __init__(self, client_list):
    #     self._clients = client_list.copy()

    def __init__(self, client_list):
        self._clients = client_list

    @property
    def clients(self):
        """
        list getter
        :return: the list of clients
        """

        return self._clients

    def find(self, client_id):
        """
        This function finds a client by its id and returns it or returns none otherwise
        :param client_id: the id of the client
        :return:
        """

        for c in self._clients:
            if client_id == c.id:
                return c
        return None

    def add_client(self, client: Client):
        """
        This function adds a client to the list of clients and raises an exception if the id is already in the list
        :param client: the client in question
        :return:
        """

        c = self.find(client.id)

        if c is not None:
            raise ClientRepositoryException('!!! Duplicate id !!!')

        self._clients.append(client)

    def delete_client(self, just_id):
        """
        This function deletes a client from the list of clients by searching the book by its id
        :param just_id: the id in question
        :return:
        """

        client_object = self.find(just_id)

        if client_object is None:
            raise ClientRepositoryException('!!! There is no client with this id !!!')

        c = 0
        while c <= len(self._clients) - 1:
            if self._clients[c].id == just_id:
                self._clients.pop(c)
            else:
                c += 1

        return client_object

    def update_client(self, client: Client):
        """
        This function updates the contents of a client besides its id
        :param client: the client in question
        :return:
        """

        client_object = self.find(client.id)

        if client_object is None:
            raise ClientRepositoryException('!!! There is no client with this id !!!')

        for c in self._clients:
            if c.id == client.id:
                c._name = client.name

    def search(self, text, results_list):
        """
        This function searches for books by a given string. This string can be anywhere (id, name)
        :param text: the text which the clients are searched by
        :param results_list: the list of results
        :return:
        """

        for c in self._clients:
            if text.casefold() in str(c.id).casefold() or text.casefold() in c.name.casefold():
                results_list.append(c)

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._clients)

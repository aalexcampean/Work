import copy

from Repository.Client_Repo import ClientRepository
from Entity.Client import ClientValidator, Client
from Service.UndoService import UndoService, FunctionCall, Operation, CascadedOperation
from Service.Rental_Service import RentalService


class ClientService:
    """
    Class implements service-level functionalities for Client entity
    It requires a Client repository to work with
    """

    def __init__(self, client_repo: ClientRepository, validator: ClientValidator, rental_service: RentalService, undo_service: UndoService):
        self._repo = client_repo
        self._validator = validator
        self._rental_service = rental_service
        self._undo_service = undo_service

    @property
    def clients(self):
        """
        list getter
        :return: the list of clients from the repo
        """

        return self._repo.clients

    def add(self, client: Client):
        """
        This function validates a given client and if it passes, the add function from the repo is called
        while at the same time, the function is added as a redo, and its inverse (delete) as an undo in the
        operations history
        :param client: the client in question
        :return:
        """

        self._validator.is_client_valid(client)

        self._repo.add_client(client)

        undo = FunctionCall(self._repo.delete_client, client.id)
        redo = FunctionCall(self._repo.add_client, client)
        self._undo_service.record(Operation(undo, redo))

    def delete(self, client_id):
        """
        This function calls the delete function from the repo, the function is added as a redo,
        and its inverse (add) as an undo in the operations history
        when deleting a client all rentals referencing that client, are deleted as well
        :param client_id: the id of the client in question
        :return:
        """

        client = self._repo.delete_client(client_id)
        deleted_list = self._rental_service.delete_rental_by_client(client_id)

        undo_client = FunctionCall(self._repo.add_client, client)
        redo_client = FunctionCall(self._repo.delete_client, client.id)
        operation_client = Operation(undo_client, redo_client)

        undo_rentals = FunctionCall(self._rental_service.add_rentals, deleted_list)
        redo_rentals = FunctionCall(self._rental_service.delete_rental_by_client, client_id)
        operation_rentals = Operation(undo_rentals, redo_rentals)

        self._undo_service.record(CascadedOperation(operation_client, operation_rentals))

    def update(self, client: Client):
        """
        This function validates a given client and if it passes, the undo function from the repo is called
        the function is added as a redo with the given client, and its inverse (update with the old client)
        as an undo in the operations history
        :param client: the book in question
        :return:
        """
        self._validator.is_client_valid(client)
        old_client = copy.deepcopy(self._repo.find(client.id))
        new_client = client

        self._repo.update_client(client)

        undo = FunctionCall(self._repo.update_client, old_client)
        redo = FunctionCall(self._repo.update_client, new_client)
        self._undo_service.record(Operation(undo, redo))

    def search(self, text):
        """
        This function searches for clients by a given string. This string can be anywhere (id, name)
        :param text: the text which the clients are searched by
        :return: the list with the results
        """

        results_list = []
        self._repo.search(text, results_list)
        return results_list

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._repo)

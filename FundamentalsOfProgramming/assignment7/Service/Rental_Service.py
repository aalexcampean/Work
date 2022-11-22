import copy

from Repository.Book_Repo import BookRepository, BookRepositoryException
from Repository.Client_Repo import ClientRepository, ClientRepositoryException
from Repository.Rental_Repo import RentalRepository, RentalRepositoryException
from Entity.Rental import Rental, RentalValidator
from Service.UndoService import UndoService, FunctionCall, Operation


class RentalService:
    """
    Class that implements functionalities for Rental entity
    It requires a Rental repository to work with
    """

    def __init__(self, rental_repo: RentalRepository, client_repo: ClientRepository, book_repo: BookRepository, validator: RentalValidator, undo_service: UndoService):
        self._rental_repo = rental_repo
        self._client_repo = client_repo
        self._book_repo = book_repo
        self._validator = validator
        self._undo_service = undo_service

    @property
    def rentals(self):
        """
        list getter
        :return: the list of rentals from the repo
        """

        return self._rental_repo.rentals

    def delete_rental_by_client(self, id_client):
        """
        This function deleted all rentals referencing the given client_id
        :param id_client: the given client_id
        :return:
        """

        return self._rental_repo.delete_rental_by_client(id_client)

    def delete_rental_by_book(self, id_book):
        """
        This function deleted all rentals referencing the given book_id
        :param id_book: the given book_id
        :return:
        """

        return self._rental_repo.delete_rental_by_book(id_book)

    def add_rentals(self, rental_list):
        """
        this function adds a list of rentals to the existing one
        :param rental_list:
        :return:
        """

        self._rental_repo.add(rental_list)

    def rent(self, rental: Rental):
        """
        This function validates a given rental, checks if the client id and book id are valid and if it passes
        the new rental is added to the list with the return date = None
        The function is added as a redo(with the parameter = the given rental),
        and its inverse (delete with the parameter = the given rental_id) as an undo in the operations history
        :param rental: the rental in question
        :return:
        """

        client_object = self._client_repo.find(rental.client_id)
        if client_object is None:
            raise ClientRepositoryException('!!! This client does not exist !!!')

        book_object = self._book_repo.find(rental.client_id)
        if book_object is None:
            raise BookRepositoryException('!!! This book does not exist !!!')

        self._validator.is_rental_valid(rental)

        self.check_book_availability(rental.book_id)

        self._rental_repo.rent(rental)

        undo = FunctionCall(self._rental_repo.delete, rental.rental_id)
        redo = FunctionCall(self._rental_repo.rent, rental)
        self._undo_service.record(Operation(undo, redo))

    def check_book_availability(self, book_id_here):
        """
        This function checks if a book is rented right now or not
        :param book_id_here: the id of the book in question
        :return: and exception if the book is not available
        """

        for r in self._rental_repo.rentals:
            if r.book_id == book_id_here:
                if r.returned_date is None:
                    raise RentalRepositoryException('!!! This book is already rented !!!')

    def turn_in(self, rental_id, returned_date):
        """
        This function calls the function from the repo that checks if the rental exists and if so it
        assigns the given returned date to the previously none date
        The function update is called to be the redo (with the parameter = the new rental),
        and as an undo is the update function (with the parameter = the old rental) in the operations history
        :param rental_id: the id of the rental
        :param returned_date: the return date
        :return:
        """

        old_rental = copy.deepcopy(self._rental_repo.find(rental_id))

        self._rental_repo.turn_in(rental_id, returned_date)

        new_rental = copy.deepcopy(self._rental_repo.find(rental_id))

        undo = FunctionCall(self._rental_repo.update_rental, old_rental)
        redo = FunctionCall(self._rental_repo.update_rental, new_rental)
        self._undo_service.record(Operation(undo, redo))

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._rental_repo)



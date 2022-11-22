import copy

from Repository.Book_Repo import BookRepository
from Entity.Book import Book, BookValidator
from Service.UndoService import UndoService, FunctionCall, Operation, CascadedOperation
from Service.Rental_Service import RentalService


class BookService:
    """
    Class implements service-level functionalities for Book entity
    It requires a Book repository to work with
    """

    def __init__(self, book_repo: BookRepository, validator: BookValidator, rental_service: RentalService, undo_service: UndoService):

        self._repo = book_repo
        self._validator = validator
        self._rental_service = rental_service
        self._undo_service = undo_service

    @property
    def books(self):
        """
        list getter
        :return: the list of books from the repo
        """

        return self._repo.books

    def add(self, book: Book):
        """
        This function validates a given book and if it passes, the add function from the repo is called
        while at the same time, the function is added as a redo, and its inverse (delete) as an undo in the
        operations history
        :param book: the book in question
        :return:
        """

        self._validator.is_book_valid(book)

        self._repo.add_book(book)

        undo = FunctionCall(self._repo.delete_book, book.id)
        redo = FunctionCall(self._repo.add_book, book)
        self._undo_service.record(Operation(undo, redo))

    def delete(self, book_id):
        """
        This function calls the delete function from the repo, the function is added as a redo,
        and its inverse (add) as an undo in the operations history
        when deleting a book all rentals referencing that book, are deleted as well
        :param book_id: the id of the client in question
        :return:
        """

        book = self._repo.delete_book(book_id)
        deleted_list = self._rental_service.delete_rental_by_book(book_id)

        undo_book = FunctionCall(self._repo.add_book, book)
        redo_book = FunctionCall(self._repo.delete_book, book.id)
        operation_book = Operation(undo_book, redo_book)

        undo_rentals = FunctionCall(self._rental_service.add_rentals, deleted_list)
        redo_rentals = FunctionCall(self._rental_service.delete_rental_by_book, book.id)
        operation_rentals = Operation(undo_rentals, redo_rentals)

        self._undo_service.record(CascadedOperation(operation_book, operation_rentals))

    def update(self, book: Book):
        """
        This function validates a given book and if it passes, the undo function from the repo is called
        the function is added as a redo with the given client, and its inverse (update with the old client)
        as an undo in the operations history
        :param book: the book in question
        :return:
        """

        self._validator.is_book_valid(book)

        old_book = copy.deepcopy(self._repo.find(book.id))
        new_book = book

        self._repo.update_book(book)

        undo = FunctionCall(self._repo.update_book, old_book)
        redo = FunctionCall(self._repo.update_book, new_book)
        self._undo_service.record(Operation(undo, redo))

    def search(self, text):
        """
        This function searches for books by a given string. This string can be anywhere (id, title, author)
        :param text: the text which the books are searched by
        :return: the list of results
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


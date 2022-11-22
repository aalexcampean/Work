from DataStructure.Data_Structure import DataStructure
from Entity.Book import Book, BookException


class BookRepositoryException(BookException):

    def __init__(self, msg):
        self._msg = msg


class BookRepository:

    def __init__(self, book_list):
        self._books = DataStructure()

        for b in book_list:
            self._books.add(b)

    @property
    def books(self):
        """
        list getter
        :return: the list of books
        """

        return self._books

    def find(self, book_id):
        """
        This function finds a book by its id and returns it or returns none otherwise
        :param book_id: the id of the book
        :return:
        """

        for b in self._books:
            if book_id == b.id:
                return b

        return None

    def add_book(self, book: Book):
        """
        This function adds a book to the list of books and raises an exception if the id is already in the list
        :param book: the book in question
        :return:
        """

        b = self.find(book.id)

        if b is not None:
            raise BookRepositoryException('!!! Duplicate id !!!')

        self._books.add(book)

    def delete_book(self, just_id):
        """
        This function deletes a book from the list of books by searching the book by its id
        :param just_id: the id in question
        :return:
        """

        book_object = self.find(just_id)

        if book_object is None:
            raise BookRepositoryException('!!! There is no book with this id !!!')

        b = 0
        while b <= len(self._books) - 1:
            if self._books[b].id == just_id:
                del self._books[b]

            else:
                b += 1

        return book_object

    def update_book(self, book: Book):
        """
        This function updates the contents of a book besides its id
        :param book: the book in question
        :return:
        """

        book_object = self.find(book.id)

        if book_object is None:
            raise BookRepositoryException('!!! There is no book with this id !!!')

        b = 0
        while b <= len(self._books) - 1:
            if self._books[b].id == book.id:
                self._books[b] = book
            b += 1

    def search(self, text, results_list):
        """
        This function searches for books by a given string. This string can be anywhere (id, title, author)
        :param text: the text which the books are searched by
        :param results_list: the list of results
        :return:
        """

        for b in self._books:
            if text.casefold() in str(b.id).casefold() or text.casefold() in b.title.casefold() or text.casefold() in b.author.casefold():
                results_list.append(b)

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._books)

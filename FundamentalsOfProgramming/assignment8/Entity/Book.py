
class BookException(Exception):
    def __init__(self, msg):
        self._msg = msg


class BookValidationException(BookException):
    def __init__(self, error_list):
        self._errors = error_list

    def __str__(self):
        """
        the string representation of the list of exceptions raised in the validator
        :return:
        """

        result = ''

        for er in self._errors:
            result += er
            result += '\n'
        return result


class BookValidator:

    @staticmethod
    def is_id_valid(book_id):
        return isinstance(book_id, int) and book_id > 0

    @staticmethod
    def is_title_valid(book_title):
        return isinstance(book_title, str)

    @staticmethod
    def is_author_valid(book_author):
        return isinstance(book_author, str)

    def is_book_valid(self, book):
        """
        This functions calls all the static methods and checks if a book is valid or not, raising the afferent
        exceptions
        :param book: the book in question
        :return:
        """

        errors = []
        if not self.is_id_valid(book.id):
            errors.append('!!! Invalid book id !!!')
        if not self.is_title_valid(book.title):
            errors.append('!!! Invalid book title !!!')
        if not self.is_author_valid(book.author):
            errors.append('!!! Invalid book author !!!')

        if len(errors) > 0:
            raise BookValidationException(errors)


class Book:

    def __init__(self, book_id, book_title, book_author):

        if not isinstance(book_id, int):
            raise BookException('!!! Invalid id !!!')
        if not isinstance(book_title, str):
            raise BookException('!!! Invalid book title !!!')
        if not isinstance(book_author, str):
            raise BookException('!!! Invalid book author !!!')

        self._id = book_id
        self._title = self.split_name(book_title)
        self._author = self.split_name(book_author)

    def split_name(self, name):
        """
        This function splits the names, capitalizing the first letter of every name
        :param name: the name in question
        :return:
        """

        names = name.strip().split(' ')
        new_book_name = ''
        for n in range(0, len(names)):
            if names[n] != '':
                new_book_name += names[n].strip().capitalize() + ' '
        return new_book_name.strip()

    @property
    def id(self):
        return self._id

    @property
    def title(self):
        return self._title

    @property
    def author(self):
        return self._author

    def __str__(self):
        """
        The string representation of a book object
        :return:
        """

        # return str('Id: ' + str(self._id).ljust(5) + 'Title: ' + self._title.ljust(35) + 'Author: ' + self._author)
        return f'Id: {self.id: <5} Title: {self.title: <35} Author: {self.author}'

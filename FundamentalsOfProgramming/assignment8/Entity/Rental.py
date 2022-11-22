import datetime


class RentalException(Exception):

    def __init__(self, msg):
        self._msg = msg


class RentalValidationException(RentalException):
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


class RentalValidator:

    @staticmethod
    def is_rental_id_valid(rental_id):
        return isinstance(rental_id, int) and rental_id > 0

    @staticmethod
    def is_client_id_valid(client_id):
        return isinstance(client_id, int) and client_id > 0

    @staticmethod
    def is_book_id_valid(book_id):
        return isinstance(book_id, int) and book_id > 0

    @staticmethod
    def are_dates_valid(date):
        return len(str(date)) == 10 and str(date)[0] != '0' and str(date)[4] == '-' and str(date)[7] == '-' \
               and str(date)[5:7] != '00' and str(date)[8:] != '00' and str(date)[0:4] != '0000'

    def is_rental_valid(self, rental):
        """
        This functions calls all the static methods and checks if a rental is valid or not, raising the afferent
        exceptions
        :param rental: the rental in question
        :return:
        """

        errors = []
        if not self.is_rental_id_valid(rental.rental_id):
            errors.append('!!! Invalid book id !!!')
        if not self.is_client_id_valid(rental.client_id):
            errors.append('!!! Invalid book title !!!')
        if not self.is_book_id_valid(rental.book_id):
            errors.append('!!! Invalid book author !!!')
        if not self.are_dates_valid(rental.rented_date):
            errors.append('!!! Invalid rented date !!!')
        if rental.returned_date is not None:
            if not self.are_dates_valid(rental.returned_date):
                errors.append('!!! Invalid returned date !!!')

        if len(errors) > 0:
            raise RentalValidationException(errors)


class Rental:

    def __init__(self, rental_id, client_id, book_id, rented_date, returned_date):

        if not isinstance(rental_id, int):
            raise RentalException('!!! Invalid rental id !!!')
        if not isinstance(client_id, int):
            raise RentalException('!!! Invalid client id !!!')
        if not isinstance(book_id, int):
            raise RentalException('!!! Invalid book id !!!')

        if returned_date == 'None\n':
            returned_date = None

        if returned_date is not None:
            rented = self.date_split(rented_date)
            returned = self.date_split(returned_date)
            if rented > returned:
                raise RentalException('!!! Invalid rented / returned dates !!!')

        else:
            rented = self.date_split(rented_date)
            returned = None

        self._id = rental_id
        self._book_id = book_id
        self._client_id = client_id
        self._rented_date = rented
        self._returned_date = returned

    def date_split(self, date: str):
        """
        This funtion splits the given str date so that it can be transformed into to datetime class type object
        :param date: the date in question
        :return:
        """

        tokens = date.split('-')
        if len(tokens) != 3:
            raise RentalException('!!! Invalid date !!!')

        self.date_validator(tokens[0], tokens[1], tokens[2])

        year = int(tokens[0])

        if tokens[1][0] == '0':
            tokens[1].replace('0', '', 1)
        month = int(tokens[1])

        if tokens[2][0] == '0':
            tokens[2].replace('0', '', 1)
        day = int(tokens[2])

        return datetime.date(year, month, day)

    def date_validator(self, year, month, day):
        """
        This function validates the given date
        :param year: the year
        :param month: the month
        :param day: the day
        :return: an exception if it is not correct and nothing otherwise
        """

        if len(year) != 4 and len(month) != 2 and len(day) != 2:
            raise RentalException('!!! Invalid date !!!')

        if year[0] == '0' and year[0] == '0000' and month == '00' and day == '00':
            raise RentalException('!!! Invalid date !!!')

    @property
    def rental_id(self):
        return self._id

    @property
    def client_id(self):
        return self._client_id

    @property
    def book_id(self):
        return self._book_id

    @property
    def rented_date(self):
        return self._rented_date

    @property
    def returned_date(self):
        return self._returned_date

    def __str__(self):
        """
        The string representation of a rental object
        :return:
        """

        # return 'rental id: ' + str(self._id).ljust(5) \
        #        + 'client id: ' + str(self._client_id).ljust(5) \
        #        + 'book id: ' + str(self._book_id).ljust(5) \
        #        + 'rented date: ' + str(self._rented_date).ljust(15) \
        #        + 'returned date: ' + str(self._returned_date)

        return f'Rental id: {self.rental_id: <5}' \
               f' Client id: {self.client_id: <5}' \
               f'Book id: {self.book_id: <5}' \
               f'Rented date: {str(self.rented_date): <15}' \
               f'Returned date: {str(self.returned_date)}'




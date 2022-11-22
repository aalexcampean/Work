import datetime

from DataStructure.Data_Structure import DataStructure
from Entity.Rental import Rental, RentalException
import copy


class RentalRepositoryException(RentalException):

    def __init__(self, msg):
        self._msg = msg


class RentalRepository:

    def __init__(self, rentals_list):
        self._rentals = DataStructure()

        for r in rentals_list:
            self._rentals.add(r)

    @property
    def rentals(self):
        """
        list getter
        :return: the list of rentals
        """

        return self._rentals

    def find(self, rental_id):
        """
        This function finds a rental by its id and returns it or returns none otherwise
        :param rental_id: the id of the rental
        :return:
        """

        for r in self._rentals:
            if rental_id == r.rental_id:
                return r

        return None

    def add(self, rental_list):
        """
        This function adds a list of rentals to the existing one
        :param rental_list: the list of rentals
        :return:
        """

        for r in rental_list:
            self._rentals.add(r)

    def rent(self, rental: Rental):
        """
        This function gets a new rental, checks if its id is unique raising an exception if not so,
        and adds it to the list otherwise
        :param rental: the rental in question
        :return:
        """

        rental_object = self.find(rental.rental_id)

        if rental_object is not None:
            raise RentalRepositoryException('!!! Duplicate id !!!')

        self._rentals.add(rental)

    def turn_in(self, id_here, returned_date):
        """
        This function sets the date of a rented date to a given one, meaning it is returned and raised exceptions if
        if the rental does not exist or if the given date is incorrect
        :param id_here:
        :param returned_date:
        :return:
        """

        rental_object = self.find(id_here)

        if rental_object is None:
            raise RentalRepositoryException('!!! This rental does not exist !!!')

        formatted_date = self.transform_date(returned_date)

        new_rental_object = copy.deepcopy(rental_object)
        new_rental_object._returned_date = formatted_date

        r = 0
        while r <= len(self._rentals) - 1:
            if self._rentals[r].rental_id == id_here:
                if self._rentals[r].returned_date is None and self._rentals[r].rented_date < formatted_date:
                    self._rentals[r] = new_rental_object
                else:
                    raise RentalRepositoryException('!!! The returned date is incorrect !!!')
            r += 1

    def delete_rental_by_client(self, client_id):
        """
        This function deletes all rentals that reference the given client id
        :param client_id: the given client id
        :return: the list of deleted rentals
        """

        deleted_list = []

        r = 0
        while r <= len(self._rentals) - 1:
            if self._rentals[r].client_id == client_id:
                deleted_list.append(self._rentals[r])
                del self._rentals[r]
            else:
                r += 1

        return deleted_list

    def delete_rental_by_book(self, book_id):
        """
        This function deletes all rentals that reference the given book id
        :param book_id: the given book id
        :return: the list of deleted rentals
        """

        deleted_list = []

        r = 0
        while r <= len(self._rentals) - 1:
            if self._rentals[r].book_id == book_id:
                deleted_list.append(self._rentals[r])
                del self._rentals[r]
            else:
                r += 1

        return deleted_list

    def delete(self, rental_id):
        """
        This functions deletes the rental with the given rental_id
        :param rental_id: the given rental_id
        :return:
        """

        r = 0
        while r <= len(self._rentals) - 1:
            if self._rentals[r].rental_id == rental_id:
                del self._rentals[r]
            else:
                r += 1

    def update_rental(self, rental):
        """
        This function updates a rental by finding it's id in the rentals lst and changing all it's other
        components
        :param rental: the given rental
        :return:
        """

        r = 0
        while r <= len(self._rentals) - 1:
            if self._rentals[r].rental_id == rental.rental_id:
                self._rentals[r] = rental
            r += 1

    def transform_date(self, date_here):
        """
        This fucntion transforms a given date from a string to a datetime object
        :param date_here: the date in question
        :return: the newly created date object
        """

        tokens = date_here.split('-')
        if len(tokens) == 0:
            raise RentalRepositoryException('!!! Invalid date !!!')

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
            raise RentalRepositoryException('!!! Invalid date !!!')

        if year[0] == '0' and year[0] == '0000' and month == '00' and day == '00':
            raise RentalRepositoryException('!!! Invalid date !!!')

    def __len__(self):
        """
        the len method for this class
        :return:
        """

        return len(self._rentals)


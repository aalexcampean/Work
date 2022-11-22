import unittest
import datetime

from Entity.Client import Client
from Entity.Book import Book
from Entity.Rental import Rental

from Repository.Client_Repo import ClientRepository
from Repository.Book_Repo import BookRepository
from Repository.Rental_Repo import RentalRepository


class ClientRepoTest(unittest.TestCase):

    def test_ClientRepo(self):

        list_clients = []
        repo = ClientRepository(list_clients)
        self.assertEqual(len(repo), 0)

        # add functionality

        repo.add_client(Client(1, 'alexandra gog andreea'))
        self.assertEqual(len(repo), 1)
        repo.add_client(Client(2, 'campean catalin alexandru'))
        self.assertEqual(len(repo), 2)

        # delete functionality

        repo.delete_client(1)
        self.assertEqual(len(repo), 1)

        # update functionality

        repo.update_client(Client(2, 'campean catalin'))
        self.assertEqual(repo.clients[0].name, 'Campean Catalin')


class BookRepoTest(unittest.TestCase):

    def test_BookRepo(self):

        list_books = []
        repo = BookRepository(list_books)
        self.assertEqual(len(repo), 0)

        # add functionality

        repo.add_book(Book(1, 'Catch 22', 'Joseph Heller'))
        self.assertEqual(len(repo), 1)
        repo.add_book(Book(2, 'Ulysses', 'James Joyce'))
        self.assertEqual(len(repo), 2)

        # delete functionality

        repo.delete_book(1)
        self.assertEqual(len(repo), 1)

        # update functionality

        repo.update_book(Book(2, 'Ulysses', 'James Joyce the 3rd'))
        self.assertEqual(repo.books[0].author, 'James Joyce The 3rd')


class RentalRepoTest(unittest.TestCase):

    def test_RentalRepo(self):

        list_rentals = []
        repo = RentalRepository(list_rentals)
        self.assertEqual(len(repo), 0)

        # rent functionality

        repo.rent(Rental(1, 2, 3, '2020-11-12', None))
        self.assertEqual(len(repo), 1)
        repo.rent(Rental(2, 3, 4, '2020-11-12', None))
        self.assertEqual(len(repo), 2)

        # turn in functionality

        repo.turn_in(1, '2020-11-20')
        self.assertEqual(repo.rentals[0].returned_date, datetime.date(2020, 11, 20))









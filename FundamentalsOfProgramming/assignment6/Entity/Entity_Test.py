import unittest
import datetime
from Entity.Client import Client
from Entity.Book import Book
from Entity.Rental import Rental


class ClientTest(unittest.TestCase):

    def test_Client(self):

        c = Client(1, 'alexandra gog andreea')
        self.assertEqual(c.id, 1)
        self.assertEqual(c.name, 'Alexandra Gog Andreea')


class BookTest(unittest.TestCase):

    def test_Book(self):

        b = Book(1, 'Catch 22', 'Joseph Heller')
        self.assertEqual(b.id, 1)
        self.assertEqual(b.title, 'Catch 22')
        self.assertEqual(b.author, 'Joseph Heller')


class RentalTest(unittest.TestCase):

    def test_Rental(self):

        r = Rental(1, 3, 2, '2020-11-12', '2020-11-20')
        self.assertEqual(r.rental_id, 1)
        self.assertEqual(r.client_id, 3)
        self.assertEqual(r.book_id, 2)
        self.assertEqual(r.rented_date, datetime.date(2020, 11, 12))
        self.assertEqual(r.returned_date, datetime.date(2020, 11, 20))


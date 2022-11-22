
from jproperties import Properties

from Console.Ui import Ui

from Entity.Client import Client
from Entity.Book import Book
from Entity.Rental import Rental

from Repository.Client_Repo import ClientRepository
from Repository.Book_Repo import BookRepository
from Repository.Rental_Repo import RentalRepository

from Repository.ClientsTextFileRepo import ClientsTextFileRepository
from Repository.BooksTextFileRepo import BooksTextFileRepository
from Repository.RentalsTextFileRepo import RentalsTextFileRepository

from Repository.ClientsBinFileRepo import ClientsBinFileRepository
from Repository.BooksBinFileRepo import BooksBinRepository
from Repository.RentalsBinFileRepo import RentalsBinFileRepository

from Service.Client_Service import ClientService
from Service.Book_Service import BookService
from Service.Rental_Service import RentalService
from Service.Statistics import Statistics
from Service.UndoService import UndoService

from Entity.Client import ClientValidator
from Entity.Book import BookValidator
from Entity.Rental import RentalValidator


def read_client_input_file(file_name):
    result = []
    f = open(file_name, "r")
    line = f.readline()
    while len(line) > 0:
        line = line.split(";")
        result.append(Client(int(line[0]), line[1]))
        line = f.readline().strip()
    f.close()
    return result


def read_books_input_file(file_name):
    result = []
    f = open(file_name, "r")
    line = f.readline()
    while len(line) > 0:
        line = line.split(";")
        result.append(Book(int(line[0]), line[1], line[2]))
        line = f.readline()
    f.close()
    return result


def read_rentals_input_file(file_name):
    result = []
    f = open(file_name, "r")
    line = f.readline()
    while len(line) > 0:
        line = line.split(";")
        result.append(Rental(int(line[0]), int(line[1]), int(line[2]), line[3], line[4]))
        line = f.readline()
    f.close()
    return result


clients = read_client_input_file('ClientsInput.txt')
books = read_books_input_file('BooksInput.txt')
rentals = read_rentals_input_file('RentalsInput.txt')


configs = Properties()
with open('settings.properties', 'rb') as config_file:
    configs.load(config_file)

type = configs.get('repository').data

if type == 'inmemory':

    client_repo = ClientRepository(clients)
    book_repo = BookRepository(books)
    rental_repo = RentalRepository(rentals)

elif type == 'textfiles':

    client_repo = ClientsTextFileRepository(configs.get('clients').data)
    book_repo = BooksTextFileRepository(configs.get('books').data)
    rental_repo = RentalsTextFileRepository(configs.get('rentals').data)

elif type == 'binfiles':

    client_repo = ClientsBinFileRepository(configs.get('clients').data)
    book_repo = BooksBinRepository(configs.get('books').data)
    rental_repo = RentalsBinFileRepository(configs.get('rentals').data)


undo_service = UndoService()

client_validator = ClientValidator()

book_validator = BookValidator()

rental_validator = RentalValidator()

rental_service = RentalService(rental_repo, client_repo, book_repo, rental_validator, undo_service)
client_service = ClientService(client_repo, client_validator, rental_service, undo_service)
book_service = BookService(book_repo, book_validator, rental_service, undo_service)

statistics = Statistics(client_repo, book_repo, rental_repo)

ready = Ui(client_service, book_service, rental_service, statistics, undo_service)
ready.start_ui()


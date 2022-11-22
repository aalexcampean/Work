import random
import datetime

from Console.Ui import Ui
from Entity.Book import Book
from Entity.Client import Client
from Entity.Rental import Rental

from Repository.Book_Repo import BookRepository
from Repository.Client_Repo import ClientRepository
from Repository.Rental_Repo import RentalRepository

from Service.Book_Service import BookService
from Service.Client_Service import ClientService
from Service.Rental_Service import RentalService
from Service.Statistics import Statistics
from Service.UndoService import UndoService

from Entity.Book import BookValidator
from Entity.Client import ClientValidator
from Entity.Rental import RentalValidator


def create_client_list():
    clients = []

    lastname = ['Alexandru', 'Maria', 'Sofia', 'Alexandra', 'Serban', 'Darius', 'Anca', 'Iulia',
                'Lorena', 'Robert', 'Sebastian', 'Hana', 'Razvan', 'Sandra', 'Catalin', 'Teodora']

    surname = ['Campean', 'Gog', 'Pop', 'Popescu', 'Crisan', 'Mihu', 'Gutiu', 'Timis', 'Chetan',
               'Bob', 'Mitrea', 'Chirtes', 'Maier', 'Gherman', 'Szongott', 'Armasu']

    clients_ids = []
    for i in range(1, 11):
        clients_ids.append(i)

    for i in range(10):
        id_here = random.choice(clients_ids)
        clients_ids.remove(id_here)
        lastname_here = random.choice(lastname)
        surname_here = random.choice(surname)
        name_here = lastname_here + ' ' + surname_here
        clients.append(Client(id_here, name_here))

    return clients


def create_book_list():

    books = []

    books_with_authors = ['In Search of Lost Time-Marcel Proust', 'Ulysses-James Joyce',
                          'Don Quixote-Miguel de Cervantes', 'The Great Gatsby-F. Scott Fitzgerald',
                          'One Hundred Years of Solitude-Gabriel Garcia Marquez', 'Moby Dick-Herman Melville',
                          'War and Peace-Leo Tolstoy', 'Lolita-Vladimir Nabokov', 'Hamlet-William Shakespeare',
                          'The Catcher in the Rye-J. D. Salinger', 'The Odyssey-Homer',
                          'The Brothers Karamazov-Fyodor Dostoyevsky', 'Crime and Punishment-Fyodor Dostoyevsky',
                          'Fyodor Dostoyevsky-Gustave Flaubert', 'The Divine Comedy-Dante Alighieri',
                          'Pride and Prejudice-Jane Austen', 'Catch 22-Joseph Heller',
                          'Nineteen Eighty Four-George Orwell', 'Anna Karenina-Leo Tolstoy',
                          'The Grapes of Wrath-John Steinbeck'
                          ]

    books_ids = []
    for i in range(1, 11):
        books_ids.append(i)

    for i in range(10):

        id_here = random.choice(books_ids)
        books_ids.remove(id_here)
        names = random.choice(books_with_authors).split('-')
        title_here = names[0]
        author_here = names[1]
        books.append(Book(id_here, title_here, author_here))

    return books


def create_rentals_list(client_list, book_list):
    rentals = []

    available_clients_ids = []

    for c in client_list:
        available_clients_ids.append(c.id)

    available_books_ids = []

    for b in book_list:
        available_books_ids.append(b.id)

    rentals_ids = []
    for i in range(1, 11):
        rentals_ids.append(i)

    for i in range(10):

        id_rental_here = random.choice(rentals_ids)
        rentals_ids.remove(id_rental_here)

        id_client_here = random.choice(available_clients_ids)
        available_clients_ids.remove(id_client_here)

        id_book_here = random.choice(available_books_ids)
        available_books_ids.remove(id_book_here)

        ok = True
        while ok:

            start_dt_rent = datetime.date.today().replace(day=1, month=1).toordinal()
            end_dt_rent = datetime.date.today().toordinal()
            rented_date_here = datetime.date.fromordinal(random.randint(start_dt_rent, end_dt_rent))

            start_dt_return = datetime.date.today().replace(day=rented_date_here.day, month=rented_date_here.month).toordinal()
            end_dt_return = datetime.date.today().toordinal()
            returned_date_here = datetime.date.fromordinal(random.randint(start_dt_return, end_dt_return))

            if abs(returned_date_here - rented_date_here).days <= 14:
                ok = False

        rentals.append(Rental(id_rental_here, id_client_here, id_book_here, str(rented_date_here), str(returned_date_here)))

    return rentals


undo_service = UndoService()

client_validator = ClientValidator()
client_repo = ClientRepository(create_client_list())


book_validator = BookValidator()
book_repo = BookRepository(create_book_list())


rental_validator = RentalValidator()
rental_repo = RentalRepository(create_rentals_list(create_client_list(), create_book_list()))


rental_service = RentalService(rental_repo, client_repo, book_repo, rental_validator, undo_service)
client_service = ClientService(client_repo, client_validator, rental_service, undo_service)
book_service = BookService(book_repo, book_validator, rental_service, undo_service)

statistics = Statistics(client_repo, book_repo, rental_repo)

ready = Ui(client_service, book_service, rental_service, statistics, undo_service)
ready.start_ui()


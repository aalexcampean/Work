from Entity.Client import Client
from Entity.Book import Book
from Entity.Rental import Rental
from Service.Book_Service import BookService
from Service.Client_Service import ClientService
from Service.Rental_Service import RentalService
from Service.UndoService import UndoService
from Service.Statistics import Statistics


class Ui:

    def __init__(self, client_service: ClientService, book_service: BookService, rental_service: RentalService, statistics: Statistics, undo_service: UndoService):
        self._client_service = client_service
        self._book_service = book_service
        self._rental_service = rental_service
        self._statistics = statistics
        self._undo_service = undo_service

    """
    
    Display Functions
    
    """

    def display_all_books(self):
        print('\n')
        if len(self._book_service) == 0:
            print('!!! There are no books !!!')
        else:
            print('Books:\n')
            for b in self._book_service.books:
                print(str(b))

    def display_all_clients(self):
        print('\n')
        if len(self._client_service) == 0:
            print('!!! There are no clients !!!')
        else:
            print('Clients:\n')
            for c in self._client_service.clients:
                print(str(c))

    def display_all_rentals(self):
        print('\n')
        if len(self._rental_service) == 0:
            print('!!! There are no rented books !!!')
        else:
            print('Rentals:\n')
            for r in self._rental_service.rentals:
                print(str(r))

    def display_results(self, results_list):
        print('\n')
        if len(results_list) == 0:
            print('!!! No results found !!!')
        else:
            print('Results found:\n')
            for e in results_list:
                print(str(e))

    def display_most_rented_books_statistics(self, result_list):
        print('\n')
        print('Most rented books:\n')
        for e in result_list:
            print('Title: ' + str(e['book'].title).ljust(40) + ' Author: ' + str(e['book'].author).ljust(40) + 'Number of times they were rented: ' + str(e['number of rentals']))

    def display_most_active_clients_statistics(self, result_list):
        print('\n')
        print('Most active clients\n')
        for e in result_list:
            print(str(e['client']).ljust(40) + 'Number of days they rented books for: ' + str(e['number of rented days']))

    def display_most_rented_author_statistics(self, result_list):
        print('\n')
        print('Most rented author/authors:\n')
        for e in result_list:
            print('Author: ' + str(e['author']).ljust(30) + ' Number of times their books were rented: ' + str(e['number of rentals']))
            print('Books:')
            i = 0
            while i <= len(e['list of books']) - 1:
                print(str(e['list of books'][i]).ljust(40) + str(e['list of books'][i+1]) + ' rentals')
                i += 2
            print('\n')

    """

    Menu

    """

    def print_start(self):
        print('\n')
        print('1: Add')
        print('2: Delete')
        print('3: Update')
        print('4: Display')
        print('5: Rent / Return')
        print('6: Search Client / Book')
        print('7: Statistics')
        print('8: Undo / Redo')
        print('0: Exit')

    """

    Start

    """

    def start_ui(self):

        done = False
        while not done:

            self.print_start()
            x = input('Enter a command: ')

            try:
                if x == '1':

                    print('1.1: Add client')
                    print('1.2: Add book')
                    y = input('Enter a command: ')

                    if y == '1.1':

                        id_here = int((input('The id: ')))
                        name_here = input('The name: ')
                        self._client_service.add(Client(id_here, name_here))

                    elif y == '1.2':

                        id_here = int(input('The id: '))
                        title_here = input('New Name: ')
                        author_here = input('New author: ')
                        self._book_service.add(Book(id_here, title_here, author_here))

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '2':

                    print('2.1: Delete client')
                    print('2.2: Delete book')
                    y = input('Enter a command: ')

                    if y == '2.1':
                        id_here = int(input('The id: '))
                        self._client_service.delete(id_here)

                    elif y == '2.2':
                        id_here = int(input('The id: '))
                        self._book_service.delete(id_here)
                        self._rental_service.delete_rental_by_book(id_here)

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '3':

                    print('3.1: Update client')
                    print('3.2: Update book')
                    y = input('Enter a command: ')

                    if y == '3.1':
                        id_here = int(input('The id: '))
                        name_here = input('New Name: ')
                        self._client_service.update(Client(id_here, name_here))

                    elif y == '3.2':
                        id_here = int(input('The id: '))
                        title_here = input('New Name: ')
                        author_here = input('New author: ')
                        self._book_service.update(Book(id_here, title_here, author_here))

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '4':
                    print('4.1: Display clients')
                    print('4.2: Display books')
                    print('4.3: Display rentals')
                    y = input('Enter a command: ')

                    if y == '4.1':
                        self.display_all_clients()

                    elif y == '4.2':
                        self.display_all_books()

                    elif y == '4.3':
                        self.display_all_rentals()

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '5':
                    print('5.1: Rent')
                    print('5.2: Return')
                    y = input('Enter a command: ')

                    if y == '5.1':
                        id_rental_here = int(input('The rental id: '))
                        id_client_here = int(input('The client id: '))
                        id_book_here = int(input('The book id: '))
                        rented_date_here = input('The rented date (format: yyyy-mm-dd): ')
                        returned_date_here = None
                        self._rental_service.rent(Rental(id_rental_here, id_client_here, id_book_here, rented_date_here, returned_date_here))

                    elif y == '5.2':
                        id_rental_here = (int(input('The rental id: ')))
                        returned_date_here = input('The returned date (format: yyyy-mm-dd): ')
                        self._rental_service.turn_in(id_rental_here, returned_date_here)

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '6':
                    print('6.1: Search for clients')
                    print('6.2: Search for books')
                    y = input('Enter a command: ')

                    if y == '6.1':
                        search_by_this = input('Insert text: ')
                        self.display_results((self._client_service.search(search_by_this)))

                    elif y == '6.2':
                        search_by_this = input('Insert text: ')
                        self.display_results(self._book_service.search(search_by_this))

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '7':
                    print('7.1: Most rented books')
                    print('7.2: Most active clients')
                    print('7.3: Most rented author')
                    y = input('Enter a command: ')

                    if y == '7.1':
                        list_of_rented_books = []
                        self.display_most_rented_books_statistics(self._statistics.create_most_rented_books_statistic(list_of_rented_books))

                    elif y == '7.2':
                        list_of_active_clients = []
                        self.display_most_active_clients_statistics(self._statistics.create_most_active_clients_statistic(list_of_active_clients))

                    elif y == '7.3':
                        list_of_rented_books = []
                        self.display_most_rented_author_statistics(self._statistics.create_most_rented_authors_statistic(list_of_rented_books))

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '8':
                    print('8.1: Undo')
                    print('8.2: Redo')
                    y = input('Enter a command: ')

                    if y == '8.1':
                        self._undo_service.undo()

                    elif y == '8.2':
                        self._undo_service.redo()

                    else:
                        print('\n ??? Oh my god, what is that ???')

                elif x == '0':
                    done = True
                    print('See you later :*')

                else:
                    print('??? Oh my god, what is that ???')

            except Exception as ex:
                print('\n' + str(ex))





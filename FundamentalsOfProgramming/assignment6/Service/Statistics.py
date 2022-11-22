from Repository.Book_Repo import BookRepository
from Repository.Client_Repo import ClientRepository
from Repository.Rental_Repo import RentalRepository


class Statistics:

    def __init__(self, client_repo: ClientRepository, book_repo: BookRepository, rental_repo: RentalRepository):
        self._rental_repo = rental_repo
        self._client_repo = client_repo
        self._book_repo = book_repo

    def initialize_list_of_rented_books(self, list_of_rented_books):
        """
        This function creates the list of rented books, each item being a dictionary containing the book and
        the number of times it was rented
        :param list_of_rented_books: the list of books that were rented
        :return: the created list
        """

        for b in self._book_repo.books:
            list_of_rented_books.append({'book': b, 'number of rentals': 0})

    def eliminate_duplicate_books(self, list_of_rented_books):
        """
        The list of rented books may contain the same book but with different ids as this is possible in a normal library
        that is why this function comes in handy as it checks for duplicate book titles and authors and if it finds such a
        case, it attributes the number of rentals of the second one to the first and then deletes the second instance
        :param list_of_rented_books: the list of books that were rented
        :return: the new list
        """

        index1 = 0
        while index1 <= len(list_of_rented_books) - 2:
            index2 = index1 + 1
            while index2 <= len(list_of_rented_books) - 1:
                if list_of_rented_books[index1]['book'].title == list_of_rented_books[index2]['book'].title and \
                        list_of_rented_books[index1]['book'].author == list_of_rented_books[index2]['book'].author:
                    list_of_rented_books[index1]['number of rentals'] += list_of_rented_books[index2][
                        'number of rentals']
                    list_of_rented_books.remove(list_of_rented_books[index2])
                else:
                    index2 += 1
            index1 += 1

    def create_most_rented_books_statistic(self, list_of_rented_books):
        """
        This function creates the statistic consisting of the most rented books by creating the list of rented books
        by going through the list of books to cover all existing books. Then they are compared with the books' id from
        rentals and counted the number of rentals for each one
        :param list_of_rented_books: the list of books that were rented
        :return: the end list that is ready to be displayed
        """

        self.initialize_list_of_rented_books(list_of_rented_books)

        for r in self._rental_repo.rentals:
            for l in list_of_rented_books:
                if r.book_id == l['book'].id:
                    l['number of rentals'] += 1

        self.eliminate_duplicate_books(list_of_rented_books)

        return sorted(list_of_rented_books, key=lambda i: i['number of rentals'], reverse=True)

    def initialize_list_of_active_clients(self, list_of_active_clients):
        """
        This function creates the list of active clients, each item being a dictionary containing the client and
        the number of days they rented something for
        :param list_of_active_clients: the list of active clients
        :return: the created list
        """

        for c in self._client_repo.clients:
            list_of_active_clients.append({'client': c, 'number of rented days': 0})

    def create_most_active_clients_statistic(self, list_of_active_clients):
        """
        This function creates the statistic consisting of the most active clients by creating the list of active clients
        by going through the list of clients to cover all existing clients. Then they are compared with the clients' id from
        rentals and counted the number of days for each one (returned_date - rented_date)
        :param list_of_active_clients: the list of active clients
        :return: the end list that is ready to be displayed
        """

        self.initialize_list_of_active_clients(list_of_active_clients)

        for r in self._rental_repo.rentals:
            for l in list_of_active_clients:
                if r.client_id == l['client'].id:
                    l['number of rented days'] += abs(r.returned_date - r.rented_date).days

        return sorted(list_of_active_clients, key=lambda i: i['number of rented days'], reverse=True)

    def initialize_list_of_authors(self, list_of_rented_authors):
        """
        This fucntion creates the list of authors and their books adn the number of times each one was rented
        :param list_of_rented_authors: the list of rented authors
        :return: the newly created list
        """

        for c in self._book_repo.books:
            list_of_rented_authors.append({'author': c.author, 'number of rentals': 0, 'list of books': []})

    def eliminate_duplicate_authors(self, list_of_rented_authors):
        """
        The list of rented authors may contain the same author with the same book as this is possible in a normal library
        that is why this function comes in handy as it checks for duplicate authors - book titles and if it finds such a
        case, it deletes the second instance
        :param list_of_rented_authors: the list of rented authors
        :return: the new list
        """

        index1 = 0
        while index1 <= len(list_of_rented_authors) - 2:
            index2 = index1 + 1
            while index2 <= len(list_of_rented_authors) - 1:
                if list_of_rented_authors[index1]['author'] == list_of_rented_authors[index2]['author']:
                    list_of_rented_authors.remove(list_of_rented_authors[index2])
                else:
                    index2 += 1
            index1 += 1

    def find_the_most_rented_author(self, list_of_rented_authors):
        """
        This function filters the list of rented authors so that only the ones having the most rented books are left
        :param list_of_rented_authors: the list of rented authors
        :return: the updated list
        """

        the_max = 0
        for a in list_of_rented_authors:
            if the_max < a['number of rentals']:
                the_max = a['number of rentals']

        index = 0
        while index <= len(list_of_rented_authors) - 1:
            if list_of_rented_authors[index]['number of rentals'] != the_max:
                list_of_rented_authors.remove(list_of_rented_authors[index])
            else:
                index += 1

    def create_most_rented_authors_statistic(self, list_of_rented_authors):
        """
        This function creates the statistic consiting of the most rented author / authors (if there are 2 authors with
        the same number rented books
        :param list_of_rented_authors: the list of rented authors
        :return: the end list that is ready to be displayed
        """

        self.initialize_list_of_authors(list_of_rented_authors)

        new_list = []
        list_of_rented_books = self.create_most_rented_books_statistic(new_list)

        for b in list_of_rented_books:
            for a in list_of_rented_authors:
                if a['author'] == b['book'].author:
                    a['number of rentals'] += b['number of rentals']
                    a['list of books'].append(b['book'].title)
                    a['list of books'].append(b['number of rentals'])

        self.eliminate_duplicate_authors(list_of_rented_authors)

        self.find_the_most_rented_author(list_of_rented_authors)

        return list_of_rented_authors

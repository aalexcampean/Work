from Entity.Rental import Rental
from Repository.Rental_Repo import RentalRepository
import pickle


class RentalsBinFileRepository(RentalRepository):
    """
    Inheritance -> TextFileRepository 'IS A' Repository

    What we want:
        1. TextFileRepository behaves EXACTLY like Repository
            with one exception
        2. Ingredients are saved to/loaded from a text file
    """

    def __init__(self, file_name='Rentals.bin'):
        super().__init__([])
        self._file_name = file_name
        self._load()

    def add(self, rental_list):
        super().add(rental_list)
        self._save()

    def rent(self, rental):
        super().rent(rental)
        self._save()

    def turn_in(self, rental_id, returned_date):
        super().turn_in(rental_id, returned_date)
        self._save()

    def delete_rental_by_client(self, client_id):
        deleted_list = super().delete_rental_by_client(client_id)
        self._save()
        return deleted_list

    def delete_rental_by_book(self, book_id):
        deleted_list = super().delete_rental_by_book(book_id)
        self._save()
        return deleted_list

    def delete(self, rental_id):
        super().delete(rental_id)
        self._save()

    def update_rental(self, rental):
        super().update_rental(rental)
        self._save()

    def _save(self):
        f = open(self._file_name, "wb")
        pickle.dump(self._rentals, f)
        f.close()

    def _load(self):
        """
        Load data from file
        We assume file-saved data is valid
        """
        f = open(self._file_name, "rb")
        self._rentals = pickle.load(f)
        f.close()


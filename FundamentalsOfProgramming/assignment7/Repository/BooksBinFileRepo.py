from Entity.Book import Book
from Repository.Book_Repo import BookRepository
import pickle


class BooksBinRepository(BookRepository):
    """
    Inheritance -> TextFileRepository 'IS A' Repository

    What we want:
        1. TextFileRepository behaves EXACTLY like Repository
            with one exception
        2. Ingredients are saved to/loaded from a text file
    """

    def __init__(self, file_name='Books.bin'):
        super().__init__([])
        self._file_name = file_name
        self._load()

    @property
    def books(self):
        return super().books

    def find(self, book_id):
        return super().find(book_id)

    def add_book(self, book):
        super().add_book(book)
        self._save()

    def delete_book(self, book_id):
        book_object = super().delete_book(book_id)
        self._save()
        return book_object

    def update_book(self, book):
        super().update_book(book)
        self._save()

    def search(self, text, result_list):
        super().search(text, result_list)

    def __len__(self):
        return super().__len__()

    def _save(self):
        f = open(self._file_name, "wb")
        pickle.dump(self._books, f)
        f.close()

    def _load(self):
        """
        Load data from file
        We assume file-saved data is valid
        """
        f = open(self._file_name, "rb")
        self._books = pickle.load(f)
        f.close()


from Entity.Book import Book
from Repository.Book_Repo import BookRepository


class BooksTextFileRepository(BookRepository):
    """
    Inheritance -> TextFileRepository 'IS A' Repository

    What we want:
        1. TextFileRepository behaves EXACTLY like Repository
            with one exception
        2. Ingredients are saved to/loaded from a text file
    """

    def __init__(self, file_name='Books.txt'):
        super().__init__([])
        self._file_name = file_name
        self._load()

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

    def _save(self):
        f = open(self._file_name, 'wt')
        for bk in self._books:
            line = str(bk.id) + ';' + bk.title + ';' + bk.author
            f.write(line)
            f.write('\n')
        f.close()

    def _load(self):
        """
        Load data from file
        We assume file-saved data is valid
        """
        f = open(self._file_name, 'rt')  # read text
        lines = f.readlines()
        f.close()

        for line in lines:
            line = line.split(';')
            super().add_book(Book(int(line[0]), line[1], line[2]))


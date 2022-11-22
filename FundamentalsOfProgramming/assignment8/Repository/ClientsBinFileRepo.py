from Entity.Client import Client
from Repository.Client_Repo import ClientRepository
import pickle


class ClientsBinFileRepository(ClientRepository):
    """
    Inheritance -> TextFileRepository 'IS A' Repository

    What we want:
        1. TextFileRepository behaves EXACTLY like Repository
            with one exception
        2. Ingredients are saved to/loaded from a text file
    """

    def __init__(self, file_name='Clients.bin'):
        super().__init__([])
        self._file_name = file_name
        self._load()

    def add_client(self, client):
        super().add_client(client)
        self._save()

    def delete_client(self, client_id):
        client_object = super().delete_client(client_id)
        self._save()
        return client_object

    def update_client(self, client):
        super().update_client(client)
        self._save()

    def _save(self):
        f = open(self._file_name, "wb")
        pickle.dump(self._clients, f)
        f.close()

    def _load(self):
        """
        Load data from file
        We assume file-saved data is valid
        """
        f = open(self._file_name, "rb")
        self._clients = pickle.load(f)
        f.close()


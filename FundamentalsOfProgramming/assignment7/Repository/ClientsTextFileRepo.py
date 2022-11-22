from Entity.Client import Client
from Repository.Client_Repo import ClientRepository


class ClientsTextFileRepository(ClientRepository):
    """
    Inheritance -> TextFileRepository 'IS A' Repository

    What we want:
        1. TextFileRepository behaves EXACTLY like Repository
            with one exception
        2. Ingredients are saved to/loaded from a text file
    """

    def __init__(self, file_name='Clients.txt'):
        super().__init__([])
        self._file_name = file_name
        self._load()

    @property
    def clients(self):
        return super().clients

    def find(self, client_id):
        return super().find(client_id)

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

    def search(self, text, result_list):
        super().search(text, result_list)

    def __len__(self):
        return super().__len__()

    def _save(self):
        f = open(self._file_name, 'wt')
        for cl in self._clients:
            line = str(cl.id) + ';' + cl.name
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
            super().add_client(Client(int(line[0]), line[1]))


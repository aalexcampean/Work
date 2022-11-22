
class ClientException(Exception):
    def __init__(self, msg):
        self._msg = msg


class BookValidationException(ClientException):
    def __init__(self, error_list):
        self._errors = error_list

    def __str__(self):
        """
        the string representation of the list of exceptions raised in the validator
        :return:
        """
        
        result = ''

        for er in self._errors:
            result += er
            result += '\n'
        return result


class ClientValidator:

    @staticmethod
    def is_id_valid(client_id):
        if client_id < 1 or not isinstance(client_id, int):
            return False
        else:
            return True

    @staticmethod
    def is_name_valid(client_name):

        names = client_name.strip().split(' ')
        new_client_name = ''
        for n in range(len(names)):
            new_client_name += names[n].strip()

        return isinstance(client_name, str) and new_client_name.isalpha()

    def is_client_valid(self, client):
        """
        This functions calls all the static methods and checks if a rental is valid or not, raising the afferent
        exceptions
        :param client: the client in question
        :return:
        """

        errors = []
        if not self.is_id_valid(client.id):
            errors.append('!!! Invalid book id !!!')
        if not self.is_name_valid(client.name):
            errors.append('!!! Invalid client name !!!')

        if len(errors) > 0:
            raise BookValidationException(errors)


class Client:

    def __init__(self, client_id, client_name):

        if not isinstance(client_id, int):
            raise ClientException('!!! Invalid id !!!')
        if not isinstance(client_name, str):
            raise ClientException('!!! Invalid book title !!!')

        self._id = client_id
        self._name = self.split_name(client_name)

    def split_name(self, client_name):
        """
        This function splits the names, capitalizing the first letter of every name
        :param client_name: the name in question
        :return:
        """

        names = client_name.strip().split(' ')
        new_client_name = ''
        for n in range(0, len(names)):
            new_client_name += names[n].strip().capitalize() + ' '
        return new_client_name.strip()

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    def __str__(self):
        """
        The string representation of a client object
        :return:
        """

        return str('id: ' + str(self._id).ljust(5) + 'name: ' + self._name)

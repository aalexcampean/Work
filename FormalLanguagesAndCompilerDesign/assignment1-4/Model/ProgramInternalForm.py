class ProgramInternalForm:
    def __init__(self):
        self.__content = []

    @property
    def content(self):
        return self.__content

    def insert(self, id, code):
        self.__content.append((id, code))

    def __str__(self):
        return str(self.__content)

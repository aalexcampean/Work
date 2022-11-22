
class DataStructure:

    def __init__(self):
        self._data = []
        self._poz = 0

    def add(self, elem):
        self._data.append(elem)

    def __setitem__(self, key, value):
        self._data[key] = value

    def __getitem__(self, key):
        return self._data[key]

    def __delitem__(self, key):
        del self._data[key]

    def __iter__(self):
        # Returns an iterator over this data structure
        self._poz = 0
        return self

    def __next__(self):
        # Stop iteration when other elements are not available
        if self._poz == len(self._data):
            raise StopIteration()
        # Move to the next element
        self._poz += 1
        return self._data[self._poz - 1]

    def __len__(self):
        return len(self._data)
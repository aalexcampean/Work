import unittest

from DataStructure.Data_Structure import DataStructure


class DataStructureTest(unittest.TestCase):

    def test_next(self):
        data = DataStructure()
        data.add("elem1")
        next(data)

        data2 = DataStructure()
        try:
            next(data2)
        except StopIteration:
            self.assertEqual(len(data2), 0)

    def test_add(self):
        data = DataStructure()
        data.add('elem')
        self.assertEqual(len(data), 1)

    def test_del(self):
        data = DataStructure()
        data.add("elem")
        del data[0]
        self.assertEqual(len(data), 0)

    def test_set(self):
        data = DataStructure()
        data.add("elem")
        data[0] = 'elem2'
        self.assertEqual(data[0], "elem2")

    def test_get(self):
        data = DataStructure()
        data.add('elem')
        x = data[0]
        self.assertEqual(x, 'elem')

    def test_iter(self):
        data = DataStructure()
        iter(data)
        self.assertEqual(data._poz, 0)
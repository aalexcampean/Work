import unittest

from Sorting_Filtering.Sorting import gnome_sort_list
from Sorting_Filtering.Filtering import filter_list


class SortTest(unittest.TestCase):

    def test_gnome_sort_list(self):
        my_list = [4, 1, 6, 0]
        my_list = gnome_sort_list(my_list, lambda a, b: a > b)
        self.assertEqual(my_list, [0, 1, 4, 6])

    def test_filter_list(self):
        my_list = [4, 1, 6, 0, 3, 5]
        my_list = filter_list(my_list, lambda a: a % 2 == 0)
        self.assertEqual(my_list, [4, 6, 0])

# EX 1

# Write the iterable FunnyList class, which has the peculiar property that iterating over
# its elements produces only every 3rd element. Specifications or tests are not required.
# Follow the example below [3p].

# class FunnyList:
#
#     def __init__(self):
#         self._data = []
#
#     def __getitem__(self, key):
#         return self._data[key]
#
#     def append(self, value):
#         self._data.append(value)
#
#     def __iter__(self):
#         # Returns an iterator over this data structure
#         self._poz = 0
#         return self
#
#     def __next__(self):
#         # Stop iteration when other elements are not available
#         if self._poz == len(self._data):
#             raise StopIteration()
#         # Move to the next element
#         self._poz += 1
#         return self._data[self._poz - 1]





# # Initialize a funny list
# data = FunnyList()
# # Add elements
# for i in range(1,11):
#     data.append(i)
# # Prints 2 6
# print(data[1])
# print(data[5])
# # Prints 1 4 7 10
# for i in data:
#     print(i)

# EX 2

# Analyse the time complexity of the following function [2p].
#
# def f(n):
#     s = 0
#     for i in range(1, n ** 3 + n):
#         j = 1
#         while j < n:
#             s = s + j
#             j = j * 2
#     return s

# T(n) = (n^3 + n - 1)log2 n  - the first loop goes until n^3 + n, while the second one depends on n,
#                                 j being multiplied by 2 until reaching or exceeding n
#
# That is why, O(n) = n^3 * log n
# Given this function, we have Best Case = Average Case = Worst Case = O(n) = n^3 * log n
#
#
#


# Ex 3

# Write the specification, test cases and Python 3 code for a function which removes all occurrences
# of a list from another list. For example, calling that function
# for a = [1, 2] and b = [3, 1, 2, 4, 1, 2, 5] will change the value of b to [3, 4, 5].
# Do not use other modules or inbuilt functions except those for removing a single element
# from a Python list [4p].

def remove_list(list1, list2):
    """
    This function removes all occurrences of a list in another list by parsing the second one
    and simultaneously searching through the first one to check if the elements are the same, if so
    the amount equal to the length of the first list will be removed from the second one starting
    at position i
    :param list1: the list that can appear in the other
    :param list2: the list from which all occurrences of the first one will be deleted
    :return: the newly computed list
    """
    i = 0
    # parse the second list
    while i <= len(list2) - 1:
        aux = i                 # we use aux not to lose the value of i
        j = 0
        found = True            # found is used for checking if the first list occurs in the second one
        # parse the first lst
        while j <= len(list1) - 1:
            # if the compared elements are not he same, there is no point in checking anymore
            if list2[aux] != list1[j]:
                found = False
                break
            aux += 1
            j += 1

        # check if we found what we are looking for and if so, delete the
        # amount equal to the length of the first list from position i
        if found:
            for cont in range(len(list1)):
                list2.pop(i)

        # increase i only if not found
        else:

            i += 1

def test_remove_list():
    """
    This function tests the procedure
    :return:
    """

    list1 = [1, 2]
    list2 = [3, 1, 2, 4, 1, 2, 5]

    correct_result = [3, 4, 5]
    incorrect_result = [3, 4, 1, 2, 5]

    remove_list(list1, list2)
    assert list2 == correct_result
    try:
        assert list2 == incorrect_result
    except AssertionError as ae:
        assert True

test_remove_list()

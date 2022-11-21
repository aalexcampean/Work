from math import gcd

# Given a list, compute the sum of all elements found on a prime position

# def is_prime(number):
#     """
#     This function checks if a given number is prime or not
#     :param number: the number in question
#     :return: true if prime or false otherwise
#     """
#     if number < 2:
#         ok = False
#
#     else:
#         ok = True
#         for x in range(2, number // 2 + 1):
#             if number % x == 0:
#                 ok = False
#
#     return ok
#
#
# def sum_the_numbers(list, l, r):
#     """
#     This function computes the sum of all elements of a list found on prime positions using divide and
#     conquer strategy
#     :param list: the list in question
#     :param l: the left index
#     :param r: the right index
#     :return: the computed sum
#     """
#
#     if l == r:
#         if is_prime(l):
#             return list[l]
#         else:
#             return 0
#
#     else:
#
#         mid = (l + r) // 2
#
#         return sum_the_numbers(list, l, mid) + sum_the_numbers(list, mid + 1, r)
#
# def test_sum():
#
#     list = [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
#
#     assert sum_the_numbers(list, 0, 14) == 71
#
#     l = 5
#
#     try:
#         sum_the_numbers(5, 0, 0)
#         assert False
#     except AssertionError:
#         assert True
#
#
# test_sum()


# Analyse the time and extra-space complexity of the following function

# def f(n):
#     sum = 0                       - 1
#     for i in range(1, n ** 3):
#         aux = 0                   - 1
#         while i != 0:
#             aux += i % 2          - 1
#             i //= 10              - 1
#         sum += aux                - 1
#
#     return sum

# T(n) = lg 1 + lg 2 + .. + lg n^3 -1 = lg (1 * 2 * ... * n^3 - 1) = lg ((n^3-1)!)
# O(n) = n^3 log n
# There is no best case regarding this example
# Average Case = Worst Case = O(n) = n^3 log n
# Regarding the extra space complexity O(n) = 1, O(1), the extra variables used are sum, aux, i


# Analyse the time and extra-space complexity of the following function

# def f(a, b):
#     if a != 1:
#         f(a-1, b-1)
#         print(a, b)
#         f(a-1, b-1)
#     else:
#         print(a, b)

# T(n) = 1 if a = 1
#      = 2^a if a != 1
# O(n) = n - linear complexity
# Best case is when a = 1, O(1)
# Average Case = Worst Case = O(2^n)
# Regarding the extra space complexity, it is O(0), the only variables used being a, b


# Given a list, find the greatest prime number found on an even position

# def is_prime(number):
#     """
#     This function checks if a given number is prime or not
#     :param number: the number in question
#     :return: true if prime or false otherwise
#     """
#     if number < 2:
#         ok = False
#
#     else:
#         ok = True
#         for x in range(2, number // 2 + 1):
#             if number % x == 0:
#                 ok = False
#
#     return ok
#
#
# def is_even(number):
#     """
#     This function checks if a given number is even or not
#     :param number: the given number
#     :return: true if even or false otherwise
#     """
#     if number % 2 == 0:
#         return True
#
#     return False
#
#
# def find_max_prime(list, l, r):
#
#     if l == r:
#         if is_even(l) and is_prime(list[l]):
#             return list[l]
#         return 0
#
#     mid = (l + r) // 2
#
#     if max(find_max_prime(list, l, mid), find_max_prime(list, mid + 1, r)) == 0 and r - l == len(list) - 1:
#         return None
#     else:
#         return max(find_max_prime(list, l, mid), find_max_prime(list, mid + 1, r))
#
#
# print(find_max_prime([5, 6, 7, 8, 9, 10, 4, 12, 13, 14, 15, 16, 17, 25, 19], 0, 14))
# print(find_max_prime([1, 2, 6, 4], 0, 3))


# Define a Sparse Data Structure. We have the class Sparse List. Use _setitem_, _getitem_. Zero values
# are not represented in memory

# class SparseList:
#
#     def __init__(self):
#         self._values = []
#
#     def __getitem__(self, key):
#         for i in self._values:
#             if i[0] == key:
#                 return i[1]
#         return 0
#
#     def __setitem__(self, key, value):
#         ok = False
#         for i in self._values:
#             if i[0] == key:
#                 i[1] = value
#                 ok = True
#         if not ok:
#             self._values.append([key, value])
#
#     def append(self, value):
#         key = self._values[-1][0] + 1
#         self._values.append([key, value])
#
#     def __len__(self):
#         maximum = 0
#         for i in self._values:
#             if i[0] > maximum:
#                 maximum = i[0]
#         return maximum + 1
#
#
# data = SparseList()
# data[1] = 'a'
# data[4] = 'b'
# data[9] = 'c'
#
# data[14] = 'd'
#
# data.append('z')
#
# for i in range(0, len(data)):
#     print(data[i])


# Define a Sparse Data Structure. We have the class Sparse List. Use _setitem_, _getitem_. Zero values
# are not represented in memory


# class SparseList:
#
#     def __init__(self):
#         self._values = []
#
#     def __getitem__(self, key):
#         for i in self._values:
#             if i[0] == key:
#                 return i[1]
#         return 0
#
#     def __setitem__(self, key, value):
#         ok = False
#         for i in self._values:
#             if i[0] == key:
#                 i[1] = value
#                 ok = True
#         if not ok:
#             self._values.append([key, value])
#
#     def __add__(self, other):
#         maximum = 0
#         for i in self._values:
#             if i[0] > maximum:
#                 maximum = i[0]
#
#         for i in range(len(other)):
#             if other[i] != 0:
#                 self._values.append([maximum + 1 + i, other[i]])
#
#     def append(self, value):
#         key = self._values[-1][0] + 1
#         self._values.append([key, value])
#
#     def __len__(self):
#         maximum = 0
#         for i in self._values:
#             if i[0] > maximum:
#                 maximum = i[0]
#         return maximum + 1
#
#
# data1 = SparseList()
# data1[1] = 'a'
# data1[3] = 'b'
# data1[5] = 'c'
#
# data2 = SparseList()
#
# data2[0] = 'x'
# data2[3] = 'z'
#
# data1 + data2
#
# for i in range(0, len(data1)):
#     print(data1[i])


# Define a Sparse Data Structure. We have the class Sparse Matrix. Zero values
# are not represented in memory

# class SparseMatrix:
#
#     def __init__(self, nr_of_rows, nr_of_columns):
#
#         self._rows = nr_of_rows
#         self._columns = nr_of_columns
#         self._data = []
#
#     def get(self, x, y):
#         for i in self._data:
#             if i[0] == x and i[1] == y:
#                 return i[2]
#         return 0
#
#     def set(self, row, column, value):
#         if row > self._rows - 1 or row < 0 or column > self._columns - 1 or column < 0:
#             raise ValueError('INDEX OUT OF RANGE')
#         ok = False
#         for i in self._data:
#             if i[0] == row and i[1] == column:
#                 i[2] = value
#                 ok = True
#         if not ok:
#             self._data.append([row, column, value])
#
#     def __len__(self):
#         maximum = 0
#         for i in self._data:
#             if i[0] > maximum:
#                 maximum = i[0]
#         return maximum + 1
#
#     def __str__(self):
#         string = ''
#         for i in range(self._rows):
#             for j in range(self._columns):
#                 string += str(self.get(i, j)) + ' '
#
#             if i != self._rows - 1:
#                 string += '\n'
#
#         return string
#
# # Initialise a 3x3 sparse matrix
# m1 = SparseMatrix(3, 3)
# # Value at [1,1] is 2
# m1.set(1, 1, 2)
# # Value at [2,2] is 4
# m1.set(2, 2, 4)
# # Prints
# # 0 0 0
# # 0 2 0
# # 0 0 4
# print(m1)
# # Prints '<class 'ValueError'>'
# try:
#     m1.set(3, 3, 99)
# except Exception as e:
#     print(type(e))
# # Update value at [1,1] with 2 + 1
# m1.set(1, 1, m1.get(1, 1) + 1)
# print(m1)
# # Prints
# # 0 0 0
# # 0 3 0
# # 0 0 4

# Using divide and conquer find the greatest common divisor of the numbers found on odd positions

# def is_even(number):
#     """
#     This function checks if a given number is even or not
#     :param number: the given number
#     :return: true if even or false otherwise
#     """
#     if number % 2 == 0:
#         return True
#
#     return False


# def find_the_gcd(list, l, r):
#     """
#     This function computes the greatest common divisor of all numbers found on odd positions, using the
#     divide and conquer strategy
#     :param list: the give list
#     :param l: the left index
#     :param r: the right index
#     :return: the computed gcd
#     """
#
#     if r == l:
#         if not is_even(l):
#             return list[l]
#     else:
#         mid = (l + r) // 2
#         if find_the_gcd(list, l, mid) is None:
#             return find_the_gcd(list, mid + 1, r)
#         elif find_the_gcd(list, mid + 1, r) is None:
#             return find_the_gcd(list, l, mid)
#         else:
#             return gcd(find_the_gcd(list, l, mid), find_the_gcd(list, mid + 1, r))


# def find_the_gcd(list, l, r):
#     """
#     This function computes the greatest common divisor of all numbers found on odd positions, using the
#     divide and conquer strategy
#     :param list: the give list
#     :param l: the left index
#     :param r: the right index
#     :return: the computed gcd
#     """
#
#     if r == l:
#         if not is_even(l):
#             return list[l]
#         return 0
#
#     mid = (l + r) // 2
#
#     return gcd(find_the_gcd(list, l, mid), find_the_gcd(list, mid + 1, r))
#
#
# print(find_the_gcd([2, 35, 5, 65, 10, 20, 5], 0, 6))


# Using divide and conquer compute the product of prime numbers found on positions of multiples of 3


def is_prime(number):
    """
    This function checks if a given number is prime or not
    :param number: the number in question
    :return: true if prime or false otherwise
    """
    if number < 2:
        ok = False

    else:
        ok = True
        for x in range(2, number // 2 + 1):
            if number % x == 0:
                ok = False

    return ok


def is_multiple_of_3(number):
    if number % 3 == 0:
        return True
    return False


def compute_product(list, l, r):

    if l == r:
        if is_multiple_of_3(l) and is_prime(list[l]):
            return list[l]

        return 1

    mid = (l + r) // 2
    
    if compute_product(list, l, mid) * compute_product(list, mid + 1, r) == 1 and r - l == len(list) - 1:
        return None

    return compute_product(list, l, mid) * compute_product(list, mid + 1, r)


print(compute_product([0, 1, 2, 31, 4, 5, 2, 7, 8, 9, 10], 0, 10))
print(compute_product([0, 1, 2, 10], 0, 3))

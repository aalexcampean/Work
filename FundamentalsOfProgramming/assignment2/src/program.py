#
# Write the implementation for A2 in this file
#

# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities
from math import isqrt


def read_complex_number():
    """
    Reads user's input and then calls the function that creates the complex number
    """
    nr = None
    while not nr:
        try:
            nr_real = int(input('Give me the real part of the number: '))
            nr_imaginary = int(input('Give me the imaginary part of the number: '))
            '''
            Here the values that compose a complex number are given and then with them created a number
            '''
            nr = create_complex_number(nr_real, nr_imaginary)
            # check if error
        except ValueError as ve:
            print('give me and integer')
    return nr


def print_menu():
    print('- Program Menu -')
    print('1. Show all numbers')
    print('2. Add a list of numbers')
    print('3. The sequence consisting of numbers having increasing modulus')
    print('4. The sequence consisting of numbers that have the sum of their elements = 10+10i')
    print('0. Exit')


def add_number_ui(nr_list):
    """
    This function adds each new number to the list
    """
    nr = read_complex_number()
    nr_list.append(nr)


def show_all_numbers_ui(nr_list):
    """
    Prints all the numbers that are currently in the list og complex numbers
    """
    x = 1
    for nr in nr_list:
        print(to_str(nr, x))
        x += 1


def start():
    """
    Initializing the list
    Populating the list
    Creating a dictionary with commands for the user (each one calls it's corresponding function)
    """
    nr_list = []
    numbers_added_already(nr_list)
    command_dict = {'1': show_all_numbers_ui, '2': add_list_of_numbers, '3': property4, '4': property10}
    done = False
    while not done:
        print_menu()
        command = input("Enter command: ")
        if command in command_dict:
            # NB! show_all_students -> variable that references a function
            # show_all_students() -> function call
            # () -> function call operator
            command_dict[command](nr_list)
        elif command == '0':
            print('You exited!')
            done = True
        else:
            print('Invalid command!')


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!


def create_complex_number(nr_real, nr_imaginary):
    return {"real_part": nr_real, "imag_part": nr_imaginary}


def get_real(complex_number):
    return complex_number['real_part']


def get_imaginary(complex_number):
    return complex_number['imag_part']


def to_str(complex_number, x):
    """
    Here the values are converted to strings and then prepared to be printed in this way
    """
    r = get_real(complex_number)
    i = get_imaginary(complex_number)
    if i < 0:
        return 'z' + str(x) + ' = ' + str(r) + ' - ' + str(abs(i)) + 'i'
    else:
        return 'z' + str(x) + ' = ' + str(r) + ' + ' + str(i) + 'i'


def add_list_of_numbers(nr_list):
    """
    Adding a list of numbers to our current one
    """
    try:
        x = int(input('Give me the length of the sequence you are going to write: '))
    except ValueError as ve:
        print('The given value is not valid')
        return
    for i in range(x):
        add_number_ui(nr_list)


def numbers_added_already(nr_list):
    """
    Some elements to populate the lost beforehand
    """
    nr_list.append(create_complex_number(1, 1))
    nr_list.append(create_complex_number(8, 2))
    nr_list.append(create_complex_number(2, 7))
    nr_list.append(create_complex_number(0, 1))
    nr_list.append(create_complex_number(5, 5))
    nr_list.append(create_complex_number(1, 1))
    nr_list.append(create_complex_number(1, 1))
    nr_list.append(create_complex_number(-5, -5))
    nr_list.append(create_complex_number(7, 8))
    nr_list.append(create_complex_number(7, 8))


def property10(nr_list):
    """
    This function searches for the longest sequence with the property that the sum of all elements is
    10 + 10i. This is done by keeping a sum of the reals and of imaginaries. Each one is being formed
    as we move through the sequence. When we find one that satisfy our condition we keep the position
    of the last number in our correct sequence so we can then print it. If one of the sums goes over 10
    we start again from the next value after the first one
    """
    sum_of_reals = 0
    sum_of_imaginaries = 0
    current_length = 0
    max_length = 0
    last = 0
    first_of_sequence = 0
    i = 0
    while i <= len(nr_list)-1:
        sum_of_reals += get_real(nr_list[i])
        sum_of_imaginaries += get_imaginary(nr_list[i])
        current_length += 1
        if sum_of_imaginaries > 10 or sum_of_reals > 10:
            first_of_sequence += 1
            i = first_of_sequence
            sum_of_reals = get_real(nr_list[i])
            sum_of_imaginaries = get_imaginary(nr_list[i])
            current_length = 1
        elif sum_of_reals == 10 and sum_of_imaginaries == 10:
            if current_length > max_length:
                max_length = current_length
                last = i
        i += 1

    """if sum_of_imaginaries == 10 and sum_of_imaginaries == 10:
        if current_length > max_length:
            max_length = current_length
            last = i"""

    show_all_numbers_ui(nr_list[last - max_length + 1: last + 1])


def property4(nr_list):
    """
    This function searches for the longest sequence that has increasing moduli. It does this by first
    keeping the first modulus and then going through the sequence. We always keep the current modulus
    and the last one to compare them. If the condition we need is no longer satisfied that means that
    our current sequence is done and we need to keep it's length if it is relevant and the position of
    the last number in the sequence.
    """
    last_modulus = calculate_square_modulus(nr_list[0])
    current_modulus = 0
    max_length = 0
    current_length = 1
    i = 1
    last = 0
    while i <= len(nr_list) - 1:
        current_modulus = calculate_square_modulus(nr_list[i])
        if current_modulus < last_modulus:
            if current_length > max_length:
                max_length = current_length
                last = i - 1
            current_length = 1
        else:
            current_length += 1
        last_modulus = current_modulus
        i += 1

    if current_length > max_length:
        max_length = current_length
        last = i - 1

    show_all_numbers_ui(nr_list[last - max_length + 1: last + 1])


def calculate_square_modulus(complex_number):
    """
    Calculating the square of the modulus
    """

    mod = (get_real(complex_number) ** 2) + (get_imaginary(complex_number) ** 2)
    return mod

start()
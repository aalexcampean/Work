"""
This is the user interface module. These functions call functions from the domain and functions module.
"""
from functions.functions import calculate_balance, to_str, remove_transactions_by_day, \
    remove_transactions_by_type, add_transaction, calc_sum, find_the_max, filter_transactions_by_type, filter_transactions_by_type_and_value
from domain.entity import get_value, get_day, get_type, create_transaction


def display_transactions_ui(transaction_list, cmd_params):
    """
    This is the main display function that, depending on the given command, displays the list of
    transactions by given criteria
    """
    transaction_list.sort(key=get_day)
    tokens = cmd_params.split(' ')  # we split the params string into a list of strings
    if len(tokens[0]) == 0:
        display_all_transactions(transaction_list)
    else:
        if tokens[0] in ['in', 'out']:
            display_type_transactions(transaction_list, tokens[0])
        elif tokens[0] in ['>', '<', '=']:
            display_value_transaction(transaction_list, tokens[0], tokens[1])
        elif tokens[0] == 'balance':
            try:
                print(calculate_balance(transaction_list, tokens[1]))
            except ValueError as ve:
                print(str(ve))


def display_all_transactions(transaction_list):
    """
    This function displays all transactions from this month
    """
    ok = False
    for transaction in transaction_list:
        print(to_str(transaction))
        ok = True
    print('There are no transaction left this month') if not ok else ''


def display_type_transactions(transaction_list, typep):
    """
    This function displays all transaction having a given type
    :param transaction_list: the list containing the transactions from this month
    :param typep: the given type
    """
    ok = False
    for transaction in transaction_list:
        if typep.lower() == get_type(transaction).lower():
            ok = True
            print(to_str(transaction))
    if not ok:
        print('There are no such transactions to display')


def display_value_transaction(transaction_list, sign, value):
    """
    This function displays all transaction equal to, greater or smaller than a give value
    :param transaction_list: the list containing the transactions from this month
    :param tokens: the sign so that we know what relation should be established + the given value
    """
    ok = False
    if sign == '=':
        for transaction in transaction_list:
            if int(value) == (get_value(transaction)):
                print(to_str(transaction))
                ok = True
    elif sign == '>':
        for transaction in transaction_list:
            if (get_value(transaction)) > int(value):
                print(to_str(transaction))
                ok = True
    elif sign == '<':
        for transaction in transaction_list:
            if (get_value(transaction)) < int(value):
                print(to_str(transaction))
                ok = True
    if not ok:
        print('There are no such transactions to display')


#
# REMOVE FUNCTION
#


def remove_transactions_ui(transaction_list, cmd_params):
    """
    This is the main remove function that further call other functions depending on the criteria that
    shows what needs to be removed
    :param transaction_list: the list containing the transactions from this month
    :param cmd_params: the parameters of the command so that the program knows what function to call
    """
    tokens = cmd_params.split(' ')
    if cmd_params.isalpha():
        try:
            remove_transactions_by_type(transaction_list, tokens[0])
        except ValueError as ve:
            print(str(ve))
    else:
        if len(tokens) == 1:
            try:
                remove_transactions_by_day(transaction_list, int(tokens[0]), int(tokens[0]))
            except ValueError as ve:
                print(str(ve))
        elif len(tokens) == 3:
            remove_transactions_by_day(transaction_list, int(tokens[0]), int(tokens[2]))


#
# ADD FUNCTION
#


def add_transaction_command_ui(transaction_list, cmd_params):
    """
    This function adds a new transaction to the list
    :param transaction_list: the list containing the transactions from this month
    :param cmd_params: the parameter needed to execute the command
    """
    # '24, 3000, out, Rent'
    tokens = cmd_params.split(' ')
    if len(tokens) != 4:
        raise ValueError('Invalid parameter count')

    for i in range(len(tokens)):
        tokens[i] = tokens[i].strip()

    transaction = create_transaction(int(tokens[0]), int(tokens[1]), (tokens[2]), tokens[3])
    add_transaction(transaction_list, transaction)


#
# SUM FUNCTION
#


def sum_ui(transaction_list, cmd_params):
    token = cmd_params.split(' ')
    if len(token) != 1:
        raise ValueError('invalid param count')
    else:
        the_type = token[0]
        print(calc_sum(transaction_list, the_type))


#
# MAX FUNCTION
#


def max_ui(transaction_list, cmd_params):
    tokens = cmd_params.split(' ')
    print(find_the_max(transaction_list, tokens[0], tokens[1]))


#
# FILTER FUNCTION
#


def filter_function_ui(transaction_list, cmd_params):
    tokens = cmd_params.split(' ')
    if len(tokens) == 1:
        try:
            filter_transactions_by_type(transaction_list, tokens[0])
        except ValueError as ve:
            print(str(ve))
    else:
        try:
            filter_transactions_by_type_and_value(transaction_list, tokens[0], tokens[1])
        except ValueError as ve:
            print(str(ve))


#
# UNDO FUNCTION
#


def undo_last_ui(history):
    last_list = []
    if len(history) > 0:
        last_list = history.pop(-1)
    else:
        raise AssertionError('Cannot undo anymore')
    return last_list.copy()



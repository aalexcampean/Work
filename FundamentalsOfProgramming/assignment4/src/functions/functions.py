"""
Functions that implement program features. They should call each other, or other functions from the domain
"""
from domain.entity import get_value, get_type, get_day, get_description, create_transaction


def split_command(command):
    """
    Split - command string into command word and parameters
    :return: (command_word, command_params)
    """
    # add 10, 2000, in, Salary
    # insert / remove / list
    # command_word = add / insert / remove / list
    # command_params = 10, 2000, in, Salary
    command = command.strip()
    # separate the first appearance of ' '
    # command.split( ... ), or command.find(' ')
    tokens = command.split(' ', 1)
    command_word = tokens[0].strip().lower()  # make the command lower cased so that the program executes it regardless
    command_params = tokens[1].strip() if len(tokens) == 2 else ''

    return command_word, command_params       # this functions returns a tuple, so one variable


def add_transaction(transaction_list, transaction):
    """
    Add student to the list
    :param transaction_list: list of transaction
    :param transaction: The new transaction
    :return: -
    """
    transaction_list.append(transaction)


def to_str(transaction):
    """
    Build the str representation for a transaction
    :param transaction: The transaction
    :return: Its str representation
    """
    return ' day: ' + str(get_day(transaction)) + ' value: ' + str(get_value(transaction)) + ' type: ' + get_type(transaction) + ' description: ' + get_description(transaction)


#
# REMOVE NON UI FUNCTIONS
#


def remove_transactions_by_type(transaction_list, typet):
    """
    This function removes all transactions having the given type by the user
    :param transaction_list: the list containing the transactions from this month
    :param typet: the type of the transactions that need to be deleted
    :return:
    """
    ok = False
    i = 0
    while i <= len(transaction_list)-1:
        if typet.lower() == get_type(transaction_list[i]).lower():
            ok = True
            transaction_list.remove(transaction_list[i])
        else:
            i += 1

    if not ok:
        raise ValueError("There are no such transactions to delete")


def remove_transactions_by_day(transaction_list, left, right):
    """
    This function deletes the all transactions from a given day until another given day,
    it works also just for the transactions of a single given day
    :param transaction_list: the list containing the transactions from this month
    :param left: the day from which the program should delete all transactions
    :param right: the day until which the program should delete all transactions
    """
    ok = False
    i = 0
    while i <= len(transaction_list) - 1:
        if left <= get_day(transaction_list[i]) <= right:
            transaction_list.remove(transaction_list[i])
            ok = True
        else:
            i += 1
    if not ok:
        raise ValueError("There are no such transactions to delete")


#
# REPLACE FUNCTION
#


def replace_transaction(transaction_list, cmd_params):
    """
    Replacing the value of a specific transaction from the list
    """
    tokens = cmd_params.split(' ')
    for transaction in transaction_list:
        if get_day(transaction) == int(tokens[0]) and get_type(transaction).lower() == tokens[1].lower() and get_description(transaction).lower() == tokens[2].lower():
            transaction['value'] = tokens[4]


#
# CALCULATE BALANCE
#


def calculate_balance(transaction_list, day):
    """
    This function displays the balance of the transactions until a given day
    :param transaction_list: the list containing the transactions from this month
    :param day: the day until the balance should be made
    """
    balance = 0
    ok = False
    s_in = 0
    s_out = 0
    for transaction in transaction_list:
        if get_day(transaction) > int(day):
            break
        else:
            if get_type(transaction).lower() == 'in':
                s_in += get_value(transaction)
                ok = True
            else:
                s_out += get_value(transaction)
                ok = True
    balance = s_in - s_out
    if ok:
        return balance
    else:
        raise ValueError('There are no transaction until day ' + day)


#
# CALCULATE THE SUM
#


def calc_sum(transaction_list, the_type):
    """
    This function calculates the sum of the transactions having a specific type
    :param transaction_list: the list of transactions
    :param the_type: the type of the transactions that make up the sum
    :return: the sum or a message in case the sum is 0
    """
    s = 0
    for transaction in transaction_list:
        if get_type(transaction) == the_type:
            s += get_value(transaction)
    if s != 0:
        return 'The sum of all ' + str(the_type) + ' transactions is ' + str(s)
    else:
        return 'There are no such transactions on this day'


#
# FIND THE MAX
#


def find_the_max(transaction_list, the_type, the_day):
    """
    This function returns the maximum all transactions from a given day having the same type
    :param transaction_list: the list of transactions
    :param the_type: the type by which the max is found
    :param the_day: the day by which the max is found
    :return: the maximum or a message in case the max is 0
    """
    maxim = 0
    for transaction in transaction_list:
        if get_type(transaction) == the_type:
            if get_day(transaction) == int(the_day):
                if get_value(transaction) > maxim:
                    maxim = get_value(transaction)
    if maxim != 0:
        return 'The maximum value of the transaction from day ' + the_day + ' with the type ' + the_type + ' is ' + str(maxim)
    else:
        return 'There are no such transactions on this day'


#
# FILTER FUNCTIONS
#


def filter_transactions_by_type(transaction_list, given_type):
    """
    This function filters the transactions by type thus removing the transactions with a different type
    from the given one
    :param transaction_list: the list of transactions
    :param give_type: the type given by the user
    :return: the filtered list or a ValueError
    """
    ok = False
    i = 0
    while i <= len(transaction_list) - 1:
        if get_type(transaction_list[i]) != given_type:
            transaction_list.remove(transaction_list[i])
            ok = True
        else:
            i += 1
    if not ok:
        raise ValueError('Your list already contains just transactions with the given type')


def filter_transactions_by_type_and_value(transaction_list, given_type, given_value):
    """
    this function filters the list by type and by value, thus filtering the list so that only the
    transactions with the given type and the value less than the given one are shown
    :param transaction_list: the list of transactions that needs to be filtered
    :param given_type: the type given by the user
    :param given_value: the type given by the user
    :return: the filtered list or a ValueError
    """
    ok = False
    i = 0
    while i <= len(transaction_list) - 1:
        if (get_type(transaction_list[i]) != given_type) or (str(get_value(transaction_list[i])) >= given_value):
            transaction_list.remove(transaction_list[i])
            ok = True
        else:
            i += 1
    if not ok:
        raise ValueError('Your list already contains just transactions with the given type and desired values')


#
# TEST FUNCTIONS
#


def test_init(transaction_list):
    """
    This fuction populates the list beforehand
    :param transaction_list:
    :return: A populated list of transactions
    """
    transaction_list.append(create_transaction(10, 2000, 'in', 'Salary'))
    transaction_list.append(create_transaction(12, 3000, 'in', 'Job'))
    transaction_list.append(create_transaction(14, 800, 'out', 'Shoes'))
    transaction_list.append(create_transaction(14, 5000, 'out', 'Shopping'))
    transaction_list.append(create_transaction(16, 200, 'out', 'Cleaning'))
    transaction_list.append(create_transaction(17, 3000, 'in', 'Rent 1'))
    transaction_list.append(create_transaction(17, 4000, 'in', 'Rent 2'))
    transaction_list.append(create_transaction(19, 200, 'out', 'Cash Gog'))
    transaction_list.append(create_transaction(19, 1500, 'in', 'Editing'))
    transaction_list.append(create_transaction(20, 300, 'out', 'Restaurant'))


def test_add_transaction():
    transaction_list = []
    test_init(transaction_list)
    # Test that we can add a valid student
    t = create_transaction(19, 5000, 'in', 'Payment')
    try:
        add_transaction(transaction_list, t)
    except ValueError:
        assert False


def test_split_command():
    cmd = 'insert        10 5000 in food'
    cmd_word, cmd_params = split_command(cmd)
    assert cmd_word == 'insert' and cmd_params == '10 5000 in food'

    cmd_word, cmd_params = split_command('exit')
    assert cmd_word == 'exit' and cmd_params == ''


def test_remove_transactions_by_type():
    transaction_list = []
    test_init(transaction_list)
    remove_transactions_by_type(transaction_list, 'in')
    for transaction in transaction_list:
        if get_type(transaction) == 'in':
            assert False


def test_remove_transactions_by_day():
    transaction_list = []
    test_init(transaction_list)
    remove_transactions_by_day(transaction_list, 14, 14)
    for transaction in transaction_list:
        if get_day(transaction) == 14:
            assert False

    remove_transactions_by_day(transaction_list, 14, 16)
    for transaction in transaction_list:
        if 14 <= get_day(transaction) <= 16:
            assert False


def test_replace_transaction():
    transaction_list = []
    test_init(transaction_list)
    cmd_params = '10 in Salary with 100'
    replace_transaction(transaction_list, cmd_params)
    for transaction in transaction_list:
        if get_day(transaction) == 10 and get_type(transaction) == 'in' and get_description(transaction) == 'Salary':
            if int(get_value(transaction)) != 100:
                assert False


def test_calculate_balance():
    transaction_list = []
    test_init(transaction_list)
    if calculate_balance(transaction_list, 14) != -800:
        assert False


def test_calc_sum():
    transaction_list = []
    test_init(transaction_list)
    if calc_sum(transaction_list, 'in') != 'The sum of all in transactions is 13500':
        assert False


def test_find_the_max():
    transaction_list = []
    test_init(transaction_list)
    cmd_params = 'in 17'
    tokens = cmd_params.split(' ')
    if find_the_max(transaction_list, tokens[0], tokens[1]) != 'The maximum value of the transaction from day 17 with the type in is 4000':
        assert False


def test_filter_transactions_by_type():
    transaction_list = []
    test_init(transaction_list)
    filter_transactions_by_type(transaction_list, 'in')
    for transaction in transaction_list:
        if get_type(transaction) == 'out':
            assert False


def test_filter_transactions_by_type_and_value():
    transaction_list = []
    test_init(transaction_list)
    cmd_params = 'in 2500'
    tokens = cmd_params.split(' ')
    filter_transactions_by_type(transaction_list, tokens)
    for transaction in transaction_list:
        if get_type(transaction) == 'out' or get_value(transaction) >= 2500:
            assert False


# test_add_transaction()
test_split_command()
# test_remove_transactions_by_type()
# test_remove_transactions_by_day()
# test_replace_transaction()
# test_calculate_balance()
# test_calc_sum()
# test_find_the_max()
# test_filter_transactions_by_type()
# test_filter_transactions_by_type_and_value()

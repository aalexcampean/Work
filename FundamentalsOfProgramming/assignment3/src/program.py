#
# Write the implementation for A3 in this file
#

#
# domain section is here (domain = numbers, transactions, expenses, etc.)
# getters / setters
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)
from datetime import datetime


def create_transaction(transaction_day, transaction_value, transaction_type, transaction_description):
    """
    Create student with given parameters
    :param transaction_day: the day the transaction was made on (non-empty)
    :param transaction_value:  the value of the transaction (non-empty)
    :param transaction_type: the type of the transaction (in/out) (non-empty)
    :param transaction_description: the description of the transaction
    :return: Created transaction
    Raise ValueError if transaction cannot be created with given params
    """
    # print(type(student_id)) -> what's my type?
    today = datetime.now().day
    if transaction_day < 1 or transaction_day > 30:
        raise ValueError('The day should be between 1 and 30')
    elif transaction_day > today:
        raise ValueError('The day should be before today or today')
    elif transaction_value < 0:
        raise ValueError('The value should be a positive integer')
    elif transaction_type not in ['in', 'out']:
        raise ValueError('The type should be in or out')
        # return None is implicit
        # return None
        # raise Exception is explicit -> PEP-20
        #  raise ValueError('Cannot create transaction using given arguments')
    return {'day': transaction_day, 'value': transaction_value, 'type': transaction_type, 'description': transaction_description}


# Straightforward getters don't need spec
def get_day(transaction):
    return transaction['day']


def get_value(transaction):
    return transaction['value']


def get_type(transaction):
    return transaction['type']


def get_description(transaction):
    return transaction['description']


# Functionalities section (functions that implement required features)
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)
# Each function does one thing only
# Functions communicate using input parameters and their return values

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
    return ' day: ' + str(get_day(transaction)) + '   value: ' + str(get_value(transaction)) + '   type: ' + get_type(transaction) + '   description: ' + get_description(transaction)


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
    final = []
    ok = False
    i = 0
    while i <= len(transaction_list)-1:
        if typet.lower() == get_type(transaction_list[i]).lower():
            ok = True
            transaction_list.remove(transaction_list[i])
        else:
            i += 1

    final += transaction_list
    if ok:
        return final
    else:
        raise ValueError("There are no such transactions to delete")


def remove_transactions_by_day(transaction_list, left, right):
    """
    This function deletes the all transactions from a given day until another given day,
    it works also just for the transactions of a single given day
    :param transaction_list: the list containing the transactions from this month
    :param left: the day from which the program should delete all transactions
    :param right: the day until which the program should delete all transactions
    """
    final = []
    ok = False
    i = 0
    while i <= len(transaction_list) - 1:
        if left <= get_day(transaction_list[i]) <= right:
            transaction_list.remove(transaction_list[i])
            ok = True
        else:
            i += 1
    final += transaction_list
    if ok:
        return final
    else:
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

# UI section
# (all functions that have input or print statements, or that CALL functions with print / input are  here).
# Ideally, this section should not contain any calculations relevant to program functionalities


#
# DISPLAY FUNCTION
#


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
            display_value_transaction(transaction_list, tokens)
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


def display_value_transaction(transaction_list, tokens):
    """
    This function displays all transaction equal to, greater or smaller than a give value
    :param transaction_list: the list containing the transactions from this month
    :param tokens: the sign so that we know what relation should be established + the given value
    """
    ok = False
    if tokens[0] == '=':
        for transaction in transaction_list:
            if int((tokens[1])) == (get_value(transaction)):
                print(to_str(transaction))
                ok = True
    elif tokens[0] == '>':
        for transaction in transaction_list:
            if (get_value(transaction)) > int((tokens[1])):
                print(to_str(transaction))
                ok = True
    elif tokens[0] == '<':
        for transaction in transaction_list:
            if (get_value(transaction)) < int((tokens[1])):
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
            transaction_list = remove_transactions_by_type(transaction_list, tokens[0])
        except ValueError as ve:
            print(str(ve))
    else:
        if len(tokens) == 1:
            try:
                transaction_list = remove_transactions_by_day(transaction_list, int(tokens[0]), int(tokens[0]))
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
# START FUNCTION
#


def start_command_ui():
    """
    The start function - the one that reads the user's command and executes it accordingly
    """
    # List of transactions in my program
    transaction_list = []
    test_init(transaction_list)
    # These students help me test my program
    # test_init(student_list)
    command_dict = {'list': display_transactions_ui, 'add': add_transaction_command_ui, 'insert': add_transaction_command_ui, 'remove': remove_transactions_ui, 'replace': replace_transaction}
    done = False
    while not done:
        command = input('command> ')
        today = datetime.now().day
        try:
            # 1. split into command_word and command_params
            cmd_word, cmd_params = split_command(command)
            # 2. have separate functions for each command word
            if cmd_word in command_dict:
                if cmd_word == 'add':
                    cmd_params = str(today) + ' ' + cmd_params
                command_dict[cmd_word](transaction_list, cmd_params)
            elif cmd_word == 'exit':
                done = True
            else:
                print('bad command')
        except ValueError as ve:
            print(str(ve))


# Test functions go here
#
# Test functions:
#   - no print / input
#   - great friends with assert

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
    transaction_list.append(create_transaction(17, 3000, 'in', 'Rent 2'))
    transaction_list.append(create_transaction(19, 200, 'out', 'Cash Gog'))
    transaction_list.append(create_transaction(19, 1500, 'in', 'Editing'))
    transaction_list.append(create_transaction(20, 300, 'out', 'Restaurant'))


def test_add_transaction():
    transaction_list = []
    test_init(transaction_list)
    # Test that we can add a valid student
    t = create_transaction(19, 5000, 'in', 'Payment')
    add_transaction(transaction_list, t)
    try:
        add_transaction(transaction_list, t)
        assert False  # this means the exception was NOT raised
    except ValueError:
        assert True   # this means that the test has passed


def test_split_command():
    for cmd in ['insert 10, 5000, in, food', '  INsert   10, 5000, in, food', 'inSERt      10, 50000, in,   food  ']:
        cmd_word, cmd_params = split_command(cmd)
    assert cmd_word == 'insert' and cmd_params == '10, 5000, in, food'

    cmd_word, cmd_params = split_command('exit')
    assert cmd_word == 'exit' and cmd_params == ''


def test_remove_transactions_by_type():
    pass


def test_remove_transactions_by_day():
    pass


def test_replace_transaction():
    pass


def test_calculate_balance():
    pass


# test_init()
# test_split_command()
# test_add_transaction()


start_command_ui()




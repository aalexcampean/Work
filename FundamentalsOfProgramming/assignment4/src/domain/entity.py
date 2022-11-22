"""
Domain file includes code for entity management
entity = number, transaction, expense etc.
"""
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


def get_day(transaction):
    return transaction['day']


def get_value(transaction):
    return transaction['value']


def get_type(transaction):
    return transaction['type']


def get_description(transaction):
    return transaction['description']

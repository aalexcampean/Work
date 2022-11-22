"""
Assemble the program and start the user interface here
"""
from functions.functions import test_init, split_command, replace_transaction
from ui.console import display_transactions_ui, add_transaction_command_ui, \
    remove_transactions_ui, sum_ui, max_ui, filter_function_ui, undo_last_ui
from datetime import datetime


def start_command_ui():
    """
    The start function - the one that reads the user's command and executes it accordingly
    """
    # List of transactions in my program
    transaction_list = []
    test_init(transaction_list)
    history = []
    # These students help me test my program
    # test_init(student_list)
    command_dict = {'list': display_transactions_ui,
                    'add': add_transaction_command_ui,
                    'insert': add_transaction_command_ui,
                    'remove': remove_transactions_ui,
                    'replace': replace_transaction,
                    'sum': sum_ui,
                    'max': max_ui,
                    'filter': filter_function_ui,
                    'undo': undo_last_ui,
                    }
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

                if cmd_word in ['add', 'insert', 'remove', 'replace', 'filter']:
                    history.append(transaction_list.copy())

                if cmd_word == 'undo':
                    try:
                        transaction_list = command_dict[cmd_word](history)
                    except AssertionError as ae:
                        print(str(ae))
                else:
                    command_dict[cmd_word](transaction_list, cmd_params)

            elif cmd_word == 'exit':
                done = True

            else:
                print('bad command')

        except ValueError as ve:
            print(str(ve))


start_command_ui()

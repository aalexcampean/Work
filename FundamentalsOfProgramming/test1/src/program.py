# Source code for Test 1 program. Success!

def create_function(function_name, params, functionality):

    return {'name': function_name, 'parameters': params, 'functionality': functionality}


def get_name(function):
    return function['name']


def get_params(function):
    return function['parameters']


def get_functionality(function):
    return function['functionality']


def split_command(command):
    """
    Split - command string into command word and parameters
    :return: (command_word, command_params)
    """

    command = command.strip()

    tokens = command.split(' ', 1)
    command_word = tokens[0].strip().lower()  # make the command lower cased so that the program executes it regardless
    command_params = tokens[1].strip() if len(tokens) == 2 else ''

    return command_word, command_params       # this functions returns a tuple, so one variable


def to_str(function):
    return str('def ' + get_name(function) + get_params(function) + ': return ' + get_functionality(function))


def add_function_ui(function_list, params):
    """
    This function receives the params given in the command, calls the create function with the split commands
    so that the new function can be created
    After that the newly created function is added to the list of functions
    :param function_list: the list of functions
    :param params: the parameters given with the command
    :return: the new list containing the newly added function
    """
    tokens = params.split('(', 1)
    tokens[1] = '(' + tokens[1]
    name = tokens[0]
    new = tokens[1].split('=')

    params = new[0]
    functionality = new[1]

    function = create_function(name, params, functionality)
    function_list.append(function)


def display_functions_ui(function_list, params):

    tokens = params.split('(', 1)
    name = tokens[0]
    ok = False
    for f in function_list:
        if get_name(f) == name:
            print(to_str(f))
            ok = True

    if not ok:
        raise ValueError('There is no function with the given name')


def evaluate_function_ui(function_list, params):

    tokens = params.split('(', 1)
    name = tokens[0]
    given_params = tokens[1].replace(')', '').split(',')

    for f in function_list:
        if get_name(f) == name:
            execute_function(given_params,get_functionality(f))


def execute_function(given_params, functionality):
    pass



def start_command_ui():
    """
    The start function - the one that reads the user's command and executes it accordingly
    """

    function_list = []

    command_dict = {'add': add_function_ui,
                    'list': display_functions_ui,
                    'eval': evaluate_function_ui
                    }
    done = False
    while not done:
        command = input('command> ')
        try:
            # 1. split into command_word and command_params
            cmd_word, cmd_params = split_command(command)
            # 2. have separate functions for each command word
            if cmd_word in command_dict:

                command_dict[cmd_word](function_list, cmd_params)

            elif cmd_word == 'exit':
                done = True

            else:
                print('bad command')

        except ValueError as ve:
            print(str(ve))

start_command_ui()
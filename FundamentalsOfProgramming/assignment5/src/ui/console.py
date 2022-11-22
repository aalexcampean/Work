"""
    UI class.

    Calls between program modules
    ui -> service -> entity
    ui -> entity
"""
from src.domain.entity import student, studentException
from src.services.service import school
import random


class ui():

    def add_first_students(self):
        """
        Here the student list is populated
        """
        students = []

        lastname = ['Alexandru', 'Maria', 'Sofia', 'Alexandra', 'Serban', 'Darius', 'Anca', 'Iulia',
                    'Lorena', 'Robert', 'Sebastian', 'Hana', 'Razvan', 'Sandra', 'Catalin', 'Teodora']

        surname = ['Campean', 'Gog', 'Pop', 'Popescu', 'Crisan', 'Mihu', 'Gutiu', 'Timis', 'Chetan',
                    'Bob', 'Mitrea', 'Chirtes', 'Maier', 'Gherman', 'Szongott', 'Armasu']

        ids = []
        for i in range(1, 11):
            ids.append(i)

        for i in range(10):

            id_here = random.choice(ids)
            ids.remove(id_here)
            lastname_here = random.choice(lastname)
            surname_here = random.choice(surname)
            name_here = lastname_here + ' ' + surname_here
            group_here = random.randrange(1, 17)
            students.append(student(id_here, name_here, group_here))

        return students

    def __init__(self):
        self._school = school(self.add_first_students())

    def display_all_students(self):
        if len(self._school.get_all) == 0:
            print('There are no students in this school')
        else:
            for s in self._school.get_all:
                print(str(s))

    def print_menu(self):
        print('')
        print('1: Display all students')
        print('2: Add student')
        print('3: Filter list by group')
        print('4: Undo')
        print('0: Exit')

    def start(self):
        """
        Start the UI here
        @return:
        """

        done = False
        while not done:
            self.print_menu()
            x = input('Enter a command: ')

            if x == '1':
                self.display_all_students()

            elif x == '2':
                ida = int(input('Give me an id: '))
                namea = input('Give me a name and surname: ').strip().split(' ', 1)
                first_namea = namea[0].strip()
                last_namea = namea[1].strip()
                namea = first_namea + ' ' + last_namea
                groupa = int(input('Give me a group: '))
                try:
                    self._school.add_student(student(ida, namea, groupa))
                except studentException as st:
                    print(str(st))

            elif x == '3':
                groupf = int(input('Give me a group: '))
                try:
                    self._school.filter_students_by_group(groupf)
                except studentException as st:
                    print(str(st))

            elif x == '4':
                try:
                    self._school.undo()
                except studentException as st:
                    print(str(st))

            elif x == '0':
                done = True
                print('You exited')

            else:
                print('Wrong command!')


program = ui()
program.start()


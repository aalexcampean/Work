"""
    Service class includes functionalities for implementing program features
"""
from src.domain.entity import student, studentException


class school():

    def __init__(self, students):
        """
        Here are defined the instances of the "school" object
        :param students: the list of students
        """
        self._students = students.copy()
        self._history = []

    @property
    def get_all(self):
        return self._students

    def add_student(self, student):
        """
        This function adds new students to the list and also checks if the new student's id is unique
        :param student: the student that needs to be added
        :return: the new list or a student exception if the current student's id is already in the list
        """
        self._history.append(self._students.copy())

        if len(self._students) == 0:
            self._students.append(student)
        else:
            for s in self._students:
                if s.id == student.id:
                    raise studentException('!!! 2 students cannot have the same id !!!')
            self._students.append(student)

    def __len__(self):
        """
        Calculates the length of the object by calculating the length of the list that defines it
        """
        return len(self._students)

    def filter_students_by_group(self, group):
        """
        This function filters the list by a group given by the user
        :param group: the given group by which the list is being filtered
        """
        self._history.append(self._students.copy())

        ok = False
        s = 0
        while s <= len(self._students) - 1:
            if self._students[s].group != group:
                ok = True
                self._students.remove(self._students[s])
            else:
                s += 1

        if not ok:
            raise studentException('!!! The list is already filtered !!!')


    def undo(self):
        """
        This function undoes the last functionality that modified the list of students in the class school
        by always keeping track of the modifications (the list is added to history before each functionality
        that is about to modify it) and when this function is called the last list in history is assigned
        to the current list of students and then deleted form the history
        """
        if len(self._history) > 0:
            self._students = self._history[-1].copy()
            self._history.pop(-1)
        else:
            raise studentException('!!! Cannot undo anymore !!!')

    def len(self):
        return len(self._students)


def test_school():
    students = []
    s = school(students)

    assert len(s) == 0

    s.add_student(student(11, 'Dumbravan Sebastian', 1))
    assert len(s) == 1

    s.add_student(student(12, 'Mitrea Sandra', 1))
    assert len(s) == 2

    try:
        s.add_student(student(13, 'Pop Marian', 1))
    except studentException as st:
        print(str(st))
    assert len(s) == 3

    try:
        s.filter_students_by_group(1)
    except studentException as st:
        print(str(st))

    s.display_all_students()


if __name__ == '__main__':
    test_school()

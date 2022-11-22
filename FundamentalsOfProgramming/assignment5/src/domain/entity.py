"""
    Entity class should be coded here
"""


class studentException(Exception):
    def __init__(self, msg):
        self._msg = msg


class student:

    def __init__(self, id_, name, group):

        if group < 1 or group > 20:
            raise studentException('!!! There are only 20 groups !!!')

        if not isinstance(name, str):
            raise studentException('!!! The second parameter is the name and it must be a string !!!')

        if id_ < 1:
            raise studentException('!!! The id must be greater than 0 !!!')

        self._id = id_
        self._name = name
        self._group = group

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def group(self):
        return self._group

    def __str__(self):
        return str('id: ' + str(self._id) + '  name: ' + self._name + '  group: ' + str(self._group))


def test_student():
    s = student(3, 'Pop Marian', 1)
    assert s.id == 3
    assert s.name == 'Pop Marian'
    assert s._group == 1


if __name__ == '__main__':

    try:
        s1 = student(3, 'Gog Alexandra', 1)
        s2 = student(2, 'Campean Catalin', 1)
        print(str(s1))
        print(str(s2))
    except studentException as st:
        print(str(st))

    test_student()




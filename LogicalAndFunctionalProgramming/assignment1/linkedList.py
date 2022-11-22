class Node:
    def __init__(self, info):
        self.info = info
        self.next = None


class List:
    def __init__(self):
        self.head = None
        

def listCreation():
    my_list = List()
    my_list.head = recursiveListCreation()
    return my_list


def recursiveListCreation():
    value = int(input("value = "))
    if value == 0:
        return None
    else:
        new_node = Node(value)
        new_node.next = recursiveListCreation()
        return new_node
    

def listPrint(given_list):
    recursiveListPrint(given_list.head)


def recursiveListPrint(given_node):
    if given_node is not None:
        print(f'{given_node.info}')
        recursiveListPrint(given_node.next)
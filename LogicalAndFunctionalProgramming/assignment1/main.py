import math
import linkedList

# problem 8
# a. Determine the lowest common multiple of the elements from a list.
# b. Substitute in a list, all occurrence of a value e with a value e1.


# a.

def myGcd(a, b):
    if a == b:
        return a
    elif a > b:
        return myGcd(a-b, b)
    else:
        return myGcd(a, b-a)


def myLcm(given_node):
    if given_node is None:
        return None
    if given_node.next is None:
        return given_node.info
    b = myLcm(given_node.next)
    a = given_node.info
    return abs(a * b) // myGcd(a, b)


def testRequirementA(my_list):
    lcm = myLcm(my_list.head)
    print(f'The lowest common multiple is: {lcm}\n')


# b.

def substituteAllOccurrences(given_node, e, e1):
    if given_node is not None:
        substituteAllOccurrences(given_node.next, e, e1)
        if given_node.info == e:
            given_node.info = e1


def testRequirementB(my_list):
    search_value = int(input("\nsearch_value = "))
    replace_value = int(input("replace_value = "))
    substituteAllOccurrences(my_list.head, search_value, replace_value)

    print('The updated list is: ')
    linkedList.listPrint(my_list)
    print('\n')


if __name__ == '__main__':
    print('--Create a list: ')

    my_list = linkedList.listCreation()
    print('--The created list is: ')
    linkedList.listPrint(my_list)

    print('\n--Menu\n'
          'a. Determine the lowest common multiple of the elements from a list\n'
          'b. Substitute in a list, all occurrence of a value e with a value e\n'
          'c. Exit\n')

    done = True
    while done:
        choice = input('choice = ')
        if choice == 'a':
            testRequirementA(my_list)
        elif choice == 'b':
            testRequirementB(my_list)
        elif choice == 'c':
            done = False
        else:
            print('No such option!')


# 8.
# a. Determine the lowest common multiple of the elements from a list.
# b. Substitute in a list, all occurrence of a value e with a value e1.
#
# a. myGcd(a, b)    = a, if a = b,
# 	                = myGcd(a-b, b), if a > b
#                   = myGcd(a, b-a), otherwise
#
#    myLcm([l1,l2,..,ln])   = [], if n = 0,
#                           = l1, if n = 1,
#                           = l1*myLcm([l2,...,ln])/myGcd(l1,myLcm([l2,...,ln])), otherwise
#
#
#
#
#
# b. substituteAllOccurrences([l1,l2,..,ln], e, e1)     = [], if n = 0,
# 			                                            = e1 U subst([l2..ln], e, e1), if l1 = e,
# 			                                            = l1 U subst([l2..ln], e, e1), otherwise.

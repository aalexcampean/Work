
def gnome_sort_list(my_list, cmp_function):
    """
    This function sorts a given list by using the sorting function
    :param my_list: the given list
    :param cmp_function: the function which the list is sorted by
    :return: the sorted list
    """

    index = 0

    while index < len(my_list):

        if index == 0:
            index = index + 1

        if cmp_function(my_list[index], my_list[index-1]):
            index = index + 1

        else:
            my_list[index], my_list[index - 1] = my_list[index - 1], my_list[index]
            index = index - 1

    return my_list

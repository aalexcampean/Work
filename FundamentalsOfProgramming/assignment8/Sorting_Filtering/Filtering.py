
def filter_list(my_list, flt_function):
    """
    This function filters a given list by using the filtering function
    :param my_list: the given list
    :param flt_function: the function which the list is filtered by
    :return: the filtered list
    """

    l = 0

    while l <= len(my_list) - 1:

        if not flt_function(my_list[l]):
            my_list.pop(l)

        else:
            l += 1

    return my_list

# def backtracking_iterative():
#     k = 0
#     sol = [0]
#     i = 0
#     while k >= 0:
#         while i <= len(coins) - 1:
#             sol[k] = coins[i]
#             if consistent(sol):
#                 if solution(sol):
#                     solutionFound(sol)
#                     i += 1
#                 else:
#
#                     sol.append(0)  # expand candidate solution
#                     k += 1
#             else:
#                 sol.pop()
#                 k -= 1
#         i -= 1
#         sol.pop()
#         k -= 1


# def backtracking_iterative():
#     sol = [0]
#     i = 0
#     while len(sol) > 0:
#         choosed = False
#         while consistent(sol) and i <= len(coins) - 1:
#             sol[-1] = coins[i]
#             choosed = consistent(sol)
#             if choosed:
#                 if solution(sol):
#                     solutionFound(sol)
#                 sol.append(0)  # expand candidate solution
#             else:
#                 sol.pop()
#                 i += 1
#         i -= 1


def backtracking_iterative():
    """
    Backtracking iterative, checks all possible solutions, if a solution is on the good path, it is incremented and
    another element from the given array of money is added, if a valid solution is found it is displayed, otherwise
    the solution vector is decremented, also it is checked if the last element from the initial array is on the last
    position of the vector, if so this means it is either a valid solution and needs to be printed or one that it is not
    and the vector needs to be decremented. Also the newly added value from the initial vector is always the one with
    the index indicated by the last value added to the solution vector + 1
    """
    sol = [0]
    while len(sol) > 0:
        path = False
        while (not path) and coins[sol[-1]] < len(coins) - 1:
            sol[-1] = coins[coins[sol[-1]] + 1]
            path = good_path(sol)
        if path:
            if solution(sol):
                solutionFound(sol)
            sol.append(0)
        else:
            sol.pop()


def compute_sum(sol):
    """
    Computing the sum of the current solution
    """
    sum_here = 0
    for i in sol:
        sum_here += i

    return sum_here


def good_path(sol):
    """
    Checking if the current solution can lead to a valid one
    """
    return compute_sum(sol) <= value


def solution(sol):
    """
    Checking if the current solution is valid
    """
    return compute_sum(sol) == value


def solutionFound(sol):
    """
    Checking if the valid solution just found can be found in the vector with the previous valid solution, if not it is
    printed and added to that vector
    """
    ok = True
    for s in sol_array:
        if len(s) == len(sol):
            ok = False
    if ok:
        sol_array.append(sol[:])
        print(sol)


number_of_coins = int(input("Number of coins: "))
coins = [0]
for i in range(number_of_coins):
    coin = int(input("Give coin value: "))
    coins.append(coin)

value = int(input("Value: "))
sol_array = []
backtracking_iterative()

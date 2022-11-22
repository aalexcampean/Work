# A number of n coins are given, with values of a1, ..., an and a value s.
# Display all payment modalities for the sum s. If no payment modality exists print a message.

# def backtracking_recursive(k, sol):
#     while k <= len(coins) - 1:
#         sol.append(coins[k])
#         if consistent(sol):
#             if solution(sol):
#                 solutionFound(sol)
#             backtracking_recursive(k+1, sol[:])
#         sol.pop()
#         k += 1

def backtracking_recursive(sol):
    """
    Backtracking recursive, goes through all the values in the given vector of coins and appends each one at each step
    the the solution vector. If this vector is on the a good path the it is checked if it is actually solution. After
    that the the function is called again with a copy of the current solution vector as a param. When the initial list
    of values is done, the program comes back to the place where the last function call was made and decrements the
    the current vector and then goes through the for until repeating again the same steps
    """
    for i in coins:
        sol.append(i)
        if good_path(sol):
            if solution(sol):
                solutionFound(sol)
            backtracking_recursive(sol[:])
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
coins = []
for i in range(number_of_coins):
    coin = int(input("Give coin value: "))
    coins.append(coin)

value = int(input("Value: "))
sol_array = []
# backtracking_recursive(0, [])
backtracking_recursive([])
if len(sol_array) == 0:
    print('No possible payment modality')

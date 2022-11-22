#
# Implement the program to solve the problem statement from the first set here
#
# First Problem

# 2. Given natural number `n`, determine the prime numbers `p1` and `p2` such that `n = p1 + p2`
# (check the Goldbach hypothesis).

from math import *


def prime(nr):

    if nr >= 2:
        if nr == 2:
            return 1
        if nr % 2 == 0:
            return 0
        else:
            for x in range(3, int(sqrt(nr)) + 1):
                if nr % x == 0:
                    return 0
            return 1
    else:
        return 0


#Main

n = int(input("give me a value: "))

# Funtion Verification
#if prime(nr) == 0:
#    print("not prime")
#else:
#    print("Prime")

ok = 0
if n < 4:
    print("Give a number greater or equal to 4")
else:
    p2 = n - 2
    while p2 >= n // 2:
        if prime(p2) == 1:
            if prime(n - p2) == 1:
                print(n - p2, ",", p2)
                print(n, " = ", n - p2, " + ", p2)
                ok = 1
                break # This way only the first pair of prime numbers that satisfy the condition are printed
                #break This way all the pairs are printed
        p2 -= 1
    if ok == 0:
        print("This number cannot be wrote as a sum of 2 prime numbers")





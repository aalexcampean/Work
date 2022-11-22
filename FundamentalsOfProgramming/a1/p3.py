#
# Implement the program to solve the problem statement from the third set here
#
# Third Problem

# 14. Determine the n-th element of the sequence 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,...
# obtained from the sequence of natural numbers by replacing composed numbers with their prime divisors,
# each divisor d being written d times, without memorizing the elements of the sequence.

from math import *


def prime(nr):

    if nr >= 2:
        if nr == 2:
            return 1
        if nr % 2 == 0:
            return 0
        else:
            for x in range(3, int(sqrt(nr) + 1)):
                if nr % x == 0:
                    return 0
            return 1
    else:
        return 0


#Main

n = int(input("Give me a value: "))

if n <= 3:
    val = n
else:
    cont = 3
    i = 4
    ok = True
    while ok:
        if prime(i) == 1:
            cont += 1
            if cont == n:
                val = i
                ok = False
        else:
            for j in range(2, i // 2 + 1):
                if i % j == 0:
                    if prime(j) == 1:
                        cont += j
                        if cont >= n:
                            val = j
                            ok = False
                            break
        i += 1
print(val)

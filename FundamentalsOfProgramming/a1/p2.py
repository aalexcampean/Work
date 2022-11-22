#
# Implement the program to solve the problem statement from the second set here
#
# Second Problem

# 9. Consider a given natural number `n`. Determine the product `p` of all the proper factors of `n`.

nr = int(input("give me a natural value: "))
p = 1
prop_fact = []

for x in range(2, nr // 2 + 1):
    if nr % x == 0:
        prop_fact.append(x)
        p *= x

if p == 1:
    print("This number has no proper factors")
else:
    print(prop_fact)
    print(p)

# I also wanted to print the list with all proper factors of the given number

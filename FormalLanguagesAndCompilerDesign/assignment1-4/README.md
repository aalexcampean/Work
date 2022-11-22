# Lab1

Statement: Considering a small programming language (that we shall call mini-langauge), write 3 small programs in this language.

* p1 and p2: compute de max/min of 3 numbers; verify if a number is prime, compute gcd of 2 numbers, compute the solutions for a 2nd order equation, aso
* p3: compute the sum of n numbers, computer the max/min of n numbers


# Lab2

Statement: Considering a small programming language (that we shall call mini-language), you have to write a scanner (lexical analyser)

The minilanguage can be a restricted form of a known programming language, and should contain the following:
* 2 simple data types and a user-defined type
* statements:
    * assignment
    * input/output
    * conditional
    * loop
    * some conditions will be imposed on the way the identifiers and constants can be formed:
* Identifiers: no more than 256 characters
* Constants: corresponding to your types


# Lab3

Statement: Implement the Symbol Table (ST) as the specified data structure, with the corresponding operations

Symbol Table:
* unique for identifiers and constants (create one instance of  ST)

Symbol Table (you need to implement the data structure and required operations) :
* hash table


# Lab4

Statement: Implement a scanner (lexical analyzer): Implement the scanning algorithm and use ST from lab 2 for the symbol table.

* Input: Programs p1/p2/p3/p1err and token.in (see Lab 1a)
* Output: PIF.out, ST.out, message “lexically correct” or “lexical error + location”

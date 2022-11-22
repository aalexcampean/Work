//
// Created by Alex Campean on 14.03.2022.
//

#include <stdio.h>
#include <stdlib.h>

// a. Determine the first (and only) 8 natural numbers (x1, x2, …, x8)
// greater than 2 with the following property:
// all the natural numbers smaller than xi and that are relatively prime with xi (except for the number 1) are prime, i = 1, 2, …, n.

// b. Given a vector of numbers, find the longest contiguous subsequence such that any consecutive elements contain the same digits.


void PrintMenu() {
    // This function prints the menu

    printf("1. Give a vector of numbers\n");
    printf("2. First functionality: Find the first 8 natural numbers having all relative prime numbers, smaller than them, prime\n");
    printf("3. Second functionality\n");
    printf("4. Print vector\n");
    printf("0. Exit\n");
}

int GCD(int number1, int number2) {
    // using sequential subtraction of the smaller number from the greater one will result in their GCD

    // in case of negative numbers, change the numbers to their modulo
    // by using conditional assignment
    number1 = ( number1 > 0) ? number1 : -number2;
    number2 = ( number2 > 0) ? number2 : -number2;

    while(number1 != number2) {
        if(number1 > number2)
            number1 -= number2;
        else
            number2 -= number1;
    }

    return number1;
}

int RelativelyPrime(int number1, int number2) {
    // return 1 if the GCD of the 2 numbers is 1 (they are relatively prime)
    // return 0 otherwise (they are not)

    if (GCD(number1, number2) == 1) {
        return 1;
    }
    return 0;
}

int IsPrime(int number) {
    // checks if a number is prime or not
    //  number = the number in question
    //  return = 1 if the number is prime or 0 otherwise

    if (number < 2) {
        return 0;
    }
    else {
        int x;
        for (x = 2; x <= number / 2; x++) {
            if (number % x == 0){
                return 0;
            }
        }
        return 1;
    }
}

void AllSmallerRelativelyPrime(int number, int *result_vector, int *vector_end) {
    int x = number - 1;
    int index = 0;

    while (x > 1) {
        if (RelativelyPrime(number, x) == 1) {
            result_vector[index] = x;
            index += 1;
        }

        x -= 1;
    }

    *vector_end = index;
}

int CheckPrimePropertyForAll(int *result_vector, int *vector_end) {
    int j;

    for (j = 0; j < *vector_end; j++){
        if (IsPrime(result_vector[j]) == 0) {
            return 0;
        }
    }
    return 1;
}

void PrintSubsequence(int* given_array, int start, int end){
    // This function prints a subsequence from a given array by having given the borders
    // start = the left border
    // end = the right border

    printf("The longest required subsequence is: [");
    for (int j = start; j <= end; j++){

        if (j == end){
            printf("%d", given_array[j]);
        }
        else {
            printf("%d, ", given_array[j]);
        }

    }
    printf("]\n");
}

int HaveSameDigits(int number1, int number2) {
    int frequency_vector[10];
    for (int i = 0; i < 10; ++i) {
        frequency_vector[i] = 0;
    }

    // Count digit frequency of number A
    while (number1 > 0) {
        frequency_vector[number1 % 10] += 1;
        number1 = number1 / 10;
    }

    // Reduce frequency digit of number B
    while (number2 > 0) {
        frequency_vector[number2 % 10] -= 1;
        number2 = number2 / 10;
    }

    for (int i = 0; i < 10; ++i) {
        if (frequency_vector[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void SecondFunc(int nr_2, int array_2[100], int *start, int *end){
    // This function checks for the longest subsequence of a given array in which every 2 elements have their difference
    // a prime number
    //  nr_2 = the number of elements in the given array_2
    //  array_2 = the array_2 in question
    //  return = prints the result

    int first = array_2[0];
    int max = 1;
    int counter = 1;
    int second = 0;
    int pos = 0;
    int i = 1;

    for (i = 1; i <= nr_2 - 1; i++){
        second = array_2[i];

        if (HaveSameDigits(first, second) == 0){

            if (counter > max){
                max = counter;
                pos = i - 1;
            }
            counter = 1;

        }
        else{
            counter += 1;
        }

        first = second;
    }

    if (counter > max){
        max = counter;
        pos = i - 1;
    }

    *start = pos - max + 1;
    *end = *start + max - 1;

}

int main() {
    system("leaks a1_aalexcampean");

    //  used for the first functionality
    int number = 3; // will start from 3 (a smaller number cannot have the given property)

    //  Memory allocation for the vector used in the first functionality
    int *rel_vector;    // will store the pointer to the beginning of the vector with all relatively prime numbers, smaller than the "number"
    rel_vector = (int*)malloc(50 * sizeof(int));
    int i;
    for (i = 0; i < 50; i++){
        rel_vector[i] = NULL;
    }

    int end;    // marks the end of the rel_vector
    int count = 0;  // used to count up to 8 => finding the first and only 8 numbers with the given property

    int n;

    int input_start;
    int input_end;

    int *input_vector;
    input_vector = (int*)malloc(50 * sizeof(int));
    for (i = 0; i < 50; i++){
        input_vector[i] = NULL;
    }

    int input_flag = 0;
    int stop_cond = 0;

    while (stop_cond == 0) {
        int arg;
        PrintMenu();

        printf("What do you want to do?\n");
        scanf("%d", &arg);

        switch(arg) {
            case 0:
                printf("Exiting...!");
                stop_cond = 1;

                //
                free(rel_vector);
                free(input_vector);

                system("leaks a1_aalexcampean");
                break;

            case 1:
                if (input_flag == 0) {
                    printf("Nr of elements in the vector: \n");
                    scanf("%d", &n);

                    printf("The vector: \n");
                    for (i = 0; i < n; i++) {
                        printf("list[%d]: ", i);
                        scanf("%d", &input_vector[i]);
                    }
                    input_flag = 1;
                    break;
                } else {
                    printf("The vector has already been given as input! To give a different one, choose: 0. Exit and start again!\n");
                }
                break;

            case 2:
                printf("The 8 number meeting the requirement are:\n");
                printf("[");
                while (count < 8) {
                    AllSmallerRelativelyPrime(number, rel_vector, &end);
                    if (CheckPrimePropertyForAll(rel_vector, &end) == 1) {
                        if (count < 7) {
                            printf("%d, ", number);
                        } else {
                            printf("%d]", number);
                        }

                        count += 1;
                    }

                    number += 1;
                }
                printf("\n");
                break;

            case 3:
                if (input_flag == 1) {
                    input_start = 0;
                    input_end = 0;

                    SecondFunc(n, input_vector, &input_start, &input_end);
                    PrintSubsequence(input_vector, input_start, input_end);

                } else {
                    printf("Input a vector first!\n");
                }
                break;

            default:
                printf("Error! operator is not correct\n");
        }
    }
}
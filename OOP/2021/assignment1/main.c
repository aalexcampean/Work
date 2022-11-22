#include <stdio.h>
#include <stdlib.h>

// FUNCTIONALITIES

int RecBinarySearch(int left, int right, int nr){
    // This function finds a close int nr to the square root of a real nr
    // left = the left border (0)
    // right = the right border (the given nr)
    // nr = the nr in question
    // return = a close int nr to the square root of the nr in question

    if (left <= right) {

        int mid = (left + right) / 2;

        if (mid * mid == nr) {
            return mid;
        }

        if (mid * mid < nr) {
            return RecBinarySearch(mid+1, right, nr);
        }
        else {
            return RecBinarySearch(left, mid - 1, nr);
        }
    }
    return right;
}

float FirstFunc(float nr_1, int precision){
    // This function computes the square root of a given real nr_1 with a given precision
    //  nr_1 = the nr_1 in question
    //  precision = the precision which the square root is computed with
    //  return = prints the result

    float close = RecBinarySearch(0, nr_1, nr_1);
    float adder = 0.1;

    for (int i = 0; i < precision; i++){
        while (close * close <= nr_1){
            close += adder;
        }

        close -= adder;
        adder /= 10;
    }

    return close;

}

int IsPrime(int nr_prime){
    // This function checks if a numbers is prime or not
    //  nr_prime = the nr_prime in question
    //  return = 1 if the nr_prime is prime or 0 otherwise

    int ok = 1;
    if (nr_prime < 2){
        return 0;
    }
    else{
        for(int x = 2; x <= nr_prime / 2; x++){
            if (nr_prime % x == 0){
                ok = 0;
            }
        }
        return ok;
    }
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

       if (IsPrime(abs(second - first)) == 0){

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

void NewFunc(int nr_3, int array_3[100], int *start, int *end) {
    // This function checks for the longest subsequence of a given array which has only prime numbers
    // nr_3 = the number of elements
    // array_3 = the given array
    // *start = the pointer to the memory location that stores "start"
    // *end = the pointer to the memory location that stores "end"

    int elem;
    int max = 0;
    int counter = 0;
    int pos = 0;
    int i = 0;

    for (i; i <= nr_3 - 1; i++) {
        elem = array_3[i];

        if (IsPrime(elem) == 0) {

            if (counter > max) {
                max = counter;
                pos = i - 1;
            }
            counter = 0;

        } else {
            counter += 1;
        }

    }

    if (counter > max) {
        max = counter;
        pos = i - 1;
    }

    *start = pos - max + 1;
    *end = *start + max - 1;

}

// UI - kinda

void PrintMenu() {
    // This function prints the menu

    printf("1. Give a vector of numbers\n");
    printf("2. First functionality\n");
    printf("3. Second functionality\n");
    printf("4. New functionality\n");
    printf("0. Exit\n");
}

void PrintFloatNumber(float float_nr, int prec){
    // This function prints a given float number with a specific precision
    // float_nr = the number in question
    // prec = the given precision

    printf("The square root with %d precision is:\n", prec);
    printf("%.*f\n", prec, float_nr);
}

void PrintSubsequence(int start, int end, int given_array[100]){
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

// START

int main(){
    int ok = 0;
    int vector = 0;
    while (ok == 0) {
        int n;
        int list[100];

        int arg = 0;
        PrintMenu();
        printf("What do you want to do?\n");
        scanf("%d", &arg);

        if (arg == 1){

            printf("How many elements does your array have?\n");
            scanf("%d", &n);

            printf("Give me the array\n");
            for (int i = 0; i < n; i++) {
                printf("array[%d]: ", i);
                scanf("%d", &list[i]);
            }
            vector = 1;
        }

        else if (arg == 2) {

            float number;
            int precision;
            printf("What is the number whose square root you want to find?\n");
            scanf("%f", &number);

            printf("Now tell me the precision you want the square root to be computed with\n");
            scanf("%d", &precision);

            PrintFloatNumber(FirstFunc(number, precision), precision);

        }

        else if (arg == 3) {
            if (vector == 1) {
                int start_1;
                int end_1;

                SecondFunc(n, list, &start_1, &end_1);
                PrintSubsequence(start_1, end_1, list);
            }
            else {
                printf("First things first you have to give a vector\n\n");
            }

        }

        else if (arg == 4){
            if (vector == 1) {
                int start_2;
                int end_2;

                NewFunc(n, list, &start_2, &end_2);
                PrintSubsequence(start_2, end_2, list);
            }
            else{
                printf("First things first you have to give a vector\n\n");
            }

        }

        else if (arg == 0){
            printf("Bye bye!");
            ok = 1;
        }

        else {
            printf("No such command!\n");
        }

    }
}





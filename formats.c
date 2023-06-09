#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int to_binary(int n) {
    int count = 0;
    int size = 0;
    int temp = n;
    if (n == 0) {
        putchar('0');
        putchar('\n');
        return count;
    }
    while (temp > 0) {
        temp /= 2;
        size++;
    }
    int *binary = malloc(size * sizeof(int));
    if (binary == NULL) {
        return -1;
    }
    for (int i = 0; i < size; i++) {
        binary[size - i - 1] = n % 2;
        n /= 2;
    }
    for (int i = 0; i < size; i++) {
        putchar(binary[i] + '0');
        count++; 
    }
    
    free(binary);
    return count; 

}
#include <stdio.h>

// Function to add two integers
int add(int num1, int num2) {
    return num1 + num2;
}

int main() {
    int result;
    // Adding 10 and 20
    result = add(10, 20);
    printf("The sum is: %d\n", result);
    return 0;
}

// 8. Write a program for data type conversion (int to float, float to int).
#include <stdio.h>

int main()
{
    int intVar = 42;
    float floatVar = 3.14;

    // Convert int to float
    float convertedFloat = (float)intVar;
    printf("Converted int to float: %f\n", convertedFloat);

    // Convert float to int
    int convertedInt = (int)floatVar;
    printf("Converted float to int: %d\n", convertedInt);

    return 0;
}

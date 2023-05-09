#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "getResults.h"



char getResult(char getOperator, int result, int num1, int num2, char output[], char id[])
{

    if (strncmp(&getOperator, "+", 1) == 0)
    {
        result = num1 + num2;
        char str[10];
        sprintf(str, "%d", result);
        strcat(output, id);
        strcat(output, ":");
        strcat(output, str);
    }
    if (strncmp(&getOperator, "*", 1) == 0)
    {
        result = num1 * num2;
        char str[10];
        sprintf(str, "%d", result);
        strcat(output, id);
        strcat(output, ":");
        strcat(output, str);
    }
    if (strncmp(&getOperator, "-", 1) == 0)
    {
        result = num1 - num2;
        char str[10];
        sprintf(str, "%d", result);
        strcat(output, id);
        strcat(output, ":");
        strcat(output, str);
    }
    if (strncmp(&getOperator, "/", 1) == 0)
    {
        result = num1 / num2;
        char str[10];
        sprintf(str, "%d", result);
        strcat(output, id);
        strcat(output, ":");
        strcat(output, str);
    }
    output[strlen(output)] = '\0';
    return *output;
}

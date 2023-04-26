#ifndef __C_GENERIC_KEYWORD_H__
#define __C_GENERIC_KEYWORD_H__

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

// 1st Usage
#define is_compatible(x, T) _Generic((x), T:1, default: 0)


// 2nd Usage
#define cbrt(X) _Generic((X),       \
              long double: cbrtl,   \
                  default: cbrt,    \
                    float: cbrtf    \
)(X)


// 3rd Usage /* Get the name of a type */
#define typename(x) _Generic((x), _Bool: "_Bool", \
    signed char: "signed char", \
    unsigned char: "unsigned char", \
    short int: "short int", \
    unsigned short int: "unsigned short int", \
    int: "int", \
    unsigned int: "unsigned int", \
    long int: "long int", \
    unsigned long int: "unsigned long int", \
    long long int: "long long int", \
    unsigned long long int: "unsigned long long int", \
    float: "float", \
    double: "double", \
    long double: "long double", \
    char *: "pointer to char", \
    void *: "pointer to void", \
    int *: "pointer to int", \
    default: "other")

void test_typename()
{
    size_t s = { 0 };
    ptrdiff_t p = { 0 };
    intmax_t i = { 0 };

    int ai[3] = { 0 };

    printf("size_t is '%s'\n", typename(s));
    printf("ptrdiff_t is '%s'\n", typename(p));
    printf("intmax_t is '%s'\n", typename(i));

    printf("character constant is '%s'\n", typename('0'));
    printf("0x7FFFFFFF is '%s'\n", typename(0x7FFFFFFF));
    printf("0xFFFFFFFF is '%s'\n", typename(0xFFFFFFFF));
    printf("0x7FFFFFFFU is '%s'\n", typename(0x7FFFFFFFU));
    printf("array of int is '%s'\n", typename(ai));
    ai[i] = (int)(s + p);  // For warnings
}

void test_C_GenericKeyword(const char* msg)
{
    printf(msg);
    double x = 8.0;
    const float y = 3.375;
    printf("cbrt(8.0) = %f\n", cbrt(x)); // selects the default cbrt
    printf("cbrtf(3.375) = %f\n", cbrt(y)); // converts const float to float, then selects cbrtf

    test_typename();

    int value = 1;

    if (is_compatible(value, int))
    {
        printf("value = %d, is Integer\n", value);
    }

    if (!is_compatible(value, double))
    {
        printf("value = %d, is Not Double\n", value);
    }
}

#endif //#ifndef __C_GENERIC_KEYWORD_H__
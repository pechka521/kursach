#include "conversion.h"
#include <stdio.h>

fixed_point float_to_fixed(float x)
{
    return (fixed_point)(x * FIXED_SCALE);
}

float fixed_to_float(fixed_point x)
{
    return (float)x / FIXED_SCALE;
}

fixed_point int_to_fixed(int x)
{
    return x << FIXED_SHIFT;
}

int fixed_to_int(fixed_point x)
{
    return (x + (1 << (FIXED_SHIFT - 1))) >> FIXED_SHIFT;
}

void print_fixed_binary(fixed_point x)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (x >> i) & 1);
        if (i == FIXED_SHIFT)
            printf(".");
    }
    printf("\n");
}

void print_fixed_hex(fixed_point x)
{
    printf("0x%08X\n", (unsigned int)x);
}
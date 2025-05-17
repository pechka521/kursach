#include "arithmetic.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

fixed_point fixed_add(fixed_point a, fixed_point b)
{
    fixed_point result = a + b;
    if ((b > 0 && a > MAX - b) || (b < 0 && a < MIN - b))
    {
        fprintf(stderr, "Предупреждение: Возможное переполнение при сложении\n");
    }
    return result;
}

fixed_point fixed_sub(fixed_point a, fixed_point b)
{
    fixed_point result = a - b;
    if ((b > 0 && a < MIN + b) || (b < 0 && a > MAX + b))
    {
        fprintf(stderr, "Предупреждение: Возможное переполнение при вычитании\n");
    }
    return result;
}

fixed_point fixed_mul(fixed_point a, fixed_point b)
{
    int64_t temp = (int64_t)a * b;
    if (temp >= 0)
        temp = temp + (1LL << (FIXED_SHIFT - 1));
    else
        temp = temp - (1LL << (FIXED_SHIFT - 1));
    temp = temp >> FIXED_SHIFT;
    
    if (temp > MAX || temp < MIN)
    {
        fprintf(stderr, "Ошибка: Переполнение при умножении\n");
        if ((a ^ b) < 0)
            return MIN;
        else
            return MAX;
    }
    return (fixed_point)temp;
}

fixed_point fixed_div(fixed_point a, fixed_point b)
{
    if (b == 0)
    {
        fprintf(stderr, "Ошибка: Деление на ноль\n");
        if (a < 0)
            return MIN;
        else
            return MAX;
    }
    
    int64_t temp = ((int64_t)a << FIXED_SHIFT) + llabs(b) / 2;
    return (fixed_point)(temp / b);
}

fixed_point fixed_neg(fixed_point x)
{
    if (x == MIN)
        return MAX;
    else
        return -x;
}

fixed_point fixed_abs(fixed_point x)
{
    if (x == MIN)
        return MAX;
    else if (x < 0)
        return -x;
    else
        return x;
}

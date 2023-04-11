#include <stdio.h>

int subtract(int x, int y)
{
    while (y != 0)
    {
        int borrow = (~x) & y;
        x = x ^ y;
        y = borrow << 1;
    }
    return x;
}

int main()
{
    int x = 29, y = 13;
    printf("x - y is %d", subtract(x, y));
    return 0;
}
#include <stdlib.h>
#include <stdio.h>

long long hi(long long x)
{
    return x >> 32;
}

long long lo(long long x)
{
    return ((1ULL << 32) - 1) & x;
}

int main()
{
    // actually uint32_t would do, but the casting is annoying
    int a;
    scanf("%d", &a);
    printf("%d", a);
    return 0;
}
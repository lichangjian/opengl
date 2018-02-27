#include <stdio.h>

int main()
{
    int a = 0;
    int *b = &a;
    int const *c = b;
    printf("%d\n", *c);
    *b = 2;
    printf("%d\n", *c);
    getchar();
    return 0;
}
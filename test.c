#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    int i = 0;
    char *a = (char *)malloc(sizeof(char) * 2000);
    while (1)
    {
        while (1)
        {
            scanf("%c", &a[i]);
            if (a[i] == '\n')
                break;
            else
                i++;
        }
        a[i] = '\0';
        i = 0;
        if (strlen(a) == 0)
            break;
        printf("%s\n", a);
    }

    return 0;
}
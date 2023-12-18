#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fptr;
    char buf[1000];

    fptr = fopen("input.txt", "r");
    int sum = 0;
    int i = 0;
    while (fgets(buf, 1000, fptr))
    {
        // Print the read data
        printf("[%4d] (%3ld) %s", ++i, strlen(buf), buf);

        int digit1 = 0, digit2 = 0;
        int num = 0;
        for (int i = 0; i < strlen(buf); ++i)
        {
            if (buf[i] >= '0' && buf[i] <= '9')
            {
                digit1 = buf[i] - '0';
                break;
            }
        }
        for (int i = strlen(buf)-1; i >= 0; --i)
        {
            if (buf[i] >= '0' && buf[i] <= '9')
            {
                digit2 = buf[i] - '0';
                break;
            }
        }
        num = (digit1 * 10) + digit2;
        sum += num;
    }

    printf("\n SUM: %d\n", sum);

    return 0;
}

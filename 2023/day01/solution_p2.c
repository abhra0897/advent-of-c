#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *strrstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;
    char *rslt = NULL;
    size_t sz_needle = strlen(needle);
    while(1)
    {
        char *p = strstr(haystack, needle);
        if (!p)
            break;
        rslt = p;
        haystack = p + sz_needle; // p+1 should work just fine but strstr() would need to scan liiiiittle bit longer then
    }
    return rslt;
}

int main(void)
{
    const char *strnums[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    FILE *fptr;
    char buf[1000];

    fptr = fopen("input.txt", "r");
    int sum = 0;
    int i = 0;
    while (fgets(buf, 1000, fptr))
    {
        // Print the read data
//         printf("[%4d] (%3ld) %s", ++i, strlen(buf), buf);
        int first_idx = strlen(buf)-1;
        int last_idx = 0;
        int digit1 = 0, digit2 = 0;
        int num = 0;

        // Find first occurance of number --------------
        for (int k = 0; k < 10; k++)
        {
            char *p = strstr(buf, strnums[k]);
            if (p)
            {
                if ((p - buf) < first_idx)
                {
                    first_idx = (p - buf);
                    digit1 = k; // value at index k of strnums = digit k
                }
            }
        }

        for (int i = 0; i < strlen(buf); ++i)
        {
            if (buf[i] >= '0' && buf[i] <= '9')
            {
                if (i < first_idx)
                {
                    digit1 = buf[i] - '0';
                }
                break;
            }
        }

        // Find last occurance of number --------------
        for (int k = 0; k < 10; k++)
        {
            char *p = strrstr(buf, strnums[k]);
            if (p)
            {
                if ((p - buf) >= last_idx)
                {
                    last_idx = (p - buf);
                    digit2 = k; // value at index k of strnums = digit k
                }
            }
        }

        for (int i = strlen(buf)-1; i >= 0; --i)
        {
            if (buf[i] >= '0' && buf[i] <= '9')
            {
                if (i >= last_idx)
                {
                    digit2 = buf[i] - '0';
                }
                break;
            }
        }
        num = (digit1 * 10) + digit2;
        sum += num;

        printf("[d1: %d] [d2: %d] [num: %2d] %s", digit1, digit2, num, buf);
    }

    printf("\n SUM: %d\n", sum);

    return 0;
}

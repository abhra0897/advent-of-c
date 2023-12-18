#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SETS    20


int count_sets(const char *str, int set_sz[MAX_SETS])
{
    int sets = 0;
    int i = 0;
    int j = 0;
    while (str[i] != ':')
        ++i;
     i += 2; // Skip : and space
    j = i;
    for (; i < strlen(str); i++)
    {
        if (str[i] == ';')
        {
            set_sz[sets] = i - j;
            ++sets;
            i += 2; // Skip ; and space
            j = i;
        }
    }
    set_sz[sets] = (strlen(str) - 1) - j; // -1: Remove last \n
    return (sets+1);
}

void find_color_in_set(char *set, int set_sz, int rgb[3])
{
//     printf("[%.*s]\n", set_sz, set);

    char color_name_str[100];
    char color_val_str[10];
    int i = 0;
    while (i < set_sz)
    {
        int k = 0;
        int j = 0;

        while (set[i] < '0' || set[i] > '9')  ++i;  // Not a number? Screw you
        while (set[i] >= '0' && set[i] <= '9')
        {
            color_val_str[k] = set[i];
            k++;
            i++;
        }
        color_val_str[k] = '\0';

        while (set[i] < 'a' || set[i] > 'z')  ++i;  // Not an alphabet? Screw you
        while (set[i] >= 'a' && set[i] <= 'z')
        {
            color_name_str[j] = set[i];
            j++;
            i++;
        }
        color_name_str[j] = '\0';

        if (strcmp(color_name_str, "red") == 0)
            rgb[0] = atoi(color_val_str);
        else if (strcmp(color_name_str, "green") == 0)
            rgb[1] = atoi(color_val_str);
        else if (strcmp(color_name_str, "blue") == 0)
            rgb[2] = atoi(color_val_str);
    }
}

int main(void)
{
    FILE *fptr;
    char buf[1000];

    int id_sum = 0;
    int id = 0;
    int power_sum = 0;

    fptr = fopen("input.txt", "r");

    while (fgets(buf, 1000, fptr))
    {
        ++id;
        int red_max = 0, green_max = 0, blue_max = 0;
        int sets_size[MAX_SETS] = {0};
        int sets = count_sets(buf, sets_size);
        int i_buf = 0;

        while (buf[i_buf] != ':')
            ++i_buf;
        i_buf += 2;  // Skip : and space

        for (int i = 0; i < sets; i++)
        {
            int rgb[3] = {0};

            find_color_in_set(&buf[i_buf], sets_size[i], rgb);

            if (rgb[0] >= red_max)  red_max = rgb[0];
            if (rgb[1] >= green_max)  green_max = rgb[1];
            if (rgb[2] >= blue_max)  blue_max = rgb[2];

            i_buf += sets_size[i] + 2; // +2: Skip the trailing semicolon and space
        }

//         printf("[R: %2d, G: %2d, B: %2d]  %s", red_max, green_max, blue_max, buf);
        power_sum += (red_max * green_max * blue_max);

    }

    printf("\nID Sum: %d\n", power_sum);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char buf[200] = {0};


int main(void)
{
    FILE *fptr;
    int card_instances[200];
    int total_instances = 0;
    int original_card_cnt = 0;

    for (int i = 0; i < 200; i++)
    {
        // setting all instances count to 1
        card_instances[i] = 1;
    }

    fptr = fopen("input.txt", "r");
    while (fgets(buf, 200, fptr))
    {
        int i_buf = 0;
        char tmp_buf[3];
        int win_nums[100];
        int match_count = 0;
        int win_num_cnt = 0;
        int k = 0;
        int flag_win_num = 1;

        while (buf[i_buf] != ':')
            ++i_buf;
        i_buf += 2;  // Skip : and space

        while (buf[i_buf] != '\0')
        {
            // If we encounter '|', that means next numbers will be "you have" numbers and not "winning numbers"
            if (buf[i_buf] == '|')
                flag_win_num = 0;

            while (buf[i_buf] >= '0' && buf[i_buf] <= '9')
            {
                tmp_buf[k] = buf[i_buf];
                ++k;
                ++i_buf;
            }
            tmp_buf[k] = '\0';
            k = 0;

            if (strlen(tmp_buf))
            {
                // Put winning numbers in an array
                if (flag_win_num)
                {
                    win_nums[win_num_cnt++] = atoi(tmp_buf);
                    printf("[Winning Num: %d]\n", win_nums[win_num_cnt-1]);
                }

                // Now we're reading "you have" numbers. Compare it with winning numbers
                else
                {
                    int have_num = atoi(tmp_buf);
                    printf("[Have Num: %d]\n", have_num);
                    for (int j = 0; j < win_num_cnt; j++)
                    {
                        match_count += (have_num == win_nums[j]);
                    }
                }
            }
            ++i_buf;
        }
        // Set instances number of next cards
        for (int i = 1; i <= match_count; i++)
        {
            if (original_card_cnt+i >= 200)  break;
            card_instances[original_card_cnt+i] += card_instances[original_card_cnt];
        }
        ++original_card_cnt;
    }

    // Sum of all cards
    for (int i = 0; i < original_card_cnt; i++)
    {
        total_instances += card_instances[i];
    }

    printf("\nTotal Instances: %d\n", total_instances);

    return 0;
}

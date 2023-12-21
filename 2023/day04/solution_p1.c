#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char buf[200] = {0};


int main(void)
{
    FILE *fptr;
    int matched_point_sum = 0;


    // Fill the buffer with the text
    fptr = fopen("input.txt", "r");
    while (fgets(buf, 200, fptr))
    {
        int i_buf = 0;
        char tmp_buf[3];
        int win_nums[100];
        int matched_point = 0;
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
//             --i_buf; // cause we'll ++ it at the end of loop
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
                        if (have_num == win_nums[j])
                            matched_point = matched_point ? (matched_point * 2) : 1;
                    }
                }
            }
            ++i_buf;
        }
        matched_point_sum += matched_point;

    }

    printf("\nMatched Points Sum: %d\n", matched_point_sum);

    return 0;
}

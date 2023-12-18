#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROWS    140
#define COLS    142 /* 140 chars, 1 '\n', 1 '\0' */

char buf[ROWS * COLS] = {0};

char get_from_buf(int idx_col, int idx_row)
{
    if (idx_col < 0 || idx_row < 0 || idx_col >= COLS || idx_row >= ROWS )
        return '\0';
    return buf[idx_row * COLS + idx_col];
}

int is_symbol(char c)
{
    if ((c < '0' || c > '9') && c != '.' && c != '\0' && c != '\n')
        return 1;
    else
        return 0;
}

int is_valid_part_num(int idx_start_col, int idx_end_col, int idx_row)
{
    int valid = 0;

    // Check char at left of same row
    if (is_symbol(get_from_buf(idx_start_col-1, idx_row)))
        valid = 1;
    // Check char at right of same row
    else if (is_symbol(get_from_buf(idx_end_col+1, idx_row)))
        valid = 1;
    // Check chars at top and bottom rows
    else
    {
        for (int i = idx_start_col-1; i <= idx_end_col+1; i++)  // idx_start_col-1 and idx_end_col+1 beacuse diagonals are considered too
        {
            if (is_symbol(get_from_buf(i, idx_row-1)) || is_symbol(get_from_buf(i, idx_row+1))) // idx_row-1 for top row, idx_row+1 for bottom row
            {
                valid = 1;
                break;
            }
        }
    }
    return valid;
}

int main(void)
{
    FILE *fptr;
    char strnum[1000];
    int i = 0;
    int j = 0;
    int idx_col = 0, idx_row = 0;
    char *tmp_buf = buf;
    int part_num_sum = 0;

    // Fill the buffer with the text
    fptr = fopen("input.txt", "r");
    while (fgets(tmp_buf, COLS, fptr))
    {
        tmp_buf += COLS;
    }
    tmp_buf = buf;


    // Scan the buffer row-wise and assemble numbers, then look for nearby symbols
    while (idx_row < ROWS)
    {
        if (*tmp_buf >= '0' && *tmp_buf <= '9')
        {
            strnum[i] = *tmp_buf;
            ++i;
        }
        else
        {
            strnum[i] = '\0';
            if (strlen(strnum) > 0)
            {
                int start = idx_col - strlen(strnum);
                int end = idx_col - 1;
                if (is_valid_part_num(start, end, idx_row))
                {
                    part_num_sum += atoi(strnum);
                    printf("   [Start: %3d, End: %3d, Row: %3d] %s\n", start, end, idx_row, strnum);
                }
                else
                {
                    printf("[X][Start: %3d, End: %3d, Row: %3d] %s\n", start, end, idx_row, strnum);
                }
            }
            i = 0;
        }

        if (*tmp_buf == '\0')
        {
            ++idx_row;
            idx_col = 0;
        }
        else
            ++idx_col;
        ++tmp_buf;
    }

    printf("\nPart Number Sum: %d\n", part_num_sum);

    return 0;
}

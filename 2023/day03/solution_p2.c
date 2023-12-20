#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// #define DEBUG

#define ROWS    140
#define COLS    142 /* 140 chars, 1 '\n', 1 '\0' */

char buf[ROWS * COLS] = {0};

void debug_print(const char *fmt, ...)
{
#ifdef DEBUG
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
#endif
}

int scan_adjacent(int *adjacent, int idx_col, int idx_row)
{
    int adj_cnt = 0;
    int i = 0;
    char tmp_buf[10];
    int j = 0;

    int start = 0, end = 0;

    int tmp_idx_col = 0;
    i = idx_row * COLS;

    while(buf[i])
    {
        if (buf[i] >= '0' && buf[i] <= '9')
        {
            tmp_buf[j++] = buf[i];
        }
        else
        {
            tmp_buf[j] = '\0';
            j = 0;
            if (strlen(tmp_buf) > 0)
            {
                start = tmp_idx_col - strlen(tmp_buf);
                end = tmp_idx_col - 1;
                debug_print("    start: %2d, end: %2d, idx_col: %2d, tmp_idx_col: %2d, tmp_buf = %s, \n", start, end, idx_col, tmp_idx_col, tmp_buf);
                if (end == idx_col - 1)
                {
                    adjacent[adj_cnt] = atoi(tmp_buf);
                    ++adj_cnt;
                    // Found left-corner adj, break if there's nothing starting at right-corner
                    if (buf[i+1] < '0' || buf[i+1] > '9')
                        break;
                }
                else if ((start <= idx_col + 1) && end >= idx_col)
                {
                    adjacent[adj_cnt] = atoi(tmp_buf);
                    ++adj_cnt;
                    break; // Found  right-corner or center adj number, there can't be any more adjacents in that row
                }
            }
        }
        ++i;
        ++tmp_idx_col;
    }
    debug_print("    [Cnt: %d]\n", adj_cnt);
    return adj_cnt;
}


int find_gear_ratio(int idx_col, int idx_row)
{
    int adj_cnt = 0;
    int adjacent[6] = {0}; // there can be max of 6 adjacent numbers
    int gear_ratio = 1;


    if (idx_row) // scan top row if there is any top row at all
    {
        debug_print("  TOP\n");
        adj_cnt = scan_adjacent(&adjacent[adj_cnt], idx_col, (idx_row - 1));
    }

    if (idx_row < ROWS - 1) // scan bottom row if there is any bottom row at all
    {
        debug_print("  BOTTOM\n");
        adj_cnt += scan_adjacent(&adjacent[adj_cnt], idx_col, (idx_row + 1));
    }

    debug_print("  SAME\n");
    adj_cnt += scan_adjacent(&adjacent[adj_cnt], idx_col, idx_row); // scan the same row

    // Proceed only if EXACTLY TWO adjacent numbers

    if (adj_cnt == 2)
    {
        for (int i = 0; i < adj_cnt; i++)
        {
            gear_ratio *= adjacent[i];
            debug_print("  %d  ", adjacent[i]);
        }
    }
    else
        gear_ratio = 0;

    if (gear_ratio)
        debug_print("-> GR: %d \n", gear_ratio);

    return gear_ratio;

}


int main(void)
{
    FILE *fptr;
    char strnum[1000];
    int i = 0;
    int j = 0;
    int idx_col = 0, idx_row = 0;
    char *tmp_buf = buf;
    long gear_ratio_sum = 0;

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

        if (*tmp_buf == '*')
        {
            debug_print("Calling find_gear_ratio(%d, %d)\n", idx_col, idx_row);
            int gr = find_gear_ratio(idx_col, idx_row);
            if (gr)
                gear_ratio_sum += (long)gr;
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

    printf("\nGear Ratio Sum: %ld\n", gear_ratio_sum);

    return 0;
}

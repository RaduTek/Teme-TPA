#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// @brief Check if chosen queen column position is good
/// @param n Size of board
/// @param board Pointer to board array
/// @param qrow Row on which last queen is placed
/// @param qcol Column on which last queen is placed
/// @return True if good position, false otherwise
bool check_good_position(int n, int *board, int qrow, int qcol)
{
    for (int col = 0; col < qrow; col++)
    {
        if (board[col] == qcol ||              // check for queen on same column
            board[col] - col == qcol - qrow || // check for queen on main diagonal
            board[col] + col == qcol + qrow)   // check for queen on 2nd diagonal
            return false;
    }
    return true;
}

/// @brief Count the number of valid queen arrangements on an nxn board
/// @param n Size of board
/// @param board Pointer to board array
/// @param row Row index to start on
/// @return Number of valid queen arrangements found
unsigned count_queens(int n, int *board, int row)
{
    if (row == n) // final row, if we reach this point, the position is good
        return 1;

    unsigned count = 0;
    for (int qcol = 0; qcol < n; qcol++)
    {
        // Check if queen can be placed on column
        if (check_good_position(n, board, row, qcol))
        {
            board[row] = qcol;
            count += count_queens(n, board, row + 1);
            board[row] = -1;
        }
    }
    return count;
}

int main()
{
    unsigned n;

    // Get value of n from stdin
    printf("Enter value for n=");
    if (scanf("%u", &n) != 1)
    {
        printf("Invalid input!");
        return -1;
    }

    // allocate array for board
    int *board = malloc(n * sizeof(int));
    if (board == NULL)
    {
        perror("Error");
        return -1;
    }

    // initialize with -1 (= no queen placed)
    for (int i = 0; i < n; i++)
    {
        board[i] = -1;
    }

    unsigned valid_arrangements = count_queens(n, board, 0);

    printf("Number of valid arrangements of %u queens on an %ux%u board found: %u\n", n, n, n, valid_arrangements);

    return 0;
}
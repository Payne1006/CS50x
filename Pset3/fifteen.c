/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

//blank tile variables
int row;
int col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

// user created prototypes
void swap_upper(int tile);
void swap_left(int tile);
void swap_lower(int tile);
void swap_right(int tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();
    
    // initialize location of original blank tile
    row = d - 1;
    col = d - 1;

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(200000);
        }

        // sleep thread for animation's sake
        usleep(200000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int num = (d * d) - 1;

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
                board[i][j] = num;
                num--;
        }
    }
    
    if (d % 2 == 0)
    {
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j =0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                printf(" _  ");
            }
            else
            {
                printf("%2d  ", board[i][j]);
            }
        }   
        printf("\n");
    }
    return;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{

    if (tile >= d * d)
    {
        printf("\nIllegal move.\n");
        usleep(500000);
        return false;
    }
    
    // Blank tile is on bottom row
    if (board[row][col] == board[d - 1][col])
    {
        // Blank tile is on rightmost column
        if (board[row][col] == board[row][d - 1])   
        {   
            // Swap with tile above blank
            if (board[row - 1][col] == tile)
            {
                swap_upper(tile);
                return true;
            }
            // Swap with tile on left of blank
            else if (board[row][col - 1] == tile)
            {
                swap_left(tile);
                return true;
            }
            else
            {
                return false;
            }
        }
        // Blank tile is on leftmost column
        else if (board[row][col] == board[row][0])
        {
            // Swap with tile on right of blank
            if (board[row][col + 1] == tile)
            {
                swap_right(tile);
                return true;
            }
            // Swap with tile above blank
            else if (board[row - 1][col] == tile)
            {
                swap_upper(tile);
                return true;
            }
            else
            {
                return false;
            }
        }
        // Blank tile is within middle columns
        else 
        {
            // Swap with tile on right of blank
            if (board[row][col + 1] == tile)
            {
                swap_right(tile);
                return true;
            }
            // Swap with tile above blank
            else if (board[row - 1][col] == tile)
            {
                swap_upper(tile);
                return true;
            }
            // Swap with tile on left of blank
            else if (board[row][col - 1] == tile)
            {
                swap_left(tile);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    // Blank tile is on top row
    else if (board[row][col] == board[0][col])
    {
         // Blank tile is on rightmost column
        if (board[row][col] == board[row][d - 1])   
        {
            // Swap with tile below blank
            if (board[row + 1][col] == tile)
            {
                swap_lower(tile);
                return true;
            }
            // Swap with tile on left of blank
            else if (board[row][col - 1] == tile)
            {
                swap_left(tile);
                return true;
            }
            else 
            {
                return false;
            }
        }
        // Blank tile is on leftmost column
        else if (board[row][col] == board[row][0])
        {
            // Swap with tile below blank
            if (board[row + 1][col] == tile)
            {
                swap_lower(tile);
                return true;
            }
            // Swap with tile on right of blank
            else if (board[row][col + 1] == tile)
            {
                swap_right(tile);
                return true;
            }
            else
            {
                return false;
            }
        }
        // Blank tile is within middle columns
        else 
        {
            // Swap with tile below blank
            if (board[row + 1][col] == tile)
            {
                swap_lower(tile);
                return true;
            }
            // Swap with tile on right of blank
            else if (board[row][col + 1] == tile)
            {
                swap_right(tile);
                return true;
            }
            // Swap with tile on left of blank
            else if (board[row][col - 1] == tile)
            {
                swap_left(tile);
                return true;
            }
            else 
            {
                return false;
            }
        }
    }
    // Blank is middle rows, on rightmost column
    else if (board[row][col] == board[row][d - 1])   
    {
        // Swap with tile above blank
        if (board[row - 1][col] == tile)
        {
            swap_upper(tile);
            return true;
        }
        // Swap with tile below blank
        else if (board[row + 1][col] == tile)
        {
            swap_lower(tile);
            return true;
        }
        // Swap with tile on left of blank
        else if (board[row][col - 1] == tile)
        {
            swap_left(tile);
            return true;
        }
        else
        {
            return false;
        }
    }
    // Blank is middle rows, on leftmost column
    else if (board[row][col] == board[row][0])
    {
        // Swap with tile above blank
        if (board[row - 1][col] == tile)
        {
            swap_upper(tile);
            return true;
        }
        // Swap with tile below blank
        else if (board[row + 1][col] == tile)
        {
            swap_lower(tile);
            return true;
        }
        // Swap with tile on right of blank
        else if (board[row][col + 1] == tile)
        {
            swap_right(tile);
            return true;
        }
        else
        {
            return false;
        }
    }
    // Blank tile is within middle columns and rows
    else 
    {
        // Swap with tile above blank
        if (board[row - 1][col] == tile)
        {
            swap_upper(tile);
            return true;
        }
        // Swap with tile below blank
        else if (board[row + 1][col] == tile)
        {
            swap_lower(tile);
            return true;
        }
        // Swap with tile of right on blank
        else if (board[row][col + 1] == tile)
        {
            swap_right(tile);
            return true;
        }
        // Swap with tile on left of blank
        else if (board[row][col - 1] == tile)
        {
            swap_left(tile);
            return true;
        }
        else
        {
           return false; 
        }
    }
    return false;
}   

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    /*int i = 0;
    int j = 1;*/
    int count = 1;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == count)
            {
                count++;
            }
            else if (board[i][j] == board[d - 1][d - 1])
            {
                if (board[i][j] == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
            /*if (board[i][j] != count && board[i][j] == board[d - 1][d - 1])
            {               
                if (board[i][j] == 0)
                {
                    return true;
                }
            }
            else if (board[i][j] != count)
            {
                return false;
            }
            else
            {
                return true;
            }*/
    return false;
}

void swap_upper(int tile)
{
    int swap;
    
    swap = tile;
    board[row - 1][col] = board[row][col];
    board[row][col] = swap;
    row -= 1;
}

void swap_left(int tile)
{
    int swap;
    
    swap = tile;
    board[row][col - 1] = board[row][col];
    board[row][col] = swap;
    col -= 1;
}

void swap_lower(int tile)
{
    int swap;
    
    swap = tile;
    board[row + 1][col] = board[row][col];
    board[row][col] = swap;
    row += 1;
    
}

void swap_right(int tile)
{
    int swap;
    
    swap = tile;
    board[row][col + 1] = board[row][col];
    board[row][col] = swap;
    col += 1;
}

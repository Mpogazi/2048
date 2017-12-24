/**********************************************
 *COMP11 Fall 2017
 *Homework 7
 *Fabrice Bigabiro Mpogazi
 **********************************************/
#include <iostream>             
#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;
// change the position of the curson
static const string CSI = "\033["; 

// Constructor for the board class
board::board() 
{
	// attributes of the board class;
	dimen = 0;
	play_board = NULL;
	number = 0;
    first_time = 0;
	position = NULL;
    possible = 0;
    added_numbers = 0;
    tiles_moved = false;

}

// Function that sets the generated number
// parameter: none
// return: nothing
void board::set_number()
{
    int s;
    srand(time(NULL));

    int randomizer = rand() % 10;

    if(randomizer == 0) 
    {
        s = 16;
    } else 
    {
        s = 8;
    }
    number = s;
}

// Function that get the size that the user wants
// parameter: none
// return: nothing
void board::get_user_size() 
{
    int s;
    cout << "Enter the board size: " << endl;
    // checking the board size entered
    while(!(cin >> s) || (s < 2) || (s > 10)) 
    {
        cin.clear();
        cin.ignore(80, '\n');
        cout << "Enter a number btn 2 && 10:" << endl; 
    }
    // Declaring the dimension of the board
    dimen = s;

    play_board = new int *[dimen];

    // Populating the board array
    for(int i = 0; i < dimen; i++)
        play_board[i] = new int[dimen];

    for(int i = 0; i < dimen; i++) 
        for(int j = 0; j < dimen; j++)
            play_board[i][j] = 0;
}

// Function that generates the first two positions of 2
// parameter: none
// return: pointer to an array
int* board::generate_positions()
{
    srand(time(NULL));
    position = new int[4];

    // Generating random positions for the first twos
    do
    {
        for(int i = 0; i < 4; i++) 
        {
            position[i] = rand() % dimen;
        }
    } while(*(position) == *(position + 2) && 
                (*(position + 1) == *(position + 3)));
    return position;
}

// Function that add a new two randomly on the board
// parameter: none
// return: nothing
void board::add_two_onboard() 
{
    // check whether possible to add another number
    bool to_add = false;
    for(int i = 0; i < dimen; i++)
        for(int j = 0; j < dimen; j++)
            if(play_board[i][j] == 0) 
            {
                to_add = true;
                break;
            }
    srand(time(NULL));
    bool not_free = true;
    // Generating the position and making sure it 
    // is at the edges
    do
    {
        int x_coordinate = rand() % dimen;
        int y_coordinate = rand() % dimen;
        int on_edges = x_coordinate * y_coordinate;

        if(play_board[x_coordinate][y_coordinate] == 0 && 
            (on_edges == 0 || x_coordinate == (dimen-1) || 
                y_coordinate == (dimen - 1)))
        {   
            not_free = false;

            if(tiles_moved) 
            {
                play_board[x_coordinate][y_coordinate] = number;   
            }
        }
        else
        {
            not_free = true;
        }

    } while(not_free && to_add);
    tiles_moved = false;
}

// Function that draws input the first two numbers
// parameters: none
// return: nothing 
void board::first_twos() 
{
    // Putting the first two on the play board
    play_board[*(position)][*(position + 1)] = 2;
    play_board[*(position + 2)][*(position + 3)] = 2;
}


// Function that draws the board
// parameter: none
// return: nothing
void board::draw_board()
{
    // Moving the curson for drawing the board
    cout << (CSI + "2J");
    cout << "\033[4;4H";
    cout << "The board: " << endl;
    for(int i = 0; i < dimen; i++)
    {
        for(int j = 0; j < dimen; j++) 
	    {
	        if(play_board[i][j] == 0)
	            cout << internal << setw(6) << '.' << " ";
	        else {
                if((play_board[i][j] / 10) == 0) 
                {
                    // changing the colors
                    cout << "\033[0;35m";
                    cout << internal << setw(6) <<play_board[i][j] << " ";
                    cout << "\033[0;37m";
                } else if((play_board[i][j]/100) == 0)
                {
                    cout << "\033[0;32m";
                    cout << internal << setw(6) <<play_board[i][j] << " ";
                    cout << "\033[0;37m";
                } else if((play_board[i][j] / 1000) == 0) 
                {
                    cout << "\033[0;31m";
                    cout << internal << setw(6) <<play_board[i][j] << " ";
                    cout << "\033[0;37m";
                } else if((play_board[i][j] / 10000) == 0) 
                {
                    cout << "\033[0;33m";
                    cout << internal << setw(6) <<play_board[i][j] << " ";
                    cout << "\033[0;37m";
                } else 
                {
                    cout << "\033[0;34m";
                    cout << internal << setw(6) <<play_board[i][j] << " ";
                    cout << "\033[0;37m";
                }
            }
	    }
        cout << endl << endl;
    }
    // Returning the curson to the initial function
    flush(cout); 
}

// Function to move the tiles to the left
// parameter: none
// returnL nothing
void board::displace_toLeft() 
{
    // Moving the numbers to the left
    for(int i = 0; i < dimen; i++) 
    {
        for(int j = 0; j < dimen; j++) 
        {
            int count = 0;
            while( (play_board[i][j] == 0) && (count < (dimen - j)) ) 
            {
                if(play_board[i][j + count] != 0) 
                {
                    play_board[i][j] = play_board[i][j + count];
                    play_board[i][j + count] = 0;
                    tiles_moved = true;
                    break;
                }
                count++;
            }
        }
    }
}

// Function to move the tiles to the right
// parameter: none
// return: nothing
void board::displace_toRight() 
{
    // Moving the numbers to the right
    for(int i = 0; i < dimen; i++) 
    {
        for(int j = dimen - 1; j > 0; j--) 
        {
            int count = 1;
            while( (play_board[i][j] == 0) && (count < (j+1)) ) 
            {
                if(play_board[i][j - count] != 0) 
                {
                    play_board[i][j] = play_board[i][j - count];
                    play_board[i][j - count] = 0;
                    tiles_moved = true;
                    break;
                }
                count++;
            }
        }
    }
}

// Function to move the tiles to the top
// parameter: none
// return: nothing
void board::displace_toUp() 
{
    // Moving the tiles upward
    for(int j = 0; j < dimen; j++) 
    {
        for(int i = 0; i < dimen; i++) 
        {
            int count = 0;
            while( (play_board[i][j] == 0) && (count < (dimen - i)) ) 
            {
                if(play_board[i + count][j] != 0) 
                {
                    play_board[i][j] = play_board[i + count][j];
                    play_board[i + count][j] = 0;
                    tiles_moved = true;
                    break;
                }
                count++;
            }
        }
    }
}

// Function to move the tiles to the bottom
// parameter: none
// return: nothing 
void board::displace_toBottom() 
{
    // Moving the tiles downward
    for(int j = 0; j < dimen; j++) 
    {
        for(int i = dimen - 1; i > 0; i--) 
        {
            int count = 1;
            while( (play_board[i][j] == 0) && (count < (i+1)) ) 
            {
                if(play_board[i - count][j] != 0) 
                {
                    play_board[i][j] = play_board[i - count][j];
                    play_board[i - count][j] = 0;
                    tiles_moved = true;
                    break;
                }
                count++;
            }
        }
    }
}

// Function that move the numbers to the left
// parameter: none
// return: nothing
void board::move_left()
{
    // Moving the tiles and doing the addition left
    board::displace_toLeft(); 
    for(int i = 0; i < dimen; i++) 
    {
        for(int j = 0; j < dimen; j++) 
        {
            if(play_board[i][j] == play_board[i][j + 1]) 
            {
                play_board[i][j] += play_board[i][j + 1];
                added_numbers += play_board[i][j];
                play_board[i][j + 1] = 0;
            }
        }
    }
    board::displace_toLeft();
}

// Function that move the numbers to the right
// parameter: none
// return: nothing
void board::move_right()
{
    // Moving the tiles and doing the addition to the right
    board::displace_toRight();    
    for(int i = 0; i < dimen; i++) 
    {
        for(int j = dimen - 1; j > 0; j--) 
        {
            if(play_board[i][j] == play_board[i][j - 1]) 
            {
                play_board[i][j] += play_board[i][j - 1];
                added_numbers += play_board[i][j];
                play_board[i][j - 1] = 0;
            }
        }
    }
    board::displace_toRight();
}

// Function to move tiles upward
// parameters: none
// returns: nothing
void board::move_upward()
{
    // Moving the tiles upward and doing the addition
    board::displace_toUp();
    for(int j = 0; j < dimen; j++) 
    {
        for(int i = 0; i < dimen - 1; i++) 
        {
            if(play_board[i][j] == play_board[i + 1][j]) 
            {
                play_board[i][j] += play_board[i + 1][j];
                added_numbers += play_board[i][j];
                play_board[i + 1][j] = 0;
            }
        }
    }
    board::displace_toUp();
}

// Function to move tiles downward
// parameters: none
// returns: nothing
void board::move_downward() 
{
    // Moving the tiles downward and doing the addition
    board::displace_toBottom();
    for(int j = 0; j < dimen; j++) 
    {
        for(int i = dimen - 1; i > 0; i--) 
        {
            if(play_board[i][j] == play_board[i - 1][j]) 
            {
                play_board[i][j] += play_board[i - 1][j];
                added_numbers += play_board[i][j];
                play_board[i - 1][j] = 0;
            }
        }
    }
    board::displace_toBottom();
}

// Function to check whether it's possible to move
// parameters: none
// returns: nothing
bool board::check_possibility() 
{
    // Checking whether there is somewhere to add a number
    for(int i = 0; i < dimen; i++)
        for(int j = 0; j < dimen; j++)
        {
            if(play_board[i][j] == 0)
            {
                return true;
            }
        }
    // Checking for the left and right
    for(int i = 0; i < dimen; i++) 
    {
        for(int j = 0; j < dimen - 1; j++) 
        {
            if(play_board[i][j] == play_board[i][j + 1]) 
            {
                return true;
                break;
            }
        }
    }
    // Checking for upward and downward
    for(int i = 0; i < dimen; i++) 
    {
        for(int j = 0; j < dimen - 1; j++) 
        {
            if(play_board[j][i] == play_board[j + 1][i]) 
            {
                return true;
                break;
            }
        }
    }
    return possible;
}

// Function that returns the added numbers on playboard
// parameter: none
// return int
int board::addition_sum() 
{
    // Added numbers to help finding the scores in the game class
    return added_numbers;
}


// Destructor for releasing all the heap allocated memory
// parameter: none
// return: nothing
board::~board()
{
    for (int i = 0; i < dimen; i++)
    {
        delete [] play_board[i];
    }
    delete []play_board;

    delete []position;
}

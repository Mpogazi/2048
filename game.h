/**********************************************
 *COMP11 Fall 2017
 *Homework 7
 *Fabrice Bigabiro Mpogazi
 **********************************************/
#ifndef GAME_H
#define GAME_H
#include "board.h"

class game
{
private:
    int scores;
    board gaming;
    char user_moves;
    bool game_end;
public:
    // Constructor for the game class
    game();
    // Destructor for the game class
    ~game();
    // Function to start the game
    void start_game();
    // Function to get user move
    char get_user_moves();
    // Function to set user move
    void set_user_moves();
    // Function to execute the move
    void execute_moves();
    // Function to allow quiting
    void quit(); 
    // Function to write the scores
    void write_score(int);
    // Function to show the five top scores
    void show_topscores(); 
};
#endif

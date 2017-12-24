/**********************************************
 *COMP11 Fall 2017
 *Homework 7
 *Fabrice Bigabiro Mpogazi
 **********************************************/
#include "board.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <bits/stdc++.h>

using namespace std;

// Constructor function
// for the game class
game::game() 
{
	board gaming;
	user_moves = ' ';
	game_end = 0;
	scores = 0;

}
// Function to set user move
// parameters: none
// return: nothing
void game::set_user_moves() 
{
	char input;
	// Enabling no-echo through system function 
	system("stty -echo");
	system("stty cbreak");
	do {
		cout << "Choose your moves(w, s, d, a) or q to quit: " <<endl;
		input = getchar();
	} while((input != 'a') && (input != 'w') &&
				(input != 's') && (input != 'd') && 
					(input != 'q') && (input != 'h'));

	// Returning the terminal to initial IO structure
	system("stty echo");
	system("stty -cbreak");

	user_moves = input;
}

// Function to get user move
// parameters: none
// return: character
char game::get_user_moves() 
{
	return user_moves;
}

// Function to start the game
// parameters: none
// return: none
void game::start_game() 
{
	// Calling the gaming object functions 
	// for the game to use the board part
	string player_name;
	gaming.get_user_size();
	gaming.generate_positions();

	gaming.first_twos();
	gaming.draw_board();

	// Looping the recurrent part of the game
	do
	{
		set_user_moves();
		get_user_moves();
		execute_moves();
		if(user_moves == 'h' || user_moves == 0) continue;
		if(user_moves == 0) {
			gaming.draw_board();
			continue;
		}
		scores = gaming.addition_sum();
		gaming.set_number();

		gaming.add_two_onboard();
		gaming.draw_board();

		cout << "Your score is: " << scores << endl;

		// Checking whether we are the end of the game
		game_end = !(gaming.check_possibility());		
	}
	while(!game_end);

	// Writing the scores in a file
	write_score(scores);

	// Ending the game for the loser
	cout << "Thanks for playing!" << endl;
	cout << "Your score is: " << scores << endl;
	cout << "The best: " << endl;

	// Displaying the top scores at end
	show_topscores();
}

// Function to start the game 
// parameters: none
// return: none
void game::execute_moves() 
{
	// Switch statement to allow the user to execute
	// moves
	switch(user_moves) 
	{
		case 'w':
			gaming.move_upward();
			break;

		case 's':
			gaming.move_downward();
			break;

		case 'a':
			gaming.move_left();
			break;

		case 'd':
			gaming.move_right();
			break;

		case 'q':
			write_score(scores);
			show_topscores();
			quit();
			break;

		case 'h':
			cout << "Top scores are: " << endl;
			show_topscores();
			break;

		default:
			user_moves = 0;
			break;
	}
}

// Function to show the five scores
// parameters: none
// return : none
void game::show_topscores() 
{
	// Opening the file to show the top scores
	fstream score_file;

	score_file.open("2048.txt", ios::in);

	string names;
	int scores;
	int count = 0;

	// Looping through the file to get scors
	while(score_file >> names >> scores) 
	{
		cout << names << " " << scores << endl;
		count++;
		if(count == 5)
			break;
	}

	score_file.close();
}

// Function to write the scores on the file
// parameters: none
// return: none
void game::write_score(int high_score) 
{
	// Opening the file to write scores
	fstream score_file;
	score_file.open("2048.txt", ios::in);

	// Checking whether the file is open
	if(score_file.fail()) 
	{
		cout << "Can't record scores!" << endl;
		exit(1);
	}

	cout << "Please fill in your name:  ";
	string player_name;
	cin >> player_name;

	// Declaring a mpa to keep the scores from the file
	map<int, string, greater_equal <int> > scores_names;
	string name;
	int points;

	// Reading the file in variables to store them in map
	while(score_file >> name >> points) 
	{
		scores_names.insert(pair<int, string>(points, name));
	}

	// Keeping the current scores of the player
	scores_names.insert(pair<int, string>(high_score, player_name));

	map<int, string>::iterator it = scores_names.begin();
	score_file.close();

	// Opening the file to write on
	score_file.open("2048.txt", ios::out | ios::trunc);

	for(it = scores_names.begin(); it != scores_names.end(); it++) 
	{
		score_file << it ->second << " " << it ->first << "\n";
	}

	score_file.close();
}

// Function to allow user to quit
// parameters: none
// return: none
void game::quit() 
{
	// Allowing the user to quit the game
	exit(1);
}

// Destructor function 
// for the game class
game::~game() 
{

}

/**********************************************
 *COMP11 Fall 2017
 *Homework 7
 *Fabrice Bigabiro Mpogazi
 **********************************************/
#ifndef BOARD_H
#define BOARD_H

class board
{
private:
	// Attributes of board class
	int dimen;
	// the board
	int **play_board;
	// the new number
	int number;
	// new number position
	int *position;
	// first time to add a new number used
	bool first_time;
	// possibility to move
	bool possible;
	// added numbers
	int added_numbers;
	// bool check whether the tiles moved
	bool tiles_moved;

public:
	// board class constructor
	board();
	// board class destructor
    ~board();
	// Set the added number
	void set_number();
	// setting the board
	void get_user_size();
	//random positions for twos in the board
	int* generate_positions();
	//randomly add another number on the board
	void add_two_onboard();
	// Input the first twos
	void first_twos();
	//function to draw the board
	void draw_board();
	//function to displace tiles to left
	void displace_toLeft();
	//function to displace tiles to right
	void displace_toRight();
	//function to displace tiles to top
	void displace_toUp();
	//function to displace tiles to left
	void displace_toBottom();
	//moving the tiles horizontally left
	void move_left();
	//moving the tiles horizontally right
	void move_right();
	//moving the tiles vertically upward
	void move_upward();
	//moving the tiles vertically downward
	void move_downward();
	//checking whether it's still possible to move anywhere
	bool check_possibility();
	// Returning the added numbers
	int addition_sum();
};
#endif

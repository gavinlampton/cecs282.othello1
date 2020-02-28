#pragma once
#include <array>

// See the project spec for a description of these functions.
// Do NOT modify this file; write your function implementations in 
// OthelloGame.cpp.

// Make sure to #include this file in OthelloGame.cpp

const int BOARD_SIZE = 8;

// A typedef creates an alias for a type (another name we can use).
// std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> is a lot to type, so
// we make an alias "OthelloMatrix" and can use that instead.
typedef std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> OthelloMatrix;

// Print the board to the screen.
void PrintBoard(const OthelloMatrix &board);

// Returns true if row and col are in the bounds of the board.
bool InBounds(int row, int col);

// Returns true if the row and column are in bounds of the board and the square
// is empty, or if the row and column represent a "pass" move. Does not 
// make sure the move actually causes pieces to flip.
bool IsValidMove(const OthelloMatrix &board, int row, int col);

// Uses cin to read a row and column from the user into the two pointers.
void GetMove(int &row, int &col);

// Takes a board, a row and column, and a player, and applies that player's move
// to that position, flipping pieces according to the game rules.
void ApplyMove(OthelloMatrix &board, int row, int col,
	char currentPlayer);

// Returns the sum of the black pieces minus the sum of the white pieces.
int GetValue(const OthelloMatrix &board);
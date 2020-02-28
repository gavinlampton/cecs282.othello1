#include "pch.h"
#include "OthelloGame.h"

#include <string>
#include <iostream>

using namespace std;

void PrintBoard(const OthelloMatrix &board)
{
	cout << '-';

	for (int y = 0; y < BOARD_SIZE + 1; y++)
	{

		if (y > 0)
		{
			cout << y - 1;
		}

		for (int x = 0; x < BOARD_SIZE; x++)
		{

			if (y == 0)
			{
				cout << " " << x;
			}

			else
			{

				if (board.at(y - 1).at(x) == 1)
				{
					cout << " B";
				}

				else if (board.at(y - 1).at(x) == -1)
				{
					cout << " W";
				}

				else
				{
					cout << " .";
				}

			}
		}

		cout << endl;
	}
}

bool InBounds(int row, int col)
{
	return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

bool IsValidMove(const OthelloMatrix &board, int row, int col)
{
	if (row != -1 && col != -1);
	{
		return (InBounds(row, col) && board.at(row).at(col) == 0);
	}

	return true;
}

void GetMove(int &row, int &col)
{
	cin.ignore(256, '(') >> row;
	cin.ignore(256, ',') >> col;
}

//TODO make this flip surrounded pieces.
void ApplyMove(OthelloMatrix &board, int row, int col, char currentPlayer)
{
	array<int, 2> direction{ {0,1} };
	array<int, 2> initial{ {row,col} };
	int counter;

	for (int x = 0; x < 8; x++)
	{
		row = initial.at(0);
		col = initial.at(1);
		counter = 0;

		//It changes direction clockwise every 2 increments.
		if (x / 2 == 1)
		{
			direction = { -1, 0 };
		}
		else if (x / 2 == 2)
		{
			direction = { 0, -1 };
		}
		else if (x / 2 == 3)
		{
			direction = { 1, 0 };
		}

		do //We save a few calls by looping here.
		{
			bool isFlipped = false;
			
			//This checks for in bounds and whether the next tile is enemy.
			while (InBounds(row+direction.at(0),col+direction.at(1)) && board.at(row + direction.at(0)).at(col + direction.at(1)) == -1 * currentPlayer)
			{
				if (isFlipped)
				{
					counter--;
				}
				else
				{
					counter++;
				}

				row += direction.at(0);
				col += direction.at(1);
			}

			if (!InBounds(row, col) || board.at(row).at(col) == 0)
			{
				break;
			}

			isFlipped = true;

			direction.at(0) *= -1;
			direction.at(1) *= -1;

			//We need to decrement here or we get an infinite loop.
			counter--;

		} while (counter > 0);
	}


	board.at(row).at(col) = currentPlayer;
}

int GetValue(const OthelloMatrix &board)
{
	int sum = 0;
	
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			sum += board.at(y).at(x);
		}
	}

	return sum;
}
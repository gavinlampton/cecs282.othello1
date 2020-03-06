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
	return (row==-1&&col==-1)? true : (InBounds(row, col) && board.at(row).at(col) == 0);
}

void GetMove(int &row, int &col)
{
	cin.ignore(256, '(') >> row;
	cin.ignore(256, ',') >> col;
}

void ApplyMove(OthelloMatrix &board, int row, int col, char currentPlayer)
{
	array<int, 2> dir{ {1,1} };
	array<int, 2> initial{ {row,col} };

	board.at(row).at(col) = currentPlayer;

	//One loop for each direction.
	for (int x = 0; x < 8; x++)
	{

		row = initial.at(0);
		col = initial.at(1);

		char outOrIn = 1;

		//It changes direction clockwise every increment.
		if ( ((x / 2) % 2) == 0)
		{
			dir.at(1) += (x/2==0) ? -1 : 1;
		}
		else
		{
			dir.at(0) += (x/2==1) ? -1 : 1;
		}

		//We need to protect the first board check but don't have enough calls to change row/col first or the space to check at the beginning.
		if (InBounds(row + dir.at(0), col + dir.at(1)))
		{
			do //We save a few calls by looping here.
			{
				//This checks for in bounds and whether the next tile is enemy.
				do
				{
					board.at(row).at(col) *= (board.at(row).at(col)==currentPlayer) ? 1 : outOrIn;

					row += dir.at(0);
					col += dir.at(1);

				} while (InBounds(row, col) && board.at(row).at(col) == -1 * currentPlayer);

				outOrIn *= -1;

				dir.at(0) *= (InBounds(row, col) && board.at(row).at(col) == currentPlayer) ? -1 : 1;
				dir.at(1) *= (InBounds(row, col) && board.at(row).at(col) == currentPlayer) ? -1 : 1;

			} while (InBounds(row, col) && board.at(row).at(col) == currentPlayer&&outOrIn==-1);
		}
	}

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
#include "pch.h"
#include "OthelloGame.h"
#include <iostream>
#include <cmath>

using namespace std;

const char BLACK = 1;
const char WHITE = -1;
const char START_TURN = BLACK;

int main()
{
	int row=0;
	int col=0;

	array<bool, 2> hasPassed{ false, false };
	char currentTurn = START_TURN;
	OthelloMatrix board;

	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board.size(); x++)
		{
			board.at(y).at(x) = (x == 3 || x == 4) && (y == 3 || y == 4) ? currentTurn: 0;
			currentTurn *= ((y==3||y==4)&&x==5) ? 1:-1;
		}
	}

	while (!(hasPassed.at(0) && hasPassed.at(1)))
	{
		PrintBoard(board);

		do
		{
			GetMove(row, col);
		} while (!IsValidMove(board, row, col));


		if (InBounds(row, col))
		{
			ApplyMove(board, row, col, currentTurn);
		}
		else
		{
			if (currentTurn == BLACK)
			{
				hasPassed.at(0) = true;
			}
			else
			{
				hasPassed.at(1) = true;
			}
		}

		currentTurn *= -1;
	}

	cout << "Game over.";

	//Simplifies all nonzero numbers to -1 or 1 depending on their sign.
	int negPosOrZero = ~((int)pow(2, sizeof(int)) - 2) & GetValue(board);

	switch (negPosOrZero)
	{
	case(BLACK):
		cout << " Black wins!";
		break;
	case (WHITE):
		cout << " White wins!";
		break;
	case 0:
		cout << " It's a draw!";
		break;
	}

}
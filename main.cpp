#include "pch.h"
#include "OthelloGame.h"
#include <iostream>

using namespace std;

const char BLACK = 1;
const char WHITE = -1;
const char START_TURN = BLACK;

int main()
{

	int row=0;
	int col=0;

	char currentTurn = START_TURN;
	OthelloMatrix board;

	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board.size(); x++)
		{
			board.at(y).at(x) = 0;
		}
	}

	while (!(row == -1 && col == -1))
	{
		PrintBoard(board);

		do
		{
			GetMove(row, col);
		} while (!IsValidMove(board, row, col));

		ApplyMove(board, row, col, currentTurn);
		currentTurn *= -1;
	}

}
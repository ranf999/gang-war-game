#include "Move.h"

Move::Move(GameState currentState, GameState nextState)
{
	//move
	int N = currentState.getBoardSize();
	int index = nextState.getMoveIndex();
	int rowIndex = 0;
	int columnIndex = 0;
	rowIndex = index / N;
	columnIndex = index % N;

	this->row.push_back('1'+ rowIndex);
	this->column.push_back('A'+columnIndex);
	
	if(nextState.getIsRaid()==true)
		this->moveType = "Raid";
	else
		this->moveType = "Stake";
	
	this->boardStates = nextState.getBoard().boardStates;
}

vector<string> Move::toString()
{
	vector<string> fileString;
	string firstLine = "";
	firstLine.append(this->column);
	firstLine.append(this->row);
	firstLine.push_back(' ');
	firstLine.append(this->moveType);
	fileString.push_back(firstLine);
	
	for(int i = 0; i < this->boardStates.size(); i++)
	{
		fileString.push_back(boardStates[i]);
	}
	return fileString;
}

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
	char rowChar[10];
	sprintf(rowChar,"%d",rowIndex+1);
	this->row=rowChar; 
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
	int N = sqrt(this->boardStates.size());
	firstLine.append(this->column);
	firstLine.append(this->row);
	firstLine.push_back(' ');
	firstLine.append(this->moveType);
	fileString.push_back(firstLine);
	
	string line;
	for(unsigned int i = 0; i < this->boardStates.size(); i++)
	{
		line.append(boardStates[i]);
		if(i % N == N-1 )
		{
			fileString.push_back(line);
			line.clear();
		}
	}
	return fileString;
}

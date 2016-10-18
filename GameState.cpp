#include "GameState.h"
#include<set>

using namespace std;

GameState::GameState(vector<string> file)
{  
	Scan scanner;
	this->depth = 0;
	this->whoseTurn = scanner.whoseTurn(file);
	this->board.cellValues = scanner.getCellValues(file);
	this->board.boardStates = scanner.getBoardStates(file);
	this->board.boardSize = scanner.getBoardSize(file);
}

void GameState::setDepth(int depth)
{
	this->depth = depth;
}

int GameState::getBoardSize()
{
	return this->board.boardSize;
}

void GameState::setBoard(Board board)
{
	this->board = board;
}

Board GameState::getBoard()
{
	return this->board;
}

void GameState::setIsRaid(bool isRaid)
{
	this->isRaid = isRaid;
}

bool GameState::getIsRaid()
{
	return this -> isRaid;
}


int GameState::getCellValue(int row, int column)
{
	int num;
	num = row *  this->board.boardSize + column;
	return this->board.cellValues[num];
}

int GameState::getCellValueByIndex(int index)
{
	return this->board.cellValues[index];
}

void GameState::setBoardStateByIndex(int index, string whoseTurn)
{
	this->board.boardStates[index] = whoseTurn;
}

void GameState::setBoardState(int row, int column, string whoseTurn)
{
	int num;
	num = row *  this->board.boardSize + column ;
	this->board.boardStates[num] = whoseTurn;
}

string GameState::getBoardState(int row, int column)
{
	int num;
	num = row *  this->board.boardSize + column;
	return board.boardStates[num];
}

string GameState::getBoardStateByIndex(int index)
{
	return this->board.boardStates[index];
}

void GameState::setWhoseTurn(string whoseTurn)
{
	this->whoseTurn = whoseTurn;
}

string GameState::getWhoseTurn()
{
	return this->whoseTurn;
}

int GameState::getDepth()
{
	return this->depth;
}

void GameState::setValue(int value)
{
	this->value = value;
}

int GameState::getValue()
{
	return this->value; 
}

void GameState::setMoveIndex(int index)
{
	this->moveIndex = index;
}

int GameState::getMoveIndex()
{
	return this->moveIndex;
}


vector<GameState> GameState::getActions(GameState& currentState)
{
	vector<GameState> stateSet;
	int size = currentState.getBoardSize();
	for(int i=0; i < size*size; i++)
	{
		string str = currentState.getBoardStateByIndex(i);
		if(str.compare("X")==0 || str.compare("O")==0)
			continue;
		else
		{
			GameState nextState;
			nextState.setDepth(currentState.getDepth()+1);
	  		if(currentState.getWhoseTurn().compare("X")==0)
				nextState.setWhoseTurn("O");
			else
				nextState.setWhoseTurn("X");
			nextState.setMoveIndex(i);

			//
			nextState.setBoard(currentState.getBoard());
			int row = i / size;
			int column = i % size;  
			nextState.setBoardState (row, column, currentState.getWhoseTurn());
			
			stateSet.push_back(nextState);
			//Raid
			//Next move is in (row,column)
			nextState = raid(nextState, row, column, currentState.getWhoseTurn());
			//nextState.setIsRaid(isRaid);
			if(nextState.isRaid == true)
			{
				stateSet.push_back(nextState);
				//cout<<"Pushing this state!"<<endl;
			}
		}
				
 	}

	return stateSet;
} 

GameState GameState::raid(GameState& state, int row, int column, string whoseTurn)
{  
	//cout<<"BBefore: "<<state.getIsRaid()<<endl;
	string opponent = "";
	int N = state.getBoardSize();
	if(whoseTurn.compare("O")==0)
		opponent.append("X");
	else
		opponent.append("O");
	//judge Raid
	//if there are moves next to the current move, then process Raid 
	int up, down, left, right;
	up = row * N + column - N;
	down = row * N + column + N;
	left = row * N + column - 1;
	right = row * N + column + 1;
	vector<int> nextSquare;
	if(up >= 0)
		nextSquare.push_back(up);
	if(down <= N * N - 1)
		nextSquare.push_back(down);
	if(left % N != N - 1 && left>=0)
		nextSquare.push_back(left);
	if(right % N != 0 && right <= N*N - 1)
		nextSquare.push_back(right);
	bool isRaid = false;
	//left
	for(auto next:nextSquare)
	{
		//cout<<"Before: "<<state.getIsRaid()<<endl;
		if(whoseTurn.compare(state.getBoardStateByIndex(next))==0)
			isRaid = true;
		//cout<<"After : "<<state.getIsRaid()<<endl;
	} 
	bool hasRaid = false;
	if(isRaid == true)
	{
		//cout<<"I think is raid is TRUE!!"<<endl;
		for(auto next:nextSquare)
		{
			if(opponent.compare(state.getBoardStateByIndex(next))==0)
			{
				//cout<<"Going to set raid!"<<endl;
				state.setBoardStateByIndex(next,whoseTurn);
				hasRaid = true;
				state.setIsRaid(true);
				////cout << "setIsRaid:" << state.board.boardStates[8] << endl;
				//system("pause");
	 		}	
	 	}
	} 
	//cout<<"State is raid? "<<state.getIsRaid()<<endl;
	return state;
} 

int GameState::getScoreX()
{
	int scoreX = 0;
	int N = this->board.boardSize;
	for(int i = 0; i < N*N; i++ )
	{
		if(this->board.boardStates[i].compare("X")==0)
		{
			scoreX += this->board.cellValues[i]; 
		}
	}
	return scoreX;
}

int GameState::getScoreO()
{
	int scoreO = 0;
	int N = this->board.boardSize;
	for(int i = 0; i < N*N; i++ )
	{
		if(this->board.boardStates[i].compare("O")==0)
		{
			scoreO += this->board.cellValues[i]; 
		}
	}
	return scoreO;
}

bool GameState::isOver()
{
	bool isOver = true;
	int N = this->board.boardSize;
	for(int i = 0; i < N*N; i++)
	{
		if(this->board.boardStates[i].compare(".")==0)
			isOver = false;
	}
	return isOver;
}



#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "global.h"
#include "Scan.h"

class Board
{	
public:
	int boardSize;
	vector<int> cellValues;
	vector<string> boardStates;
}

class GameState
{
protected:
	Board board;
	string whoseTurn;
	int depth;// current depth
	bool isRaid;
	int value;
	int moveIndex;
public:
	GameState(vector<string> file);
	//void setBoard(Board board);
	Board getBoard();
	int getBoardSize();
	void setDepth(int depth);
	int getDepth();
	void setIsRaid(bool isRaid);
	bool getIsRaid();
	
	int getScoreX();
	int getScoreO();

	void setValue(int value);
	int getValue();

	void setMoveIndex(int index);
	int getMoveIndex();
	// row and column count from 0 to N-
	int getCellValue(int row, int column);
	int getCellValueByIndex(int index);
	void setBoardState(int row, int column, string whoseTurn);
	void setBoardStateByIndex(int index, string whoseTurn);
	string getBoardState(int row, int column);
	string getBoardStateByIndex(int index);

	void setWhoseTurn(string whoseTurn);
	string getWhoseTurn();
	
	GameState getActions(GameState state);
	int getScore(GameState state);
	bool raid(GameState state, int row, int column, string whoseTurn);
	bool isOver();
};
#endif

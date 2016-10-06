#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "global.h"
#include "Scan.h"

class GameState
{
protected:
	vector<int> cellValues;
	vector<string> boardStates;
	string whoseTurn;
	int depths;
	int boardSize;
	string mode;
public:
	GameState(vector<string> file);
	int getCellValue(int row, int column);
	int getboardState(int row, int column);
	string getWhoseTurn();
	int getDepths();
	int getBoardSize();
	string getMode();
	//
	vector<vector<string>> getActions(GameState state);
	bool isOver();
}
#endif

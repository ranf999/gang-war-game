#ifndef _MOVE_H_
#define _MOVE_H_

#include "global.h"
#include "GameState.h"


class Move
{
protected:
	string row;
	string column;
	string moveType;
	vector<string> boardStates;
public:
	Move()
	{}
	Move(GameState currentState, GameState nextState);
	vector<string> toString();
};

#endif

#ifndef _DECISION_H_
#define _DECISION_H_

#include "GameState.h"
#include "Move.h"

class Decision
{
public:
	
	Move makeDecision(GameState state);
	Move minimax(GameState state);
	Move alphaBeta(GameState state);
}

#endif

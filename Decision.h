#ifndef _DECISION_H_
#define _DECISION_H_

#include "GameState.h"
#include "Scan.h"
#include "Move.h"

class Decision
{
protected:
	int depths;
	string mode;
	set<GameState> choices;
public:
	int getDepths();
	string getMode();
	Decision(vector<string> file);
	Move makeDecision(GameState state);
	Move minimax(GameState state);//X is MIN and O is MAX, the score = scoreO-scoreX
	int Max_Value(GameState state);
	int Min_Value(GameState state);
	bool Terminal_Test(GameState state);
	int utility(GameState state);
	
	Move alphaBeta(GameState state);

};

#endif

#include "Decision.h"

Decision::Decision(vector<string> file)
{
	Scan scanner;
	this->depths = scanner.getDepth(file);
	this->mode = sccanner.getMode(file);	
}

int Decision::getDepths()
{
	return this->depths;
}

string Decision::getMode()
{
	return this->mode;
}

Move Decision::makeDecision(GameState state)
{
	string mode = this->mode;
	int depths = this->depths;
	Move nextMove;
	switch(mode[1])
	{
		case "M":
			nextMove = minimax(state);
			break;
		case "A":
			nextMove = alphaBeta(state);
			break;
		default:
			break;
	}
	return nextMove;
}

Move Decision::minimax(GameState state)
{
	Move nextMove;
	int v;
	if(state.getWhoseTurn().compare("O")==0)
		v = Max_Value(state);
	else 
		v = Min_Value(state);
	for(auto move : this->choices)
	{
		if(move.getValue() == v)
			nextMove = Move(state, move);
	}
	return nextMove;
}

int Decision::Max_Value(GameState state)
{
	if(Terminal_Test(state)==true) return utility(state);
    v = -10000;
	set<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		v = max(v,Min_Value(s));
		s.setValue(v);
		if(s.getDepth() == 1)
			this->choices.insert(s);
	}

	return v;	
}

int Decision::Min_Value(GameState state)
{
	if(Terminal_Test(state)==true) return utility(state);
    v = 10000;
	set<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		v = min(v,Max_Value(s));
		s.setValue(v);	
		if(s.getDepth() == 1)
			this->choices.insert(s);
	}
	return v;	
}

bool Decision::Terminal_Test(GameState state)
{
	if(this->depths == state.getDepth()||state.isOver())
		return true;
	else
		return false;
}

int Decision::utility(GameState state)
{
	int scoreX, scoreO;
	scoreX = state.getScoreX();
	scoreO = state.getScoreO();
	return scoreO - scoreX;
}





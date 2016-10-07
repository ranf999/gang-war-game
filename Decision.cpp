#include "Decision.h"
using namespace std;
Decision::Decision(vector<string> file)
{
	Scan scanner;
	this->depths = scanner.getDepth(file);
	this->mode = scanner.getMode(file);	
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
	switch(mode[0])
	{
		case 'M':
			nextMove = minimax(state);
			break;
		case 'A':
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
		if (move.getValue() == v)
		{
			nextMove = Move(state, move);
			return nextMove;
		}
	}
	return nextMove;
} 

int Decision::Max_Value(GameState state)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = -10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		v = max(v,Min_Value(s));
		s.setValue(v);
		if(s.getDepth() == 1)
			this->choices.push_back(s);
	}

	return v;	
}

int Decision::Min_Value(GameState state)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = 10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		v = min(v,Max_Value(s));
		s.setValue(v);	
		if(s.getDepth() == 1)
			this->choices.push_back(s);
	}
	return v;	
}

Move Decision::alphaBeta(GameState state)
{	
	Move nextMove;
	int v;
	if(state.getWhoseTurn().compare("O")==0)
		v = Max_Value(state,-10000,10000);
	else 
		v = Min_Value(state,-10000,10000);
	for(auto move : this->choices)
	{
		if (move.getValue() == v)
		{
			nextMove = Move(state, move);
//			cout << nextMove.toString()[0] << endl;
			return nextMove;
		}
	}
	return nextMove;	
}

int Decision::Max_Value(GameState state, int alpha, int beta)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = -10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		int minValue = Min_Value(s, alpha, beta);
		v = max(v,minValue);
		s.setValue(v);
		if(s.getDepth() == 1)
			this->choices.push_back(s);
		if(v >= beta) return v;
		alpha = max(alpha,v);
	}
	return v;	
}

int Decision::Min_Value(GameState state, int alpha, int beta)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = 10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		int maxValue = Max_Value(s, alpha, beta);
		v = min(v,maxValue);
		s.setValue(maxValue);	
		if(s.getDepth() == 1)
			this->choices.push_back(s);
		if(v <= alpha) return v;
		beta = min(beta,v);
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





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

Move Decision::makeDecision(GameState& state)
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

Move Decision::minimax(GameState& state)
{
	Move nextMove;
	int v;
	if(state.getWhoseTurn().compare("O")==0)
		v = Max_Value(state);
	else 
		v = Min_Value(state);
	for(auto move : this->choices)
	{
		if (move.getValue() == v && move.getIsRaid() == false)
		{
			nextMove = Move(state, move);
			return nextMove;
		}
	}
	for(auto move : this->choices)
	{
		if (move.getValue() == v && move.getIsRaid() == true)
		{
			nextMove = Move(state, move);
			return nextMove;
		}
	}
	return nextMove;
} 

int Decision::Max_Value(GameState& state)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = -10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		int minVal = Min_Value(s);
		v = max(v,minVal);
		s.setValue(minVal);
		if(s.getDepth() == 1)
			this->choices.push_back(s);
	}

	return v;	
}

int Decision::Min_Value(GameState& state)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = 10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		int maxVal = Max_Value(s);
		v = min(v, maxVal);
		//cout<<maxVal<<endl;
		s.setValue(maxVal);
		if(s.getDepth() == 1)
			this->choices.push_back(s);
	}
	return v;	
}

Move Decision::alphaBeta(GameState& state)
{	
	Move nextMove;
	int v;
	vector<int> choiceValue;
	this->choices = state.getActions(state);

	for (int i = 0; i < choices.size(); i++)
	{
		if (choices[i].getWhoseTurn().compare("O") == 0)
			v = Max_Value(choices[i], -10000, 10000);
		else
			v = Min_Value(choices[i], -10000, 10000);
		choiceValue.push_back(v);
		choices[i].setValue(v);
	}
	int min = 10000;
	int max = -10000;
	for (auto val : choiceValue)
	{
		if(val < min)
			min = val;
		if (val > max)
			max = val;
	}
	if (state.getWhoseTurn().compare("X") == 0)
		v = min;
	else
		v = max;

    for(auto move : this->choices)
	{
		if (move.getValue() == v && move.getIsRaid() == false)
		{
			nextMove = Move(state, move);
//			cout << nextMove.toString()[0] << endl;
			return nextMove;
		}
	}
	for(auto move : this->choices)
	{
		if (move.getValue() == v && move.getIsRaid() == true)
		{
			nextMove = Move(state, move);
			return nextMove;
		}
	}
	return nextMove;	
}

int Decision::Max_Value(GameState& state, int alpha, int beta)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = -10000;
	vector<GameState> nextStates = state.getActions(state);
	for(auto s : nextStates)
	{
		int minValue = Min_Value(s, alpha, beta);
		v = max(v,minValue);
		//s.setValue(minValue);
		//s.setValue(10000);
		if(v >= beta) return v;
		alpha = max(alpha,v);

	}
	return v;	
}

int Decision::Min_Value(GameState& state, int alpha, int beta)
{
	if(Terminal_Test(state)==true) return utility(state);
    int v = 10000;
	vector<GameState> nextStates = state.getActions(state);
	GameState move;
	for(auto s : nextStates)
	{
		int maxValue = Max_Value(s, alpha, beta);
		v = min(v,maxValue);
		//s.setValue(10000);	
		if(v <= alpha) return v;
		beta = min(beta,v);
		s.setValue(maxValue);
		//if (s.getDepth() == 1)
		//	this->choices.push_back(s);	
	}
	return v;	
}

bool Decision::Terminal_Test(GameState& state)
{
	if(this->depths == state.getDepth()||state.isOver())
		return true;
	else
		return false;
}

int Decision::utility(GameState& state)
{
	int scoreX, scoreO;
	scoreX = state.getScoreX();
	scoreO = state.getScoreO();
	return scoreO - scoreX;
}





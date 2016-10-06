#include "Scan.h"

int Scan::getBoardSize(vector<string> file)
{
	int size;
	size = atoi(file[0].c_str());
	return size;
}

string getMode(vector<string> file)
{
	string mode;
	mode = file[1];
	return mode;
}

string whoseTurn(vector<string> file)
{
	string whoseTurn;
	whoseTurn = file[2];
	return whoseTurn;
}

int getDepth(vector<string> file)
{
	int depth;
	depth = file[3];
	return depth;
}

vector<int> getCellValues(vector<string> file)
{
	int n = getBoardSize(file);
	vector<int> cellValues;
	string row;
	string num;
	int value;

	for(int i = 0; i < N; i++)	
	{
		row = file[i+4];
		for(int j = 0; j < row.size(); j++)
		{
			if(row[j]!=' ')
				num.push_back(row[i]);
			else if(row[j]==' '&&row[j+1]!=' ')
			{
				value = atoi(num.c_str());
				cellValues.push_back(value);
				num.clear();
			}
		}
		num.clear();
	}
	return cellValues;
}

vector<string> getBoardStates(vector<string> file)
{

	int n = getBoardSize(file);
	vector<string> boardState;
	string row;

	for(int i = 0; i < N; i++)	
	{
		row = file[i+4];
		for(int j = 0; j < row.size(); j++)
		{
			if(row[j]!=' ')
				boardState.push_back(row[i]);
		}
	}
	return boardState;
}


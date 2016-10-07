#include "Scan.h"

int Scan::getBoardSize(vector<string> file)
{
	int size;
	size = atoi(file[0].c_str());
	return size;
}

string Scan::getMode(vector<string> file)
{
	string mode;
	mode = file[1];
	return mode;
}

string Scan::whoseTurn(vector<string> file)
{
	string whoseTurn;
	whoseTurn = file[2];
	return whoseTurn;
}

int Scan::getDepth(vector<string> file)
{
	int depth;
	depth = atoi(file[3].c_str());
	return depth;
}

vector<int> Scan::getCellValues(vector<string> file)
{
	int N = getBoardSize(file);
	vector<int> cellValues;
	string row;
	string num;
	int value;

	for(int i = 0; i < N; i++)	
	{
		row = file[i+4];
		for(unsigned int j = 0; j < row.size(); j++)
		{
			if(row[j]!=' ')
				num.push_back(row[j]);
			else if(row[j]==' '&&row[j+1]!=' ')
			{
				value = atoi(num.c_str());
				cellValues.push_back(value);
				num.clear();
			}
		}
		value = atoi(num.c_str());
		cellValues.push_back(value);
		num.clear();
	}
	return cellValues;
}

vector<string> Scan::getBoardStates(vector<string> file)
{

	int N = getBoardSize(file);
	vector<string> boardState;
	string row;

	for(int i = 0; i < N; i++)	
	{
		row = file[i+4+N];
		for(int j = 0; j < row.size(); j++)
		{
			if(row[j]!=' ')
			{
				string rowStr = "";
				rowStr.push_back(row[j]);
				boardState.push_back(rowStr);
			}
			
		}
	}
	return boardState;
}


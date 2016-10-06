#ifndef _SCAN_H_
#define _SCAN_H_

#include "global.h"
#include "GameState.h"

class Scan
{
public:
	int getBoardSize(vector<string> file);
	string getMode(vector<string> file);
	string whoseTurn(vector<string> file);
	int getDepth(vector<string> file);
	vector<vector<int>> getCellValues(vector<string> file);
	vector<vector<string>> getBoardState(vector<string> file);
};


#endif

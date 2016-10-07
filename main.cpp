#include <iostream>
#include "global.h"
#include "GameState.h"
#include "Move.h"
#include "Decision.h"
#include "FileUtil.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	vector<string> fileStr;
	FileUtil file;
	fileStr = file.loadFile("input.txt");
	GameState startState = GameState(fileStr);
	Decision dc = Decision(fileStr);
	Move nextMove = dc.makeDecision(startState);
	file.writeFile("output.txt",nextMove.toString());
	return 0;
}

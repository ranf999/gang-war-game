#include <iostream>
#include "global.h"
#include "GameState.h"
#include "Move.h"
#include "Decision.h"
#include "FileUtil.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	for(int i = 0; i < 150; i++)
	{
		vector<string> fileStr;
		FileUtil file;
		char inputFile[20];
		char outputFile[20];
		sprintf(inputFile,"sample_%d.txt",i);
		sprintf(outputFile,"output_%d.txt",i);
		fileStr = file.loadFile(inputFile);
		//fileStr = file.loadFile("input.txt");
		GameState startState = GameState(fileStr);
		Decision dc = Decision(fileStr);
		Move nextMove = dc.makeDecision(startState);
		file.writeFile(outputFile,nextMove.toString());
		//	file.writeFile("output.txt",nextMove.toString());
	}
	
	return 0;
}

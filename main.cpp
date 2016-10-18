#include <iostream>
#include "global.h"
#include "GameState.h"
#include "Move.h"
#include "Decision.h"
#include "FileUtil.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	for(int i = 1; i <= 96; i++)
	{
		vector<string> fileStr;
		FileUtil file;
		char inputFile[20];
		char outputFile[20];
		sprintf(inputFile,"./Test%d/input.txt",i);
		sprintf(outputFile,"output%d.txt",i);
		cout<<inputFile<<endl;
		fileStr = file.loadFile(inputFile);
	//	fileStr = file.loadFile(outputFile);
		GameState startState = GameState(fileStr);
		Decision dc = Decision(fileStr);
		Move nextMove = dc.makeDecision(startState);
		file.writeFile(outputFile,nextMove.toString());
		//	cout<<inputFile<<endl;
		//	file.writeFile("output.txt",nextMove.toString());
		
	}
	system("pause");
	return 0;
}

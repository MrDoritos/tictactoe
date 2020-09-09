#include "tictactoeGame.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	int b = 3;
	if (argc > 1) {
		if (sscanf(argv[1], "%i", &b) == 0) {
			b = 3;
		}
	}
	
	tictactoeGame::Game(b);
}


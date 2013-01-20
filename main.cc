#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include "colors.h"
#include "checkers.h"
#include "game.h"

using namespace main_savitch_14;

int main () 
{
	system("clear");
	checkers instance;
	game::who winner;
	winner=instance.play();
	if (winner == game::HUMAN)
		std::cout<<"Player 1 Wins";
	else 
		std::cout<<"Player 2 Wins";

}



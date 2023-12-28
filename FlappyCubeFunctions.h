#pragma once

#include "Includes.h"

void changeBestScore(long long score)
{
	ofstream ofile;

	ofile.open("best score.txt");

	ofile << to_string(score);

	ofile.close();
}
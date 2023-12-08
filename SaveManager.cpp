#include "SaveManager.h"

void saveScore(std::string text) {

	std::ofstream oSavefile("score.txt");
	std::ifstream iSavefile("score.txt");
	std::string currentLine;
	if (oSavefile.is_open()) {
		oSavefile << text;
		oSavefile.close();
		//std::cout << "information written\n";
	}
	else std::cout << "Unable to open file 'savedData/score.txt\n'";
}
int readHighscore() {
	std::ifstream iSavefile("score.txt");
	std::string currentLine;
	int score = 0;

	if (iSavefile.is_open()) {
		std::getline(iSavefile, currentLine);
		if (currentLine != "")
		{
			score = stoi(currentLine);
		}

		iSavefile.close();
	}
	else std::cout << "Unable to open file 'savedData/score.txt\n'";

	std::cout << score << std::endl;
	return score;
}
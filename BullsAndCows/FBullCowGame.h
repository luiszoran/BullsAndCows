#pragma once
#include <string>

class FBullCowGame {
public:
	void Reset(); // TODO change return type
	int GetMaxTries();
	int GetCurrentTry();
	bool IsGameWon();
	bool CheckGuessValidity(std::string);

	
private:
	int MyCurrentTry;
	int MyMaxTries;
};
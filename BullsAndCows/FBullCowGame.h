/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

// Unreal friendly sintax
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	int32 GetMaxTries() const;

	EGuessStatus CheckGuessValidity(FString) const;

	int32 GetMinWordLength() const;
	int32 GetMaxWordLength() const;
	FString GetRandomWord(int32) const;
	void Reset(FString);
	FBullCowCount SubmitValidGuess(FString);

	
private:
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	int32 MinWordLength;
	int32 MaxWordLength;
};
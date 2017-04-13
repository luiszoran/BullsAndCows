#include "FBullCowGame.h"
#include <map>
#include <vector>

// Unreal friendly sintax
#define TMap std::map

FBullCowGame::FBullCowGame() {
	Reset("");
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

int32 FBullCowGame::GetMinWordLength() const
{
	return MinWordLength;
}

int32 FBullCowGame::GetMaxWordLength() const
{
	return MaxWordLength;
}

bool FBullCowGame::IsGameWon() const {
	return bIsGameWon;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) return false;
	}
	return true;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

FString FBullCowGame::GetRandomWord(int32 length) const {
	std::vector<FString> threeLetterWord = { "and", "two" };
	std::vector<FString> fourLetterWord = { "word", "cash" };
	std::vector<FString> fiveLetterWord = { "jumpy", "brick" };
	std::vector<FString> sixLetterWord = { "dwarfs", "drying" };
	std::vector<FString> sevenLetterWord = { "dumbing", "abdomen" };
	TMap<int32, std::vector<FString>> WordLengthToMaxTries { { 3, threeLetterWord }, { 4, fourLetterWord }, { 5, fiveLetterWord }, { 6, sixLetterWord }, { 7, sevenLetterWord }};
	FString Word = WordLengthToMaxTries[length][0 + (rand() % (int)(1 - 0 + 1))];
	return Word;
}

void FBullCowGame::Reset(FString Word) {
	MyHiddenWord = Word;
	const int32 MIN_LENGTH = 3;
	MinWordLength = MIN_LENGTH;
	const int32 MAX_LENGTH = 7;
	MaxWordLength = MAX_LENGTH;
	bIsGameWon = false;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (MyHiddenWord[MHWChar] == Guess[GChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	} else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) return true;

	TMap<char,bool> LetterSeen;
	for (auto Letter : Word){
		Letter = tolower(Letter);
		if(LetterSeen[Letter] == true){
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

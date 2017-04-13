/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic see the FBullCowgame cass.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// To introduce functions
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
int32 ChooseWordLength();

// Game instance
FBullCowGame BCGame;

// Entry point of application
int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
/*	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";*/
	return;
}

// plays a single game
void PlayGame() {

	int32 WordLength = ChooseWordLength();
	FString Word = BCGame.GetRandomWord(WordLength);
	BCGame.Reset(Word);
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows  = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'Y' || Response[0] == 'y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon() == true) {
		std::cout << "Well done, you won.\n";
	}
	else {
		std::cout << "You lost, bad luck.\n\n";
	}
}

int32 ChooseWordLength() {
	FText Response = "";
	int32 length;
	while (true) {
		try {
			std::cout << "How many letters should the isogram be made of (" << BCGame.GetMinWordLength() << "-" << BCGame.GetMaxWordLength() << ")? ";
			getline(std::cin, Response);
			length = std::stoi(Response);
			if (length < BCGame.GetMinWordLength() || length > BCGame.GetMaxWordLength()) {
				std::cout << "Enter a number between " << BCGame.GetMinWordLength() << " and " << BCGame.GetMaxWordLength() << ".\n";
			} else {
				break;
			}
		} catch (const std::invalid_argument& ia) {
			std::cout << "Enter a number.\n";
		}
	}
	return length;
}

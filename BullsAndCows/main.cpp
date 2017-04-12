#include <iostream>
#include <string>


void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

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
	constexpr int WORLD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORLD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

std::string GetGuess(){
	std::cout << "Enter your guess: ";
	std::string Guess = "";
	getline(std::cin, Guess);
	return Guess;
}

void PlayGame()
{
	constexpr int NUMBEER_OF_TURNS = 5;
	for (int i = 0; i < NUMBEER_OF_TURNS; i++) {
		std::string Guess = GetGuess();
		std::cout << "Your guess: " << Guess << "\n";
		std::cout << std::endl;
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	std::string Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y');
}

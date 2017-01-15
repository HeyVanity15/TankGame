/*
This is the console executable, that makes use of the BullCow class.
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "main.h"
#include "FBullCowGame.h"

// aliasing types
using FText = std::string;
using int32 = int;

// Prototypes : These will usually go into the header file
void PrintIntro();
FText GetValidGuess();
void PrintBack(FText);
bool AskToPlayAgain();
void PrintGameSummary(bool);

// This declares and instantiates the object via constructor
FBullCowGame bCGame;

// The entry-point for the application
int main()
{
	bool bWantsToPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bWantsToPlayAgain = AskToPlayAgain();
	} while (bWantsToPlayAgain);

	std::cout << std::endl;
	return 0;
}

void PrintIntro()
{
	constexpr int WORD_LENGTH = 5;
	// std::endl is the same as \n but flushes the output buffer
	std::cout << "Welcome to Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << bCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	bCGame.Reset();
	int32 maxTries = bCGame.GetMaxTries();

	// TODO change from FOR to WHILE loop once we are validating tries
	while (!bCGame.IsGameWon() && bCGame.GetCurrentTry() <= maxTries)
	{
		FText guessWord = GetValidGuess(); 
		// Submit valid guess to the game
		FBullCowCount BullCowCount = bCGame.SubmitValidGuess(guessWord);
		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}

	PrintGameSummary(bCGame.IsGameWon());
}

// loop continually until the user gives a valid guess
FText GetValidGuess() // TODO make loop checking valid
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText guessWord = "";

	do {
		// get a guess from the player
		int32 tryNum = bCGame.GetCurrentTry();
		std::cout << "Try " << tryNum++ << ". Enter your guess: ";
		std::getline(std::cin, guessWord);

		Status = bCGame.CheckGuessValidity(guessWord);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << bCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters." << std::endl;
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);

	return guessWord;
}

bool AskToPlayAgain()
{
	FText answer = "";
	bool playAgain = false;
	std::cout << "Would you like to play again (y/n)? ";
	std::getline(std::cin, answer);
	std::cout << std::endl;
	return answer == "yes" || answer == "y";
}

void PrintGameSummary(bool IsGameWon)
{
	if (IsGameWon)
	{
		std::cout << "YOU WON! CONGRATULATIONS!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	std::cout << std::endl;
}

// "#" is a pre-processor directive and is used to import libraries
// "< ... >" to reference .NET system libraries
// quotes to reference personal libraries
// "using" so we don't have to qualify namespace before accessing members (just like C#)
// "::" to access namespace/class members
// "<<" overloaded operator?
//     in C++, values can be assigned from the left or right.
//     the >> operater will point to the assignee
// constexpr is used for compile-time constants
// const is used as an access modifier for getters and provides run-time constants
// std::cout and std::cin are used for console io streams
// std::getline(input, variable) gets input from line, including whitespace
// .h files are header files that contain class/method contracts
// try not to use "using namespace" because namespace conflicts can occur

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// Do not trust the compiler
// Rebuild after changing initialized members

// use enum class to limit scope and avoid redefining enum values when defining other enums
enum class EGuessStatus {
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	// constructor
	FBullCowGame();

	// member methods
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	FBullCowCount SubmitValidGuess(FString);
	bool IsIsogram(FString);

private:
	// fields
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsGameWon;

	// private methods
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};

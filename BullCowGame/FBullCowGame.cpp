#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guessWord) const
{
	// be careful with implicit dependencies
	// one method call should not depend on one running before it

	if (guessWord.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (IsLowerCase(guessWord))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (!IsIsogram(guessWord))
	{
		return EGuessStatus::Not_Isogram;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guessWord)
{
	MyCurrentTry++;
	FBullCowCount bullCowCount;
	int WordLength = GetHiddenWordLength();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (guessWord[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					bullCowCount.Bulls++;
				}
				else
				{
					bullCowCount.Cows++;
				}
			}
		}
	}

	if (WordLength == bullCowCount.Bulls)
	{
		bIsGameWon = true;
	}

	return bullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// OPTIONS:
		// 1) perform O(n^2) comparison
		// 2) perform O(n log(n)) sort
			// + O(n) loop through each character comparing it to the next
		// 3) use hashset for O(n)

	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}
	
	// a map is used in the example but a hashset would be better
	TMap<char, bool> SeenLetters;

	// loop through all the letters of the word
		// if the letter is in the map
			// we do NOT have an isogram
		// otherwise
			// add the letter to the map as seen
	for (auto Letter : Word)
	{
		if (SeenLetters[Letter])
		{
			return false;
		}
		else
		{
			SeenLetters[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}

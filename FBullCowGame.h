/*
	the game logic (no view code or direct user interaction)
	BullCowGame is a guess the word game, where the player 
	guesses the isogram.
	(isogram is a word with no repeating letters)
*/

#pragma once
#include <string>

/* using unreal syntax */
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus 
{
	Invalid_Guess,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullCowGame 
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const; 

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for inistialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool  bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};

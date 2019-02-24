#pragma once

#include "FBullCowGame.h"
#include <map>

/* using unreal syntax */
#define TMap std::map 
using FString = std::string;
using int32 = int;

/* default contructor */
FBullCowGame::FBullCowGame() { Reset(); }

/* getters */
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

/*  
	gets the maximum number of tries based 
	on the length of the hidden word
*/
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxtries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxtries[MyHiddenWord.length()];
}

/* Resets the game to default values */
void FBullCowGame::Reset()
{
	bGameIsWon = false;

	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
}

/* 
	checks the validity of the users guess by checking if it is an isogram, 
	if all the letters are lower case and if the length of the guess 
	matches the length of the hidden word
*/
EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) 
	{
		return EWordStatus::Not_LowerCase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OK;
	}
}

/*  
	revieces a VALID guess, increments turn, and returns count
	of bulls and cows.
*/
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) 
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the guess
	for (int32 i = 0; i < WordLength; i++) 
	{
		// compare letters against the hidden word
		for (int32 j = 0; j < WordLength; j++) 
		{
			if(Guess[j] == MyHiddenWord[i])
			{
				if (i == j) 
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	/*	if bulls or the number of corectly 
		guest leters matches the length of 
		the word then the game is won otherwise it isn't
	*/
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

/* Checks if the word is an isogram */
bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 0) { return true; }
	
	TMap<char, bool> LetterSeen;	
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

/* Checks if the word is an isogram */
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (Letter != tolower(Letter))
		{
			return false;
		}
	}
	return true;
}

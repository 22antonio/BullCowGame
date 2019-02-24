/* This is the console executable, that makes use of the BullCow class
   This acts as the view in a MVC pattern, and is resonsible for all 
   user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

/* using unreal syntax */
using FText = std::string;
using int32 = int;

/* function protypes */
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

/* instantiate a new game */
FBullCowGame BCGame;

int32 main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (!bPlayAgain);

	return 0;
}

void PrintIntro() 
{

	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	/*
	std::cout << << std::endl;
	std::cout << << std::endl;
	std::cout << << std::endl;
	std::cout << << std::endl; ascii art will go here
	std::cout << << std::endl;
	std::cout << << std::endl;
	*/
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";

}

/* plays a single game to completion */
void PlayGame() 
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns specified and ask for guesses
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText guess = GetValidGuess();

		// Submit valid guess to the game, and revcieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	} 

	PrintGameSummary();
}

/* Gets a guess from the player and checks for invalid inputs */
FText GetValidGuess() 
{
	int32 CurrentTry = BCGame.GetCurrentTry();

	FText guess = "";
	EWordStatus Status = EWordStatus::Invalid_Guess;
	do {
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() << " Enter your guess: ";
		getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a word with " << BCGame.GetHiddenWordLength() << " letters\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "There can be no repeating letters\n\n";
			break;
		case EWordStatus::Not_LowerCase:
			std::cout << "All letters have to be lowercase\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EWordStatus::OK);
	return guess;
}

/* asks the player to play again and checks for valid response */
bool AskToPlayAgain() 
{
	std::cout << "\nWould you like to play again with the same word? (y/n) \n";
	FText Response = "";
	getline(std::cin, Response);

	if (Response == "y" || Response == "Y") 
	{
		return false;
	}
	else if (Response == "n" || Response == "N") 
	{
		return true;
	}
	else 
	{
		std::cout << "Please enter a valid choice \n";
		AskToPlayAgain();
	}

}

/* checks if game is won and prints appropriate summary */
void PrintGameSummary() {
	if (BCGame.IsGameWon()) 
	{
		std::cout << "You WIN!!\n";
	}
	else
	{
		std::cout << "Better luck next time.\n";
	}
}

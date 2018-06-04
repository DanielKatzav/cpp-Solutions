#include <iostream>
#include <string>
#include "FBullCowGame.h"


using std::cout;
using std::cin;
using std::string;
using std::endl;
using FText = std::string;
using int32 = int;

void printintro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary(bool);

FBullCowGame BCGame;

int main()
{
	bool again;

	do 
	{
		printintro();
		PlayGame();
		again = AskToPlayAgain();
	} while (again);


	return 0;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	FBullCowCount BullCowCount;
	bool GameEnds;
	do {
		FText Guess = GetValidGuess();

		BullCowCount = BCGame.SubmitValidGuess(Guess);
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << "\tCows = " << BullCowCount.Cows << endl;
		GameEnds = BCGame.IsGameWon(BullCowCount.Bulls);
	} while (!GameEnds && BCGame.GetCurrentTry() <= MaxTries);

	PrintGameSummary(GameEnds);

	return;
}

void printintro()
{
	// Introduce the game
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n\n";
	return;
}

FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

	int32 CurrentTry = BCGame.GetCurrentTry();
	// get a guess from the player
	cout << "Try " << CurrentTry << ". Enter your guess : \n";
	std::getline(cin, Guess);

	// Validation for Guess
	
		Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			cout << "\nPlease enter a " << BCGame.GetHiddenWordLength() << " letter word" << endl;
			break;
		case EGuessStatus::Not_Isogram:
			cout << "\nPlease enter a valid Isogram word !" << endl;
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "\nPlease enter an Isogram word with all Lowercase Letters !" << endl;
			break;
		default:
			break;
		}
		cout << endl;
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors

	return Guess;
	
}

bool AskToPlayAgain()
{
	FText choice = "";

	cout << "Do you want to play again ? (y/n)\n";
	std::getline(cin, choice);

	return (choice[0] == 'y') || (choice[0] == 'Y');

}

void PrintGameSummary(bool GameEnds)
{	
	if (GameEnds)
		cout << "\nYou won !! \n\n";
	else
		cout << "\nBetter Luck next time !\n\n";
	return;
}
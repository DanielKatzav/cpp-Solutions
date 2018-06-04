#include "FbullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getters

int32 FBullCowGame::GetMaxTries() const {	return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}


// Functions

void FBullCowGame::Reset()
{
	constexpr int32 MY_MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	MyCurrentTry = 1;
	MyMaxTries = MY_MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	return;
}
bool FBullCowGame::IsGameWon(int32 Bulls) 
{
	if (Bulls == GetHiddenWordLength())
		return true;
	else
		return false;
}


EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess)) // Is the Guess an valid Isogram ?
	{
		return EGuessStatus::Not_Isogram;
		// return Error
	}
	else if (!IsLowercase(Guess)) // If the Guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // If the guess isn't within the same length of the HiddenWord
	{
		return EGuessStatus::Wrong_Length;
	}
	else
		return EGuessStatus::OK; // TODO Make Real Error
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();

	for (int32 i = 0; i < WordLength; i++)
	{
		char HiddenWordChar = MyHiddenWord[i];
		for (int32 j = 0; j < Guess.length(); j++)
		{
			char MyGuesschar = Guess[j];
			if(MyGuesschar == HiddenWordChar){
				if (i == j){
					BullCowCount.Bulls++;
					break;
				}
				else{
					BullCowCount.Cows++;
					break;
				}
			}
		}
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) return true;

	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
			return false;
		LetterSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length() <= 1) return true;

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}

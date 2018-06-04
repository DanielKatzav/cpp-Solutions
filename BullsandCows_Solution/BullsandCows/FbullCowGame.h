#pragma once
#include <iostream>
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:

	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	bool IsGameWon(int32);
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	void Reset(); // TODO make mor rich value
	EGuessStatus IsGuessValid(FString) const;

	//counts bulls & cows and increasing try # assumin valid guess
	FBullCowCount SubmitValidGuess(FString);

	//string GenerateWordToGuess();

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
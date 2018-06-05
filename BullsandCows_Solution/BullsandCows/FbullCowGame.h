#pragma once
#include <iostream>
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
	FString Difficulty = "";
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EDifficultyStats
{
	Begginer,
	Intermidiate,
	Advanced,
	Expert
};

class FBullCowGame
{
public:

	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	bool IsGameWon(int32);
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	void Reset(FString); // TODO make mor rich value
	EGuessStatus IsGuessValid(FString) const;

	//counts bulls & cows and increasing try # assumin valid guess
	FBullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
#pragma once

#include <vector>

#include "Player.h"
#include "Word.h"

//all methods are static. input from user and output to console
class UserInterface {
public:
	//help the user understand what is the expected structure of the input file
	static void describeWordsFile();

	//get input from user about each player and fill a Players vector
	static std::vector<Player> getPlayersInfo();

	//after each guess, print the guessed word, current score for each player and which turn it is
	static void displayGameState(const Word& currentWord, const std::vector<Player>& players, const Player& currentPlayer);

	//read the player's guess (one character)
	static char getPlayerGuess();

	//when all the characters were guessed, print what is the word
	static void announceWordHasBeenGuessed(const Word& word);

	//while we play, before each new word, announce that we started a new word
	static void announceOnNewWord();

	//game over. print who won :-)
	static void displayResult(const Player& winner);
};


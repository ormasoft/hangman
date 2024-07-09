#include <iostream>
#include <sstream>
#include <cctype>

#include "UserInterface.h"

//------------------------------------------------------------------------------
// Method: describeWordsFile
// help the user understand what is the expected structure of the input file
//------------------------------------------------------------------------------
void UserInterface::describeWordsFile()
{
	std::cout << std::endl;
	std::cout << "Note: The word file should contain one word per line, with only alphabetic characters." << std::endl;
	std::cout << "For example:" << std::endl;
	std::cout << "red" << std::endl;
	std::cout << "green" << std::endl;
	std::cout << "blue" << std::endl;
	std::cout << std::endl;
}

//------------------------------------------------------------------------------
// Method: getPlayersInfo
// get input from user about each player and fill a Players vector
//------------------------------------------------------------------------------
std::vector<Player> UserInterface::getPlayersInfo() { //return refernce !!!
	std::vector<Player> players;
	int numPlayers = 0;
	std::string input;

	//get the number of players. Check that it is really a valid number and greater than 0.
	while (true) {
		std::cout << "Enter the number of players: ";
		std::getline(std::cin, input);
		std::stringstream ss(input);

		// Check if the input can be converted to an integer, ensure no extra characters, and check if the number is greater than 0
		if (ss >> numPlayers && ss.eof() && numPlayers > 0) {
			break;
		}
		else {
			std::cout << "Invalid input. Please enter a positive number" << std::endl;
		}
	}

	std::cout << "Number of players: " << numPlayers << std::endl;

	//for each Player, get their name. Any name is valid
	for (int i = 0; i < numPlayers; ++i) {
		std::string name;
		std::cout << "Enter name for Player " << (i + 1) << ": ";
		std::getline(std::cin, name);
		players.emplace_back(name);
	}
	return players;
}

//------------------------------------------------------------------------------
// Method: displayGameState
// after each guess, print the guessed word, current score for each player and which turn it is
//------------------------------------------------------------------------------
void UserInterface::displayGameState(const Word& currentWord, const std::vector<Player>& players, const Player& currentPlayer) {
	std::cout << "\n==================================================\n";
	std::cout << "Current word: " << currentWord.getDisplayWord() << std::endl;
	std::cout << "Guessed letters: " << currentWord.getGuessedLetters() << std::endl;
	for (const auto& player : players) {
		std::cout << player.getName() << "'s score: " << player.getScore() << std::endl;
	}
	std::cout << "It's " << currentPlayer.getName() << "'s turn." << std::endl;
}

//------------------------------------------------------------------------------
// Method: getPlayerGuess
// read the player's guess (one character)
//------------------------------------------------------------------------------
char UserInterface::getPlayerGuess() {
	char guess;

	//guess one letter. allow only one alpabetic characters. 
	while (true) {
		std::cout << "Guess a letter: ";
		std::string input;
		std::getline(std::cin, input);

		//ensure it is one, alphbetic character!
		if (input.length() == 1 && std::isalpha(input[0])) {
			guess = std::tolower(input[0]);
			break;
		}
		else {
			std::cout << "Invalid input. Please enter a single alphabetic character.\n";
		}
	}
	return guess;
}

//------------------------------------------------------------------------------
// Method: announceWordHasBeenGuessed
// when all the characters were guessed, print what is the word
//------------------------------------------------------------------------------
void UserInterface::announceWordHasBeenGuessed(const Word& word) {
	std::cout << "\nThe word " << word.getDisplayWord() << " was guessed" << std::endl;
}

//------------------------------------------------------------------------------
// Method: announceOnNewWord
// while we play, before each new word, announce that we started a new word
//------------------------------------------------------------------------------
void UserInterface::announceOnNewWord() {
	std::cout << "A new word has been chosen!" << std::endl;
}

//------------------------------------------------------------------------------
// Method: displayResult
// game over. print who won :-)
//------------------------------------------------------------------------------
void UserInterface::displayResult(const Player& winner) {
	std::cout << "\n**************************************************\n";
	std::cout << "Game Over! The winner is " << winner.getName() << " with " 
		                                     << winner.getScore() << " points!" 
		                                     << std::endl;
	std::cout << "**************************************************\n\n";
}


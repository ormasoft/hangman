#include <algorithm>

#include "UserInterface.h"
#include "Game.h"


//------------------------------------------------------------------------------
// Method: constructor
//------------------------------------------------------------------------------
Game::Game(WordsManager& wordManager) : wordManager(wordManager) {
	//get the players "list" from the user
	players = UserInterface::getPlayersInfo();
}

//------------------------------------------------------------------------------
// Method: play - main function of the game
//------------------------------------------------------------------------------
void Game::play() {
	Word currentWord;

	//while there are more words to process
	while ((currentWord = wordManager.getNextWord()) != Word()) {
		UserInterface::announceOnNewWord();

		//users will try to guess letters till the entire word will be guessed
		while (!currentWord.entireWordWasGuessed()) {
			Player& currentPlayer = players[currentPlayerIndex];
			UserInterface::displayGameState(currentWord, players, currentPlayer);
			char guess = UserInterface::getPlayerGuess();
			int points = currentWord.countNumOfOccurrences(guess);
			currentPlayer.addPointsToScore(points);

			//if the player guessed correctly, he is entitled for more guess. 
			//otherwise he got 0 points so index wil be advance
			if (points == 0) {
				currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
			}
		}
		//all characters were guessed, print what was the word
		UserInterface::announceWordHasBeenGuessed(currentWord);
	}

	//all words where guessed. go over all players and see which one has the highest score. 
	Player& winner = *std::max_element(players.begin(), players.end(),
		[](const Player& a, const Player& b) { return a.getScore() < b.getScore(); });

	//announce the winner :-)
	UserInterface::displayResult(winner);
}
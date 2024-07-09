#pragma once

#include <vector>
#include "WordsManager.h"
#include "Player.h"

class Game {
public:
	//constructor
	Game(WordsManager& wordManager);

	//play the game
	void play();

private:
	WordsManager& wordManager;   //reference to WordManager so changes during game will be reflected in it
	std::vector<Player> players;
	size_t currentPlayerIndex = 0;
};


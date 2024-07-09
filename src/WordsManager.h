#pragma once

#include <string>
#include "Word.h"

class WordsManager {
public:
	//constructor
	WordsManager(const std::string& filePath, unsigned int wordLimit = 0);

	//get the next word which its letters should be guessed.
	Word getNextWord();

private:
	//read the words from the file to the words vector
	void loadWordsFromFile(const std::string& filePath);

	std::vector<Word> words;
};

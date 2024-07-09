#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

#include "WordsManager.h"


//------------------------------------------------------------------------------
// Method: constructor
//------------------------------------------------------------------------------
WordsManager::WordsManager(const std::string& filePath, unsigned int wordLimit) {
	// read the words from file
	loadWordsFromFile(filePath);
	if (words.empty()) {
		throw std::runtime_error("Error: No valid words found in the file.");
	}

	// create random number generator object, based on Mersenne Twister 19937
	std::random_device rd;
	std::mt19937 generator(rd());

	// shuffle the words so every game the word's order will be different
	std::shuffle(words.begin(), words.end(), generator);

	// make sure that the words will not contain more than wordLimit 
	if (wordLimit > 0 && wordLimit < words.size()) {
		words.resize(wordLimit);
	}
}


//------------------------------------------------------------------------------
// Method: getNextWord
// get the next word which its letters should be guessed.
//------------------------------------------------------------------------------
Word WordsManager::getNextWord() {
	if (words.empty()) 
		return Word();
	Word word = std::move(words.back());
	words.pop_back();
	return word;
}

//------------------------------------------------------------------------------
// Method: loadWordsFromFile
// read the words from the file to the words vector
//------------------------------------------------------------------------------
void WordsManager::loadWordsFromFile(const std::string& filePath) {
	//open the file
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Unable to open file '" + filePath + "'");
	}

	//for each word in the file, construct Word object in the words vector
	std::string line;
	int lineNum = 0;
	while (std::getline(file, line)) {
		lineNum++;
		try {
			words.emplace_back(line); // Directly construct Word objects
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "Warning: Line " << lineNum << ": " << e.what() << std::endl;
		}
	}
}

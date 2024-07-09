#include <iostream>
#include <cctype>
#include <algorithm>
#include "Word.h"

//------------------------------------------------------------------------------
// Method: constructor
//------------------------------------------------------------------------------
Word::Word(const std::string& word) : word(word) {
	//ensure all characters are alpabetic characters
	if (!std::all_of(word.begin(), word.end(), [](char c) { return std::isalpha(c); })) {
		throw std::invalid_argument("Invalid word: '" + word + "'. All characters must be alphabetic.");
	}
	//convert all characters to lower case
	std::transform(this->word.begin(), this->word.end(), this->word.begin(), ::tolower);
}

//------------------------------------------------------------------------------
// Method: empty constructor
//------------------------------------------------------------------------------
Word::Word() : word("") {}

//------------------------------------------------------------------------------
// Method: move constructor
//------------------------------------------------------------------------------
Word::Word(Word&& other) : word(std::move(other.word)), guessedLetters(std::move(other.guessedLetters)) {}

//------------------------------------------------------------------------------
// Method: move assignment operator
//------------------------------------------------------------------------------
Word& Word::operator=(Word&& other) noexcept {
		if (this != &other) {
			word = std::move(other.word);
			guessedLetters = std::move(other.guessedLetters);
		}
		return *this;
	}

//------------------------------------------------------------------------------
// Method: operator ==
//------------------------------------------------------------------------------
bool Word::operator==(const Word& other) const {
	return word == other.word && guessedLetters == other.guessedLetters;
}

//------------------------------------------------------------------------------
// Method: operator !=
//------------------------------------------------------------------------------
bool Word::operator!=(const Word& other) const {
	return !(*this == other);
}

//------------------------------------------------------------------------------
// Method: countNumOfOccurrences
// count and return the number of occurences of a letter in this word
//------------------------------------------------------------------------------
int Word::countNumOfOccurrences(char letter) {
	letter = std::tolower(letter);
	//check if the guessed character already in the set
	if (guessedLetters.find(letter) != guessedLetters.end()) {
		return 0;
	}
	//otherwise, insert the new letter to the set and return how many times the letter appears in the word
	guessedLetters.insert(letter);
	return std::count(word.begin(), word.end(), letter);
}

//------------------------------------------------------------------------------
// Method: entireWordWasGuessed
// all letters in this word were guessed
//------------------------------------------------------------------------------
bool Word::entireWordWasGuessed() const {
	//check if the condition is true for all elements in the range.
	return std::all_of(word.begin(), word.end(), [this](char c) { 
		return guessedLetters.find(c) != guessedLetters.end(); 
	});
}

//------------------------------------------------------------------------------
// Method: getDisplayWord
// retrun string with dashes in the places where letter wasn't already guessed
//------------------------------------------------------------------------------
std::string Word::getDisplayWord() const {
	std::string display;
	for (char c : word) {
		display += (guessedLetters.find(c) != guessedLetters.end()) ? c : '_';
	}
	return display;
}

//------------------------------------------------------------------------------
// Method: getGuessedLetters
// return the letters that was guessed so far, seperated by comma
//------------------------------------------------------------------------------
std::string Word::getGuessedLetters() const {
	//check for edge cases
	if (guessedLetters.empty()) {
		return "";
	}

	//build a string from the guessed latters, seperated by commas
	std::string letters;
	for (auto it = guessedLetters.begin(); it != guessedLetters.end(); ++it) {
		if (it != guessedLetters.begin()) {
			letters += ", ";
		}
		letters += *it;
	}
	return letters;
}

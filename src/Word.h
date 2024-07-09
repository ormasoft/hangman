#pragma once

#include <string>
#include <set>

class Word {
public:
	//constructor
	Word(const std::string& word);

	//empty constructor
	Word();

	//move constructor
	Word(Word&& other);

	//move assignment operator
	Word& operator=(Word&& other) noexcept;

	//operator ==
	bool operator==(const Word& other) const;

	//operator !=
	bool operator!=(const Word& other) const;

	//count and return the number of occurences of a letter in this word
	int countNumOfOccurrences(char letter);

	//all letters in this word were guessed
	bool entireWordWasGuessed() const;

	//retrun string with dashes in the places where letter wasn't already guessed
	std::string getDisplayWord() const;

	//return the letters that was guessed so far, seperated by comma
	std::string getGuessedLetters() const;

private:
	std::string word;
	std::set<char> guessedLetters;
};

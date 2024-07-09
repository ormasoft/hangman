/*****************************************************************************************
| The main file of the hangman game.
| 
| It contains the parsing of command line arguments (via cxxopts library) 
| https://github.com/jarro2783/cxxopts/tree/master
| Few functions and one data structure are used to handle the parsing.
| The rest of the file is the main function
\*****************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cxxopts.hpp>

#include "UserInterface.h"
#include "Game.h"

//------------------------------------------------------------------------------
// define (scalable) struct for holding the params from commnad line
// cuttently there are only two. the input file and how many words to use
//------------------------------------------------------------------------------
struct ParsedOptions {
	std::string wordFile;
	int wordLimit;
};

//------------------------------------------------------------------------------
// Function to generate usage description
//------------------------------------------------------------------------------
std::string getUsageDescription(std::string programName) {
	return std::string("Usage: " + programName + " -w word-file [-l word-limit]");
}

//------------------------------------------------------------------------------
// Function to parse arguments
//------------------------------------------------------------------------------
ParsedOptions parseArguments(int argc, char* argv[]) {
	ParsedOptions options;

	cxxopts::Options cxxOptions("Word Guessing Game", "A simple word guessing game");
	cxxOptions.add_options()
		("w,word-file", "Path to the file containing words", cxxopts::value<std::string>())
		("l,word-limit", "Limit the number of words in the game", cxxopts::value<int>()->default_value("0"))
		("h,help", getUsageDescription(std::string(argv[0])))
		;

	auto result = cxxOptions.parse(argc, argv);

	if (result.count("help")) {
		std::cout << cxxOptions.help() << std::endl;
		exit(0); // Exit after displaying help
	}

	if (!result.count("word-file")) {
		std::cerr << "Error: Word file path is required." << std::endl;
		std::cout << cxxOptions.help() << std::endl;
		exit(1); // Exit with error code
	}

	options.wordFile = result["word-file"].as<std::string>();
	options.wordLimit = result["word-limit"].as<int>();

	return options;
}


//------------------------------------------------------------------------------
// Function: main
//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	ParsedOptions options;

	try {
		options = parseArguments(argc, argv);
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred during argument parsing: " << e.what() << std::endl;
		return 1;
	}

	try {
		UserInterface::describeWordsFile();
		WordsManager wordManager(options.wordFile, options.wordLimit);
		Game game(wordManager);
		game.play();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

#pragma once

#include <string>

class Player {
public:
	//constructor (any player name will do. even email...)
	Player(const std::string& name) : name(name), score(0) {} 

	// assignment operator
	inline void addPointsToScore(int points) { score += points; }
	inline const std::string& getName() const { return name; }
	inline int getScore() const { return score; }

private:
	std::string name;
	int score;
};


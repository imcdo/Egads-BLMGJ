#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "card.h"
#include <vector>

class Player {

private:
	int health;
	std::vector<Card> deck;
public:
	Player();
	void initDeck();
	int getHealth();
};
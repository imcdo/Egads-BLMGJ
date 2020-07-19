#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "card.h"
#include <vector>

class Discard {
private:

public:
	std::vector<Card*> cards;

	Discard();
	void addCard(Card* card); //Player gets card from hand
	void clear(); //Player should check when deck+hand are empty
};
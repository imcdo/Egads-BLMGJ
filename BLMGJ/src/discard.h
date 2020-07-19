#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "card.h"
#include <deque>

class Discard {
private:
	glm::vec2 position;
	std::deque<Card*> cards;

public:
	Discard() = default;
	Discard(glm::vec2 pos);
	void addCard(Card* card); //Player gets card from hand
	void clear(); //Player should check when deck+hand are empty
};
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "battlefield.h"
#include "card.h"
#include <vector>

class Player {

private:
	int health;
	std::vector<Card> deck;

	Bestiary* bestiary;
	Battlefield* battlefield;
public:
	Player(Bestiary* bestiary, Battlefield* field);
	void initDeck();
	int getHealth();
	void useCard(Card card);
};
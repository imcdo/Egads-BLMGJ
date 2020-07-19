#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "battlefield.h"
#include "card.h"
#include "drawDeck.h"
#include "hand.h"
#include "discard.h"
#include <vector>

class Player {

private:
	int health;
	DrawDeck drawDeck;
	Hand hand;
	Discard discard;
	std::vector<Card> deck;

	Bestiary* bestiary;
	Battlefield* battlefield;
public:
	Player(Bestiary* bestiary, Battlefield* field, Math::Rect rect);
	void initDeck();
	int getHealth();
	DrawDeck getDrawDeck();
	Hand getHand();
	Discard getDiscard();
	void useCard(Card card);
};
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "battlefield.h"
#include "card.h"
#include "drawDeck.h"
#include "hand.h"
#include "discard.h"
#include <vector>
#include "projectile.h"
class Player {

private:
	int health;
	DrawDeck drawDeck;
	Hand hand;
	Discard discard;
	

	Bestiary* bestiary;
	Battlefield* battlefield;

public:
	std::vector<Card> deck;
	Projectile* loaded;

	Player(Bestiary* bestiary, Battlefield* field, Math::Rect rect, glm::vec2 drawDeckPos, glm::vec2 discardPos);
	~Player();
	void initDeck();
	int getHealth();
	DrawDeck getDrawDeck();
	Hand getHand();
	Discard getDiscard();
	
	void useCard(Card& card);

	void drawToHand();
	void cardPlayInputHandler(Card* card);
	void resetCards();

	void updateCard(Card& card);

	void shootLoadedProjectile(vec2 dir);
};
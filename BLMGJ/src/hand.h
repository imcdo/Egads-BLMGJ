#pragma once
#include <vector>
#include "card.h"
#include "settings.h"
#include "math.h"

class Hand {
private:
	Math::Rect playSpace;

	Card* playCardHelper(std::vector<Card*>::iterator it);
	void spaceCards();
public:
	Hand(Math::Rect);
	std::vector<Card*> cards;

	// returns the index in hand
	size_t drawCard(Card*);
	Card* playCard(Card*);
	Card* playCard(size_t);
	

};
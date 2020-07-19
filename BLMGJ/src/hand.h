#pragma once
#include <vector>
#include "card.h"
#include "settings.h"
#include "math.h"

class Hand {
private:
	Math::Rect playSpace;

	void playCardHelper(std::vector<Card*>::iterator it);
public:
	Hand(Math::Rect);
	std::vector<Card*> cards;

	// returns the index in hand
	size_t drawCard(Card*);
	void playCard(Card*);
	void playCard(size_t);


};
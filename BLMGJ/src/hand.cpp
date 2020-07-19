#include <algorithm>
#include "hand.h"

Hand::Hand(Math::Rect playArea) : playSpace(playArea)
{
}

size_t Hand::drawCard(Card* card) {
	float idx = cards.size();
	cards.push_back(card);

	float maxWidth = playSpace.getWidth();
	float cardWidthSum = 0;
	
	// sum card widths
	for (const Card* c : cards) {
		cardWidthSum += c->getRect().getWidth();
	}

	// no spacing needed for card
	float cardSpacing = (maxWidth - cardWidthSum) / (cards.size() +1);

	// place cards in new location
	float newX = playSpace.getXMin();
	float newY = playSpace.getYMin() + playSpace.getHeight() / 2;
	for (Card* c : cards) {
		float halfCWidth = c->getRect().getWidth() / 2.0f;
		newX += cardSpacing + halfCWidth;
		c->warp({newX, newY});
		newX += halfCWidth;
	}

	return idx;
}

void Hand::playCard(Card* card) {
	std::vector<Card*>::iterator it = std::find(cards.begin(), cards.end(), card);
	if (it == cards.end()) {
		std::cerr << "trying to play a card not in hand" << std::endl;
		return;
	}

	playCardHelper(it);
}

void Hand::playCard(size_t idx) {
	playCardHelper(cards.begin() + idx);
}

void Hand::playCardHelper(std::vector<Card*>::iterator it) {

}

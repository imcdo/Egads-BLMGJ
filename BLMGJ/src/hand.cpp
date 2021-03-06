#include <algorithm>
#include "hand.h"

Hand::Hand(Math::Rect playArea) : playSpace(playArea)
{
}

void Hand::spaceCards() {
	float maxWidth = playSpace.getWidth();
	float cardWidthSum = 0;

	// sum card widths
	for (const Card* c : cards) {
		cardWidthSum += c->getRect().getWidth();
	}

	// no spacing needed for card
	float cardSpacing = (maxWidth - cardWidthSum) / (cards.size() + 1);

	// place cards in new location
	float newX = playSpace.getXMin();
	float newY = playSpace.getYMin() + playSpace.getHeight() / 2;
	for (Card* c : cards) {
		float halfCWidth = c->getRect().getWidth() / 2.0f;
		newX += cardSpacing + halfCWidth;
		c->warp({ newX, newY });
		newX += halfCWidth;
	}
}

size_t Hand::drawCard(Card* card) {
	float idx = cards.size();
	cards.push_back(card);

	spaceCards();

	return idx;
}

Card* Hand::playCard(Card* card) {
	std::vector<Card*>::iterator it = std::find(cards.begin(), cards.end(), card);
	if (it == cards.end()) {
		std::cerr << "trying to play a card not in hand" << std::endl;
		return card;
	}

	return playCardHelper(it);
}

Card* Hand::playCard(size_t idx) {
	return playCardHelper(cards.begin() + idx);
}

Card* Hand::playCardHelper(std::vector<Card*>::iterator it) {

	Card* c = *it;
	cards.erase(it);

	spaceCards();
	return c;
}

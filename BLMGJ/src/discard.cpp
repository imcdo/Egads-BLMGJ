#include "discard.h"

Discard::Discard() {
	cards = vector<Card*>();
}

void Discard::addCard(Card* card) {
	cards.push_back(card);
}

void Discard::clear() {
	cards.clear();
}
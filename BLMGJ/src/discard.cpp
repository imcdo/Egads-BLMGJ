#include "discard.h"

Discard::Discard(glm::vec2 pos) : position(pos) {}

void Discard::addCard(Card* card) {
	cards.push_front(card);
	card->warp(position);
}

void Discard::clear() {
	cards.clear();
}
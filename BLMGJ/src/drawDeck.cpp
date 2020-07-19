#include "drawDeck.h"

template<class It>
DrawDeck::DrawDeck(glm::vec2 pos, It iter) : position(pos) {
	for (Card* c : iter) {
		deck.push_back(c);
	}
}

DrawDeck::DrawDeck(glm::vec2 pos) : position(pos) {}

Card* DrawDeck::drawCard() {
	Card* result = deck.front();
	deck.pop_front();
	return result;
}

Card* DrawDeck::peekCard() const {
	Card* result = deck.front();
	return result;
}

template <class It>
void DrawDeck::putBottom(It iterable) {
	for (Card* c : iterable) {
		deck.push_back(c);
		c->warp(position);
	}
}

void DrawDeck::putBottom(Card* card) {
	deck.push_back(card);
	card->warp(position);
}

template <class It>
void DrawDeck::putTop(It iterable) {
	for (Card* c : iterable) {
		deck.push_front(c);
		c->warp(position);
	}
}

void DrawDeck::putTop(Card* card) {
	deck.push_front(card);
	card->warp(position);
}

void DrawDeck::shuffle() {
	std::random_shuffle(deck.begin(), deck.end());
}

int DrawDeck::getDeckSize() {
	return deck.size();
}
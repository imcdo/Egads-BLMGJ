#include "drawDeck.h"

template<class Its>
DrawDeck::DrawDeck(glm::vec2 pos, Its iter) :position(pos) deque(iter.size()) {
	std::copy(iter.begin(), iter.end(), deque.begin());
}

template<class It>
DrawDeck::DrawDeck(glm::vec2 pos, It iter) : position(pos) {
	for (Card* c : iter) {
		deque.push_back(c);
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
	}
}

void DrawDeck::putBottom(Card* card) {
	deck.push_back(card);
}

template <class It>
void DrawDeck::putTop(It iterable) {
	for (Card* c : iterable) {
		deck.push_front(c);
	}
}

void DrawDeck::putTop(Card* card) {
	deck.push_front(card);
}

void DrawDeck::shuffle() {
	std::random_shuffle(deck.begin(), deck.end());
}

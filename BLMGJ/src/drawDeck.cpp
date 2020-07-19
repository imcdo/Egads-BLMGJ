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

}

Card* DrawDeck::peekCard() const {

}

template <class It>
void DrawDeck::putBottom(It iterable) {

}

void DrawDeck::putBottom(Card* card) {

}

template <class It>
void DrawDeck::putTop(It iterable) {

}

void DrawDeck::putTop(Card* card) {

}

void DrawDeck::shuffle() {
	std::random_shuffle(deck.begin(), deck.end());
}

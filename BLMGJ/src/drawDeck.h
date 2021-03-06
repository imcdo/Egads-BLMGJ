#pragma once
#include <deque>
#include <algorithm>
#include <glm/glm.hpp>
#include "card.h"

class DrawDeck {
private:
	glm::vec2 position;
	std::deque<Card*> deck;
public:
	DrawDeck() = default;

	DrawDeck(glm::vec2);

	template<class It>
	DrawDeck(glm::vec2, It iter);

	Card* drawCard();
	Card* peekCard() const;
	
	template <class It>
	void putBottom(It iterable);
	void putBottom(Card*);

	template <class It >
	void putTop(It iterable);
	void putTop(Card*);

	void shuffle();

	int getDeckSize();
};
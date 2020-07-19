#include "player.h"
#include "projectile.h"
#include "settings.h"
#include <algorithm>
#include <string>

// Need to add drawdeck and discard depending on how the positions are passed in
Player::Player(Bestiary* bestiary, Battlefield* field, Math::Rect rect, glm::vec2 drawDeckPos, glm::vec2 discardPos)
	: health(settings::PLAYER_HEALTH), bestiary(bestiary), battlefield(field), 
	  drawDeck(DrawDeck(drawDeckPos)), hand(Hand(rect)), discard(Discard(discardPos)) {
	initDeck();
}

void Player::initDeck() {
	deck = vector<Card>();
	for (int i = 0; i < settings::DECK_SIZE; i++) {
		//generate card
		MonsterData* randMon = bestiary->getRandomMonster();
		std::string monsterPath = "src\\sprites\\monsters\\" + randMon->sprite;
		Card c(0, 0, monsterPath, { 5,5 }, 0.0f, 0.0f, randMon);
		deck.push_back(c);
		drawDeck.putTop(&c);
	}

	drawDeck.shuffle();
	drawToHand();
}

int Player::getHealth() {
	return health;
}

DrawDeck Player::getDrawDeck() {
	return drawDeck;
}

Hand Player::getHand() {
	return hand;
}

Discard Player::getDiscard() {
	return discard;
}

void Player::useCard(Card card) {
	MonsterData* mData = card.getMonsterData();
	Projectile p(0, 0, Sprite("src\\sprites\\UwU.png"), { 1, 1 }, 0.0f, 0.0f, mData, { 0,1 }, battlefield, &card);
	p.active = true;
	card.decrementCardUse();
}

void Player::drawToHand() {
	for (int i = 0; i < settings::HAND_SIZE; i++) {
		Card* c = drawDeck.drawCard();
		hand.drawCard(c);
	}
}


void Player::cardPlayInputHandler(Card* card) {
	hand.playCard(card);
	useCard(*card);
	discard.addCard(card);

	if (hand.cards.size() == 0 && drawDeck.getDeckSize() == 0)
		resetCards();

	if (hand.cards.size() == 0)
		drawToHand();
}

void Player::resetCards() {
	discard.clear();
	for (Card c : deck) {
		drawDeck.putTop(&c);
	}
	//auto deckIter = deckPtrs.begin();
	//drawDeck.putTop(deckIter);
	drawDeck.shuffle();
}
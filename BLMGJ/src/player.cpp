#include "player.h"
#include "projectile.h"
#include "settings.h"
#include <algorithm>

Player::Player(Bestiary* bestiary, Battlefield* field, Math::Rect rect) 
	: health(settings::PLAYER_HEALTH), bestiary(bestiary), battlefield(field), hand(Hand(rect)) {
	initDeck();
}

void Player::initDeck() {
	deck = vector<Card>();
	for (int i = 0; i < 20; i++) {
		//generate card
		Card c(0, 0, Sprite("src\\sprites\\UwU.png"), { 1,1 }, 0.0f, 0.0f, bestiary->getRandomMonster());
		deck.push_back(c);
	}
	std::random_shuffle(deck.begin(), deck.end());
}

int Player::getHealth() {
	return health;
}

Hand Player::getHand() {
	return hand;
}

void Player::useCard(Card card) {
	MonsterData* mData = card.getMonsterData();
	Projectile p(0, 0, Sprite("src\\sprites\\UwU.png"), { 1, 1 }, 0.0f, 0.0f, mData, { 0,1 }, battlefield, &card);
	p.active = true;
	card.decrementCardUse();
}
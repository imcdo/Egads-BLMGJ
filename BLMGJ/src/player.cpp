#include "player.h"
#include "settings.h"

Player::Player() : health(settings::PLAYER_HEALTH) {
	initDeck();
}

void Player::initDeck() {
	//ivan pls help
}

int Player::getHealth() {
	return health;
}

void Player::addCard(Card card) {
	deck.push_back(card);
}

void Player::removeCard(Card card) {

}
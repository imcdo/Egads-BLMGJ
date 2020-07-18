#include "player.h"
#include "settings.h"
#include <algorithm>

Player::Player() : health(settings::PLAYER_HEALTH) {
	initDeck();
}

void Player::initDeck() {
	//ivan pls help
	deck = vector<Card>();
	for (int i = 0; i < 20; i++) {
		//generate card
		//deck.push_back(c);
	}
	std::random_shuffle(deck.begin(), deck.end());
}

int Player::getHealth() {
	return health;
}
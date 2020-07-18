#include "card.h"

Card::Card(float x, float y, Sprite sprite, glm::vec2 scale, float depth, float angle, MonsterData* data) :
	GameObject(x, y, sprite, scale, depth, angle), data(data), decay(data->decay) {}

void Card::use() {
	// make projectile using data

	if (data == nullptr)
		return;

	this->decay--;

	if (this->decay == 0)
		data = nullptr;
}
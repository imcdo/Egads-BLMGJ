#include "card.h"
#include "monsterData.h"

Card::Card(float x, float y, Sprite sprite, glm::vec2 scale, float depth, float angle) :
	GameObject(x, y, sprite, scale, depth, angle), data(new Flame()) {}

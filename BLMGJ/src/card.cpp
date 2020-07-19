#include "card.h"
#include "cardRenderer.h"
#include "batchSpriteRenderer.h"

Card::Card(float x, float y, std::string spritePath, glm::vec2 scale, float depth, float angle, MonsterData* data) :
	GameObject(x, y, Sprite(CardRenderer::drawCard(data->name, data->flavor, spritePath, data->decay, data->rank /*color?*/)), scale, depth, angle), data(data) {
	
	if (data == nullptr)
		decay = 0;
	else
		decay = data->decay;

	BatchSpriteRenderer& sr = *BatchSpriteRenderer::getInstance();
	sr.addGameObject(data->name + "_MonsterObject", this, sr.getShader("default"));
}

MonsterData* Card::getMonsterData() {
	return this->data;
}

void Card::decrementCardUse() {
	if (data == nullptr) {
		return;
	}

	decay--;

	if (decay == 0) {
		data = nullptr;
	}
}

void Card::addNewData(MonsterData* monData) {
	data = monData;
	decay = data->decay;
}


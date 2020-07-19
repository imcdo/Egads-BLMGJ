#include "monster.h"
#include "batchSpriteRenderer.h"
#include <sstream>

Monster::Monster(float x, float y, glm::vec2 scale, float depth, float angle, MonsterData* data): 
	GameObject(x, y, Sprite("src\\sprites\\monsters\\" + data->sprite, Default, 4), scale, depth, angle),
	currentHealth(data->health),
	data(data)
{
	BatchSpriteRenderer& sr = *BatchSpriteRenderer::getInstance();
	stringstream ss;

	ss << data->name << "_MonsterObject" << this;
	name = ss.str();
	
	sr.addGameObject(name, this, sr.getShader("default"));

	currentHealth = 1;
}

bool Monster::Attack(int baseDamage, Element* damageType)
{
	currentHealth -= baseDamage * damageType->GetDamageMultiplierAgainst(data->element);
	if (currentHealth <= 0)
		return true;
	return false;
}

Monster::~Monster()
{
	BatchSpriteRenderer& sr = *BatchSpriteRenderer::getInstance();
	sr.remove(name);
}
#include "monster.h"

Monster::Monster(float x, float y, Sprite sprite, glm::vec2 scale, float depth, float angle, MonsterData* data): 
	GameObject(x, y, sprite, scale, depth, angle),
	currentHealth(data->health),
	data(data)
{

}

void Monster::Attack(int baseDamage, Element* damageType)
{
	currentHealth -= baseDamage * damageType->GetDamageMultiplierAgainst(data->element);
	// check for die
	//cout << "DID " << baseDamage * damageType->GetDamageMultiplierAgainst(data->element) << " DAMAGE!" << endl;
}

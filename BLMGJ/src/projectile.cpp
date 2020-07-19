#include "projectile.h"
#include "Time.h"

Projectile::Projectile(float x, float y, Sprite sprite, vec2 scale, float depth, float angle,
	const MonsterData * data, vec2 trajectory, Battlefield * field, Card * card) : 
	GameObject(x, y, sprite, scale, depth, angle),
	trajectory(trajectory),
	bounce(data->bounce),
	damage(data->damage),
	element(data->element),
	field(field),
	card(card)
{
	
}

// Move projectile, bounce, damage, and destroy
void Projectile::Update()
{
	if (active)
	{
		pos += normalize(trajectory) * speed * Time::getDeltaTime();
		if (field->AtLocation(pos) != nullptr)
		{
			// bounce, damage, get new trajectory OR destroy
		}
	}
}

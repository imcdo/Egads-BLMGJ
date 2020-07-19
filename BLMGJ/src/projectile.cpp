#include "projectile.h"
#include "Time.h"

using namespace std;

vec2 lerp(vec2 x, vec2 y, float t) {
	return x * (1.0f - t) + y * t;
}

Projectile::Projectile(float x, float y, Sprite sprite, vec2 scale, float depth, float angle,
	const MonsterData * data, vec2 trajectory, Battlefield * field, Card * card) : 
	GameObject(x, y, sprite, scale, depth, angle),
	destination(trajectory),
	bounce(data->bounce),
	damage(data->damage),
	element(data->element),
	field(field),
	card(card)
{
	origin = pos;
	bounce = 10000;
		// bestiary.getRandomMonster();
}

void Projectile::Update()
{
	if (!active) // Only move when active
		return;

	// Lerp
	distanceTraveled += Time::getDeltaTime() * speed;
	if (distanceTraveled > totalDistance)
		distanceTraveled = totalDistance;

	// Move
	vec2 lerps = lerp(origin, destination, distanceTraveled / totalDistance);
	this->warp(lerp(origin, destination, distanceTraveled/totalDistance));
	if (!active) // Only move when active
		return;

	// Bounce
	if (distanceTraveled >= totalDistance)
	{
		if (!field->OutOfBounds(pos) || field->AtLocation(pos) != nullptr)		// CASE: that tile is still solid
		{
			origin = pos;
			std::pair<vec2, vec2> originTrajectory = field->Raycast(origin, destination);													// Current pos is new origin

			destination = field->Raycast(origin, originTrajectory.second).first;	// Destination from reflect angle raycast
			bounce--;
			cout << "BOUNCE!" << endl;
		}
		else																	 // CASE: that tile is now vacant
		{
			origin = pos;															// Current pos is new origin
			std::pair<vec2, vec2> originTrajectory = field->Raycast(origin, destination);
			destination = originTrajectory.first;									// Destination from new raycast
		}

		totalDistance = glm::length((destination - origin));					 // Recalculate distance
		distanceTraveled = 0;													 // Reset counter
	}

	// Damage
	cout << "CHECKING: " << pos.x << " " << pos.y << endl;
	cout << field->OutOfBounds(pos) << " | " << (field->AtLocation(pos)) << endl;
	//field->Attack(pos, damage, element);

	// Destroy
	if (bounce <= 0)
	{
		// Destroy this projectile
	}
}


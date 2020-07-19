#include "projectile.h"
#include "Time.h"

using namespace std;

vec2 lerp(vec2 x, vec2 y, float t) {
	return x * (1.0f - t) + y * t;
}

Projectile::Projectile(float x, float y, Sprite sprite, vec2 scale, float depth, float angle,
	const MonsterData * data, vec2 trajectory, Battlefield * field, Card * card) :
	GameObject(x, y, sprite, scale, depth, angle),
	bounce(data->bounce),
	damage(data->damage),
	element(data->element),
	field(field),
	card(card)
{

	origin = pos;
	auto raycast = field->Raycast(origin, glm::normalize(trajectory));

	destination = raycast.first;
	nextTrajectory = raycast.second;

	bounce = 10;
	cout << "Create projectile at " << origin.x << " " << origin.y
		<< " | destination at " << destination.x << " " << destination.y
		<< " | with trajectory " << trajectory.x << " " << trajectory.y << "\n";
	totalDistance = glm::length((destination - origin));					 // Recalculate distance

		// bestiary.getRandomMonster();
}

void Projectile::Update()
{

	if (!active) // Only move when active
		return;


	// Lerp
	distanceTraveled += /* Time::getDeltaTime()  * */ speed;
	if (distanceTraveled > totalDistance)
		distanceTraveled = totalDistance;

	// Move
	vec2 lerps = lerp(origin, destination, distanceTraveled / totalDistance);
	this->warp(lerp(origin, destination, distanceTraveled/totalDistance));
	
	// cout << "POS " << getPosition().x << " " << getPosition().y << endl;
	if (!active) // Only move when active
		return;


	// Bounce
	if (distanceTraveled >= totalDistance)
	{
		origin = pos;
		auto ray = field->Raycast(origin, nextTrajectory);
		destination = ray.first;	// Destination from reflect angle raycast
		nextTrajectory = ray.second;
		bounce--;
		

		totalDistance = glm::length((destination - origin));					 // Recalculate distance
		distanceTraveled = 0;			
		// Reset counter

		
		field->Attack(pos, damage, element);

	}

	// Damage
	// cout << "CHECKING: " << pos.x << " " << pos.y << endl;
	// cout << field->OutOfBounds(pos) << " | " << (field->AtLocation(pos)) << endl;

	// Destroy
	if (bounce <= 0)
	{
		// Destroy this projectile
	}
}


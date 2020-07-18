#include "battlefield.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

Battlefield::Battlefield(float x, float y, Sprite sprite, glm::vec2 scale, float depth, float angle,
	int sizeX, int sizeY, float spacing): GameObject(x, y, sprite, scale, depth, angle)
{
	// Allocate battlefield 
	grid = vector<vector<Monster*>>();
	grid.resize(sizeY, vector<Monster*>(sizeX, nullptr));

	AtLocation(vec2(2, 2));
	AtLocation(vec2(3, 3));

	dimensions = vec2(sizeX, sizeY);
	offset = vec2(0, 0);
	attackOrigin = vec2(0, -10); // TODO: fix this
}

void Battlefield::Populate(float density, int intensity)
{
	// Randomly place enemies
}

void Battlefield::Update()
{
	//cout << "BF tick" << endl;
}

Monster* Battlefield::AtLocation(vec2 location)
{
	// Round to nearest tile
	return grid[(int)(location.y + 0.5)][(int)(location.x + 0.5)];
}

vec2 Battlefield::GetLocation(int row, int col)
{
	return offset + vec2(
		row * spacing,
		(col + ((row % 2) == 0 ? 0 : 0.5f)) * spacing
		);
}

pair<vec2, vec2> Battlefield::Raycast(vec2 origin, vec2 direction)
{
	bool hit = false;
	vec2 step = normalize(direction) * 0.2f; // TODO: lol

	while (!hit)
	{
		origin += step;
		if (OutOfBounds(origin))
			break;
		if (AtLocation(origin) != nullptr)
			break;
	}

	vec2 normal = origin - AtLocation(origin)->getPosition();

	return make_pair(
		origin, 
		reflect(direction, normal));
}

bool Battlefield::OutOfBounds(vec2 position) // TODO: fi
{
	if (position.x < 0 || position.y < 0
		|| position.x > dimensions.x || position.y > dimensions.y)
	{
		return true;
	}
	return false;
}

void Battlefield::Attack()
{
	// while (bounces > 0)
		// 1. Raycast from start position
		// 2. Move
		// 3. Damage at impact location
}

void Battlefield::Defend()
{
	// Damage player based on living enemies
}



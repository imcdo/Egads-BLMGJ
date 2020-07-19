#include "battlefield.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

Battlefield::Battlefield(float x, float y, Sprite sprite, glm::vec2 scale, float depth, float angle,
	int sizeX, int sizeY, float spacing): GameObject(x, y, sprite, scale, depth, angle), spacing(spacing)
{
	// Allocate battlefield 
	grid = vector<vector<Monster*>>();
	grid.resize(sizeY, vector<Monster*>(sizeX, nullptr));

	dimensions = vec2(sizeX, sizeY);
}

void Battlefield::Populate(float density, int intensity)
{
	for (int r = 0; r < grid.size(); r++)
	{
		for (int c = 0; c < grid[0].size(); c++)
		{
			if(((double)rand() / (RAND_MAX)) <= density)
			{
				MonsterData* data = GetBestiary()->getRandomMonster();
				grid[r][c] = new Monster(c * spacing + offset.x, r * spacing + offset.y, { 1,1 }, 0.0f, 0.0f, data);
			}
		}
	}
}

void Battlefield::Update()
{
	//cout << "BF tick" << endl;
}

Monster* Battlefield::AtLocation(vec2 location)
{
	location = (location + offset) / spacing;
	if (OutOfBounds(location))
	{
		return nullptr;
	}
	else
	{
		// Round to nearest tile
		return grid[(int)(location.y + 0.5)][(int)(location.x + 0.5)];
	}
	return nullptr;
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
	origin = (origin + offset) / spacing;
	vec2 step = normalize(direction) * 0.2f; // TODO: lol

	bool hit = false;
	while (!hit)
	{
		//cout << "STEPPING " << step.x << " " << step.y << " | now at " << origin.x << " " << origin.y << endl;

		origin += step;
		if (OutOfBounds(origin))
			break;
		if (AtLocation(origin) != nullptr)
			break;
	}

	vec2 normal = origin - GetLocation((int)origin.x, (int)origin.y);

	return make_pair(
		(origin * spacing) - offset, 
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



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
			//if(((double)rand() / (RAND_MAX)) <= density)
			if(true)
			{
				MonsterData* data = GetBestiary()->getRandomMonster();
				vec2 origin = ToWorldSpace(r, c);
				grid[r][c] = new Monster(origin.x, origin.y, { 1,1 }, 0.0f, 0.0f, data);
			}
			else
			{
				grid[r][c] = nullptr;
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
	if (OutOfBounds(location))
	{
		return nullptr;
	}
	else
	{
		ivec2 gridLocation = ToGridSpace(location);
		cout << "GGGGGGG" << gridLocation.x << " " << gridLocation.y << endl;
		return grid[gridLocation.x][gridLocation.y];
	}
}

void Battlefield::ClearLocation(vec2 location)
{
	if (OutOfBounds(location))
	{
		return;
	}
	else
	{
		ivec2 gridLocation = ToGridSpace(location);
		grid[gridLocation.x][gridLocation.y] = nullptr;
	}
}

ivec2 Battlefield::ToGridSpace(vec2 location)
{
	location = (location - offset) / spacing;
	return ivec2((int)location.y, (int)location.x);
}

vec2 Battlefield::ToWorldSpace(int row, int col)
{
	return (vec2(col, row) * spacing) + offset;
}

pair<vec2, vec2> Battlefield::Raycast(vec2 origin, vec2 direction)
{
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

	vec2 normal = ToWorldSpace((int)origin.x, (int)origin.y);

	return make_pair(
		(origin * spacing) - offset, 
		reflect(direction, normal));
}

bool Battlefield::OutOfBounds(ivec2 position)
{
	position = ToGridSpace(position);

	cout << "GRID: " << position.x << " " << position.y << endl;
	cout << "DIMEN: " << dimensions.x << " " << dimensions.y << endl;

	if (position.x < 0 || position.y < 0
		|| position.y >= dimensions.x || position.x >= dimensions.y)
	{
		return true;
	}
	return false;
}

void Battlefield::Attack(vec2 position, float baseDamage, Element* type)
{
	if (OutOfBounds(position))
		return;

	Monster* monster = AtLocation(position);
	if(monster != nullptr)
		if (monster->Attack(baseDamage, type))	// If the monster died
		{
			delete(monster);
			ClearLocation(position);

			cout << "MONSTER KILLED" << endl;
		}
}

void Battlefield::Defend()
{
	// Damage player based on living enemies
}



#include "battlefield.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "projectile.h"

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
	for (int r = 2; r < grid.size(); r++)
	{
		for (int c = 0; c < grid[0].size(); c++)
		{
			if(((double)rand() / (RAND_MAX)) <= density)
			//if(true)
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
	location = (location - offset - ballOffset) / spacing;
	return ivec2((int)location.y, (int)location.x);
}

vec2 Battlefield::ToWorldSpace(int row, int col)
{
	return (vec2(col, row) * spacing) + offset + ballOffset;
}

pair<vec2, vec2> Battlefield::Raycast(vec2 origin, vec2 direction)
{

	vec2 step = normalize(direction) * 0.2f; // TODO: lol
	vec2 dest = origin;

	bool hit = false;

	vec2 normal = { 0,0 };

	int count = 0;

	while (!hit && count < 100000)
	{

		//cout << "STEPPING " << step.x << " " << step.y << " | now at " << origin.x << " " << origin.y << endl;
		bool prevOutOfBounds = OutOfBounds(dest);
		dest += step;

		if (OutOfBounds(dest) && !prevOutOfBounds) {
			ivec2 position = ToGridSpace(dest);
			normal = { 0,0 };
			if (position.x < 0)
				normal += vec2(1, 0);
			else if (position.x >= dimensions.y)
				normal += vec2(-1, 0);
			if (position.y < 0)
				normal += vec2(0, 1);
			else if (position.y >= dimensions.x)
				normal += vec2(0, -1);
			cout << "herer" << endl;

			//dest = clamp(dest, ToWorldSpace(0, 0), ToWorldSpace(grid.size(), grid[0].size()));
			cout << to_string(direction) << endl;
			cout << to_string(normal) << endl;
			cout << to_string(normalize(reflect(-direction, normal))) << endl;
			return { dest + normal * 10.0f , normalize(reflect(-direction, normal)) };
		}

		else if (OutOfBounds(dest)) {
			ivec2 position = ToGridSpace(dest);

			normal = { 0,0 };
			vec2 closest = clamp(dest, ToWorldSpace(0,0), ToWorldSpace(grid.size(), grid[0].size()));
			if (position.x < 0)
				normal += vec2(1, 0);
			else if (position.x >= dimensions.y)
				normal += vec2(-1, 0);
			if (position.y < 0) 
				normal += vec2(0, 1);
			else if (position.y >= dimensions.x)
				normal += vec2(0, -1);

			closest += normal;
			// cout << "origin " << glm::to_string(origin) << " closest " << to_string(closest) << " normal " << to_string(normal) << endl;
			return { closest + normal * 10.0f, normalize(reflect(-direction, normal)) };
		}


		Monster* monster = AtLocation(dest);
		if (monster != nullptr) {
			normal = normalize(dest - monster->getPosition());
			break;
		}
		++count;
	}
	// vec2 normal = ToWorldSpace((int)dest.x, (int)dest.y);
	vec2 ref = normalize(reflect(-direction, normal));

	/*cout << "RAYCAST: from  " << origin.x << " " << origin.y << " | goin in dir "
		<< direction.x << " " << direction.y << " | to "
		<< dest.x << " " << dest.y << " | next in dir " << ref.x << " " << ref.y << endl;*/
	return make_pair(
		dest,
		ref);
}

bool Battlefield::OutOfBounds(ivec2 position)
{
	position = ToGridSpace(position);

	// cout << "GRID: " << position.x << " " << position.y << endl;
	// cout << "DIMEN: " << dimensions.x << " " << dimensions.y << endl;

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
		}
}

void Battlefield::Defend()
{
	// Damage player based on living enemies
}

void Battlefield::DestroyProjectile(Projectile* p) {
	delete p;
}




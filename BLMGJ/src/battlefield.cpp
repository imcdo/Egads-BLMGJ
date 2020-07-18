#include "battlefield.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

Battlefield::Battlefield(float x, float y, Sprite sprite, float scale, float depth, float angle,
int sizeX , int sizeY, float spacing) : GameObject(x, y, sprite, scale, depth, angle)
{
	// Allocate battlefield 
	grid = vector<vector<Monster*>>();
	grid.resize(sizeY, vector<Monster*>(sizeX, nullptr));

	AtLocation(vec2(2, 2));
	AtLocation(vec2(3, 3));

	offset = vec2(0, 0);
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


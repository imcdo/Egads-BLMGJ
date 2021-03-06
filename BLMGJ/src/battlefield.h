#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "monster.h"
#include "gameObject.h"
#include "FrameUpdater.h"
#include <unordered_set>

class Projectile;

using namespace glm;
using namespace std;

class Battlefield : public GameObject {
private:

	// Hexagonal grid
	vector<vector<Monster*>> grid;							// Track positions of enemies

	unordered_set<Monster*> monsters;
	unordered_set<Projectile*> projectiles;


	vec2 dimensions;		// 2D array dimensions (y = rows)
	vec2 offset = { -575, -100 };			// center the grid
	vec2 ballOffset = {32, -32};
	vec2 attackOrigin = {0, -500};		// Where attacks come from
	float spacing = 50;			// buffer around tile sprites


public:
	Battlefield(float x, float y, Sprite sprite, vec2 scale = {1,1}, float depth = 0.0f, float angle = 0.0f,
		int sizeX = 10, int sizeY = 6, float spacing = 1.0f); // sprite = background?
	void Populate(float density = 0.5f, int intensity = 0); // Populate field with monsters
	void Attack(vec2 position, float baseDamage, Element* type);
	void Defend(); // Input: player object / health bar reference?
	bool hasWon();

	Monster* AtLocation(vec2 location);						// Check tile occupation
	vec2 ToWorldSpace(int row, int col);						// For tile placement
	ivec2 ToGridSpace(vec2 location);
	void ClearLocation(vec2 location);
	pair<vec2, vec2> Raycast(vec2 origin, vec2 direction);	// For trajectory calculation
	bool OutOfBounds(ivec2 position);						// For trajectory calculation


	void DestroyProjectile(Projectile*);
	void AddProjectile(Projectile*);

	void ClearBattleField();
};
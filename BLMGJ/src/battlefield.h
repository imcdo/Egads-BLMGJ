#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "monster.h"
#include "gameObject.h"
#include "FrameUpdater.h"

using namespace glm;
using namespace std;

class Battlefield : public GameObject, public FrameUpdater {
private:

	// Hexagonal grid
	vector<vector<Monster*>> grid;							// Track positions of enemies

	void Update() override;
	
	vec2 dimensions;		// 2D array dimensions (y = rows)
	vec2 offset = {-300, -100};			// center the grid
	vec2 attackOrigin = {0, -500};		// Where attacks come from
	float spacing = 50;			// buffer around tile sprites

public:
	Battlefield(float x, float y, Sprite sprite, vec2 scale = {1,1}, float depth = 0.0f, float angle = 0.0f,
		int sizeX = 10, int sizeY = 6, float spacing = 1.0f); // sprite = background?
	void Populate(float density = 0.5f, int intensity = 0); // Populate field with monsters
	void Attack();
	void Defend(); // Input: player object / health bar reference?

	Monster* AtLocation(vec2 location);						// Check tile occupation
	vec2 GetLocation(int row, int col);						// For tile placement
	pair<vec2, vec2> Raycast(vec2 origin, vec2 direction);	// For trajectory calculation
	bool OutOfBounds(vec2 position);						// For trajectory calculation
};
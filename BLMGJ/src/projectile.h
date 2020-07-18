#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "monster.h"
#include "FrameUpdater.h"
#include "battlefield.h"

using namespace glm;

class Projectile: public GameObject, public FrameUpdater
{
private:
	vec2 trajectory;
	float speed = 10;

	int bounce;
	int damage;
	Element* element = nullptr;

	Battlefield *field = nullptr;

public:
	bool active = false;
	Projectile(float x, float y, Sprite sprite, vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f,
		const MonsterData * data = nullptr, vec2 trajectory = { 0,1 }, Battlefield * field = nullptr);
	void Update() override;
};
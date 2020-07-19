#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "monster.h"
#include "FrameUpdater.h"
#include "battlefield.h"
#include "card.h"

using namespace glm;

vec2 lerp(vec2 x, vec2 y, float t);

class Projectile: public GameObject, public FrameUpdater
{
private:
	vec2 origin;
	vec2 destination;


	vec2 nextTrajectory;

	float distanceTraveled = 0;
	float totalDistance = 1;
	float speed = 5;

	int bounce;
	int damage;
	Element* element = nullptr;

	Battlefield *field = nullptr;

public:
	Card* card = nullptr;
	bool active = false;
	Projectile(float x, float y, Sprite sprite, vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f,
		const MonsterData* data = nullptr, vec2 trajectory = { 0,1 }, Battlefield* field = nullptr, Card* card = nullptr);
	void Update() override;
};
#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "gameObject.h"

using namespace glm;



class Monster : public GameObject {
private:
	MonsterData* data;

	int currentHealth;

public:

	Monster(float x, float y, glm::vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f,
		MonsterData * data = nullptr);
	void Attack(int baseDamage, Element* damageType);
};
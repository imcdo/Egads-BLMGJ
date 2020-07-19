#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "gameObject.h"

using namespace glm;



class Card : public GameObject {
private:
	MonsterData* data;
	int decay;
public:
	Card(float x, float y, Sprite sprite, vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f, MonsterData* data = nullptr);
	MonsterData* getMonsterData();
	void decrementCardUse();
	void addNewData(MonsterData* monData);

};
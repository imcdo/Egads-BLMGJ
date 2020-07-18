#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "gameObject.h"

using namespace glm;



class Card : public GameObject {
private:
	CardData data;

public:
	Card(float x, float y, Sprite sprite, float scale = 1.0f, float depth = 0.0f, float angle = 0.0f);
};
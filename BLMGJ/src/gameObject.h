#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "shader.h"
#include <vector>

using namespace glm;



class GameObject {

protected:
	vec2 pos;
	float depth;
	float angle;
	vec2 scaleFactor;
	Sprite sprite;

	vec2 pivot = { .5, .5 };

public:			

	GameObject(float x, float y, Sprite sprite, glm::vec2 scale = {1,1}, float depth = 0.0f, float angle = 0.0f);
	void draw(Shader* s) const;
	void warp(float x, float y); // goto location
	void move(float x, float y); // add to current location

	void setScale(vec2 sf);
	void setRotation(float angle);

	void rotate(float angle);
	void scale(vec2 sf);

	void setSprite(Sprite sprite) { this->sprite = sprite; }
	Sprite getSprite() const { return sprite; }


};
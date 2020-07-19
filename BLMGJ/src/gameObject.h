#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "sprite.h"
#include "shader.h"
#include "math.h"

using namespace glm;



class GameObject {

protected:
	vec2 pos;
	float depth;
	float angle;
	vec2 scaleFactor;
	Sprite sprite;
	
	vec2 pivot = { .5, .5 };

	glm::vec2 getAdjScaleFactor() const;

public:			

	GameObject(float x, float y, Sprite sprite, glm::vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f);
	GameObject(glm::vec2, Sprite sprite, glm::vec2 scale = {1,1}, float depth = 0.0f, float angle = 0.0f);
	virtual void draw(const Shader* s) const;
	void warp(float x, float y); // goto location
	void warp(glm::vec2); // goto location
	void move(float x, float y); // add to current location
	void move(glm::vec2); // add to current location
	vec2 getPosition();

	void setScale(vec2 sf);
	void setRotation(float angle);

	void rotate(float angle);
	void scale(vec2 sf);

	void setSprite(Sprite sprite) { this->sprite = sprite; }
	Sprite getSprite() const { return sprite; }

	// Get a non unique rect for computation perpouses
	Math::Rect getRect() const;
};
﻿#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"

using namespace glm;



class GameObject {
private:
	vec2 pos;
	float depth;
	float angle;
	float scale;
	Sprite sprite;
	
public:			
	GameObject(float x, float y, Sprite sprite, float scale = 1.0f, float depth = 0.0f, float angle = 0.0f);
	void draw() const;
	void warp(float x, float y); // goto location
	void move(float x, float y); // add to current location
};
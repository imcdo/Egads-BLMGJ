#pragma once
#include "gameObject.h"
#include "CursorMoveUpdater.h"
#include "math.h"
#include <iostream>

class Shooter : public GameObject, public CursorMoveUpdater {
public:
	Shooter(float x, float y, Sprite sprite, glm::vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f) :
		GameObject(x, y, sprite, scale, depth, angle) {}

	void CursorMove(float x, float y) override {

		std::cout << "cursorrot " << x << " " << y << " pos " << getPosition().x << " " << getPosition().y << std::endl;
		glm::vec2 dir = glm::normalize(glm::vec2(x, y) - getPosition());
		std::cout << "dir " << dir.x << " " << dir.y  << std::endl;
		setRotation(glm::clamp<float>(Math::angleBetween({0,1}, dir), -90, 90));
	}
};
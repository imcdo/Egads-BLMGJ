#pragma once
#include "gameObject.h"
#include "frameUpdater.h"
#define M_PI 3.14159

class Trail : public GameObject {
public:
	glm::vec2 trajectory;
	Trail(float x, float y, Sprite sprite, vec2 scale, float depth, float angle) :
		GameObject(x, y, sprite, scale, depth, angle) {
		GameObject::scale(glm::vec2(3.0, 1.0));
	};
	void update(glm::vec2 traj, glm::vec2 pos) {
		trajectory = traj;
		warp(pos - normalize(traj)*28.0f);
		setRotation((std::atan2(trajectory.y, trajectory.x))/ M_PI * 180.0);
	}
	void draw(const Shader* s) const override {
		GameObject::draw(s);
	}
};
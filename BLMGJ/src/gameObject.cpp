#include "gameObject.h"


GameObject::GameObject(float x, float y, Sprite sprite, float scale, float depth, float angle) : pos(), sprite(sprite) {
	pos.x = x;
	pos.y = y;
	this->scale = scale;
	this->depth = depth;
	this->angle = angle;
}

void GameObject::draw() const {
	
}

void GameObject::warp(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void GameObject::move(float x, float y) {
	pos.x += x;
	pos.y += y;
}
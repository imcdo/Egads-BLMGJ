#include "gameObject.h"
#include <GL/glew.h>

GameObject::GameObject(float x, float y, Sprite sprite, float scale, float depth, float angle) : pos(), sprite(sprite) {
	pos.x = x;
	pos.y = y;
	this->scale = scale;
	this->depth = depth;
	this->angle = angle;


}

void GameObject::draw(unsigned int VAO) const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite.getTextureID());

	glBindVertexArray(VAO);
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void GameObject::warp(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void GameObject::move(float x, float y) {
	pos.x += x;
	pos.y += y;
}
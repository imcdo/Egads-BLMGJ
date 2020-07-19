#include "gameObject.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


GameObject::GameObject(float x, float y, Sprite sprite, glm::vec2 scale, float depth, float angle) : 
	pos(x,y), sprite(sprite), scaleFactor(scale), depth(depth), angle(angle)
{}

GameObject::GameObject(glm::vec2 pos, Sprite sprite, glm::vec2 scale, float depth, float angle) :
	pos(pos), sprite(sprite), scaleFactor(scale), depth(depth), angle(angle) {
}

glm::vec2 GameObject::getAdjScaleFactor() const {
	return  { sprite.getWidth() * scaleFactor.x / sprite.ppi, sprite.getHeight() * scaleFactor.y / sprite.ppi };
}

void GameObject::draw(const Shader* s) const {

	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 realSF = getAdjScaleFactor();
	
	transform = glm::translate(transform, glm::vec3(pos, 0));
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0, 0, 1));
	transform = glm::scale(transform, glm::vec3(realSF, 1));

	unsigned int transformID = glGetUniformLocation(s->id, "transform");
	glUniformMatrix4fv(transformID, 1, GL_FALSE, &transform[0][0]);

	unsigned int depthID = glGetUniformLocation(s->id, "depth");
	glUniform1f(depthID, depth);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite.getTextureID());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GameObject::warp(float x, float y) {
	warp({ x,y });
}

void GameObject::warp(glm::vec2 w) {
	pos = w;
}

void GameObject::move(float x, float y) {
	move({ x,y });
}

void GameObject::move(glm::vec2 trans) {
	pos += trans;
}

vec2 GameObject::getPosition() const {
	return pos;
}

void GameObject::setScale(glm::vec2 sf) {
	scaleFactor = sf;
}

void GameObject::setRotation(float angle) {
	this->angle = angle;
}

void GameObject::rotate(float angle) {
	this->angle += angle;
}

void GameObject::scale(glm::vec2 sf) {
	scaleFactor *= sf;
}

Math::Rect GameObject::getRect() const {
	return { pos - getAdjScaleFactor() / 2.0f, pos + getAdjScaleFactor() / 2.0f };
}
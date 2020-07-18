#include "gameObject.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


GameObject::GameObject(float x, float y, Sprite sprite, glm::vec2 scale , float depth, float angle) : pos(), sprite(sprite) {
	pos.x = x;
	pos.y = y;
	this->scaleFactor = scale;
	this->depth = depth;
	this->angle = angle;
}

void GameObject::draw(Shader* s) const {

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(scaleFactor, 1));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1));

	model = glm::translate(model, glm::vec3(pos, 0));


	unsigned int modelID = glGetUniformLocation(s->id, "model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	unsigned int depthID = glGetUniformLocation(s->id, "depth");
	glUniform1f(depthID, depth);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite.getTextureID());

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
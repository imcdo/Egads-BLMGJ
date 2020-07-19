#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "sprite.h"
#include "monsterData.h"
#include "gameObject.h"
#include "Time.h"

using namespace glm;



class Card : public GameObject {
private:
	MonsterData* data;
	int decay;
public:
	Card(float x, float y, Sprite sprite, vec2 scale = { 1,1 }, float depth = 0.0f, float angle = 0.0f, MonsterData* data = nullptr);
	MonsterData* getMonsterData();
	void decrementCardUse();
	void addNewData(MonsterData* monData);
	void draw(const Shader* s) const override {
		glUniform1f(glGetUniformLocation(s->id, "time"), Time::getCurrentTime());
		glUniform1i(glGetUniformLocation(s->id, "rarity"), data ? data->rank : 0);
		GameObject::draw(s);
	}
};
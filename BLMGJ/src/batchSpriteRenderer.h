#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>
#include "gameObject.h"
#include <string>
#include <GL/glew.h>
#include "settings.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

using namespace std;

class BatchSpriteRenderer {
private:
	unordered_map<const Shader*, vector<const GameObject *>> bigDumDum; // shaders to sprite batching
	unordered_map<string, Shader> shaderBank;
	unordered_map<string, const GameObject*> gameObjects;

	GLuint VAO;
	GLuint VBOs[3];
public:
	
	glm::mat4 projection = glm::ortho(0.0f, (float)settings::SCREEN_WIDTH, 0.0f, (float)settings::SCREEN_HEIGHT, -1.0f, 1.0f);
	
	//glm::mat4 model = glm::mat4(1.0f);

	void init();


	Shader* addShader(std::string name, std::string pathVert, std::string pathFrag);

	void addGameObject(std::string name, const GameObject* gameObject, const Shader* s);

	void draw() const;

	friend GameObject;
};

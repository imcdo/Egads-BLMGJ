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
	unordered_map<Shader*, vector<GameObject *>> bigDumDum; // shaders to sprite batching
	unordered_map<string, Shader> shaderBank;
	unordered_map<string, GameObject *> gameObjects;

	unsigned int VAO;
	unsigned int VBOs[2];
public:

	glm::mat4 projection = glm::ortho(0.0f, settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
	//glm::mat4 model = glm::mat4(1.0f);

	void init();


	Shader* addShader(std::string name, std::string pathVert, std::string pathFrag);

	void addGameObject(std::string name, GameObject* gameObject, Shader* s);

	void draw() const;

	friend GameObject;
};

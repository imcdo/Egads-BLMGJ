#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "gameObject.h"
#include "settings.h"

using namespace std;

class BatchSpriteRenderer {
private:
	unordered_map<const Shader*, vector<const GameObject *>> bigDumDum; // shaders to sprite batching
	unordered_map<string, Shader> shaderBank;
	unordered_map<string, const GameObject*> gameObjects;

	GLuint VAO;
	GLuint VBOs[3];

	static BatchSpriteRenderer* instance;

public:
	BatchSpriteRenderer();

	glm::mat4 projection = glm::ortho(0.0f, (float)settings::SCREEN_WIDTH, 0.0f, (float)settings::SCREEN_HEIGHT, -1.0f, 1.0f);
	
	//glm::mat4 model = glm::mat4(1.0f);

	static BatchSpriteRenderer* getInstance() { return instance;  }

	void init();


	Shader* addShader(std::string name, std::string pathVert, std::string pathFrag);
	Shader* getShader(std::string name);

	void addGameObject(std::string name, const GameObject* gameObject, const Shader* s);
	const GameObject* getGameObject(std::string name);
	void draw() const;


	friend GameObject;
};


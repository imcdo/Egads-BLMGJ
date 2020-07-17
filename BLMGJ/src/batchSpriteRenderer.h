#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>
#include "gameObject.h"
#include <string>
#include <GL/glew.h>

using namespace std;

class BatchSpriteRender {
private:
	unordered_map<Shader*, vector<GameObject>> bigDumDum; // shaders to sprite batching
	unordered_map<string, Shader> shaderBank;
	unordered_map<string, GameObject> gameObjects;

	unsigned int quadVAO;
public:
	void init() {
		unsigned int VBO;

		// dummy data for now
		float verticies[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glBindVertexArray(quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void addShader(std::string name, Shader shader) {
		shaderBank.insert({ name, shader });
		bigDumDum.insert({ &shader, std::vector<GameObject>() });
	}

	void addGameObject(std::string name, GameObject gameObject, Shader s) {
		gameObjects.insert({ name, gameObject });
		if (bigDumDum.find(&s) != bigDumDum.end())
			bigDumDum[&s].push_back(gameObject);
		else
			std::cout << "woops" << std::endl;
	}

	void draw() const {
		for (const pair<Shader*, vector<GameObject>>& renderPass : bigDumDum) {
			renderPass.first->use();
			for (const GameObject& gameObject : renderPass.second) {
				gameObject.draw(quadVAO);
			}
		}
	}

};

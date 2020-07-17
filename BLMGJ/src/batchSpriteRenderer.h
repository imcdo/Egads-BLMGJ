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

	unsigned int VAO;
public:
	void init() {
		unsigned int VBOs[2];

		// dummy data for now
		float verticies[] = {
			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
		};

		float tex[] = {
			0.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(2, &VBOs[0]);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex), tex, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}


	Shader* addShader(std::string name, std::string pathVert, std::string pathFrag) {
		shaderBank.emplace(std::make_pair( name, Shader(pathVert.c_str(), pathFrag.c_str())));
		bigDumDum.insert({ &shaderBank[name], std::vector<GameObject>() });
		return &shaderBank[name];
	}

	void addGameObject(std::string name, GameObject gameObject, Shader* s) {
		gameObjects.insert({ name, gameObject });
		if (bigDumDum.find(s) != bigDumDum.end())
			bigDumDum[s].push_back(gameObject);
		else
			std::cout << "woops" << std::endl;
	}

	void draw() const {
		for (const pair<Shader*, vector<GameObject>>& renderPass : bigDumDum) {
			renderPass.first->use();
			for (const GameObject& gameObject : renderPass.second) {
				gameObject.draw(VAO);
			}
		}
	}
};

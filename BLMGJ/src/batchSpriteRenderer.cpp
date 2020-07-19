#include <glm/gtc/matrix_transform.hpp>
#include "batchSpriteRenderer.h"
#include "settings.h"
#include "Time.h"

BatchSpriteRenderer::BatchSpriteRenderer() {
	
}

Shader* BatchSpriteRenderer::getShader(std::string name) {
	return &shaderBank[name];
}

const GameObject* BatchSpriteRenderer::getGameObject(std::string name) {
	return stringToGameObject[name];
}


void BatchSpriteRenderer::init() {
	std::vector<glm::vec2> verticies = {
		{-0.5, -0.5},
		{-0.5,  0.5},
		{ 0.5, -0.5},
		{ 0.5,  0.5}
	};

	std::vector<glm::vec2> tex = {
		{0.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
	};

	std::vector<glm::uvec3> idxs = {
		{0, 1, 2},
		{2, 1, 3}
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// initialize buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, &VBOs[0]);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * verticies.size(), verticies.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * tex.size(), tex.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uvec3) * idxs.size(), idxs.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader* sh = addShader("default",
		"src\\shaders\\default.vert",
		"src\\shaders\\default.frag");

	Shader* back = addShader("background",
		settings::BACKGROUND_GAME_VS,
		settings::BACKGROUND_GAME_FS);
}

Shader* BatchSpriteRenderer::addShader(std::string name, std::string pathVert, std::string pathFrag) {
	shaderBank.emplace(std::make_pair(name, Shader(pathVert.c_str(), pathFrag.c_str())));
	bigDumDum.insert({ &shaderBank[name], std::vector<GameObject *>() });

	// bind uniforms
	shaderBank[name].use();

	GLuint projectionId = glGetUniformLocation(shaderBank[name].id, "projection");
	glUniformMatrix4fv(projectionId, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 world = glm::mat4(1);
	world = glm::translate(world, glm::vec3(settings::SCREEN_WIDTH / 2, settings::SCREEN_HEIGHT / 2, 0));

	GLuint worldId = glGetUniformLocation(shaderBank[name].id, "world");
	glUniformMatrix4fv(worldId, 1, GL_FALSE, &world[0][0]);

	
	
	std::cout << "bound uniforms" << std::endl;
	return &shaderBank[name];
}

void BatchSpriteRenderer::addGameObject(std::string name, GameObject* gameObject, const Shader* s) {
	stringToGameObject.insert({ name,gameObject });
	if (bigDumDum.find(s) != bigDumDum.end())
		bigDumDum[s].push_back(gameObject);
	else
		std::cout << "woops" << std::endl;
}

void BatchSpriteRenderer::draw() const {
	glBindVertexArray(VAO);
	shaderBank.at("background").use();
	glUniform1f(glGetUniformLocation(shaderBank.at("background").id, "time"), Time::getCurrentTime());
	glUniform1f(glGetUniformLocation(shaderBank.at("background").id, "scale"), 2.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	for (const pair<const Shader*, vector<GameObject*>>& renderPass : bigDumDum) {
		renderPass.first->use();
		for (const GameObject* gameObject : renderPass.second) {
			gameObject->draw(renderPass.first);
		}
	}
	glBindVertexArray(0);

}

void BatchSpriteRenderer::remove(std::string name) {
	GameObject* go = nullptr;
	if (stringToGameObject.find(name) != stringToGameObject.end()) {
		go = stringToGameObject[name];
		stringToGameObject.erase(name);
	}

	for (auto& pair : bigDumDum) {
		auto idx = 0;
		for (GameObject* ptr : pair.second) {
			if (ptr == go) break;
			++idx;
		}
		if (idx != pair.second.size()) {
			pair.second.erase(pair.second.begin() + idx);
		}
	}


}

BatchSpriteRenderer* BatchSpriteRenderer::instance = new BatchSpriteRenderer();
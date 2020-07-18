#include "batchSpriteRenderer.h"

void BatchSpriteRenderer::init() {
	// dummy data for now

	std::vector<glm::vec2> verticies = {
		{-0.5f, 0.5f},
		{0.5f, -.5f},
		{-.5f, -.5f},


		{-0.5f, 0.5f},
		{0.5f, 0.5f},
		{0.5f, -0.5f}
	};



	std::vector<glm::vec2> tex = {
		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f},

		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, 0.0f}
	};

	// initialize buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, &VBOs[0]);

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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

Shader* BatchSpriteRenderer::addShader(std::string name, std::string pathVert, std::string pathFrag) {
	shaderBank.emplace(std::make_pair(name, Shader(pathVert.c_str(), pathFrag.c_str())));
	bigDumDum.insert({ &shaderBank[name], std::vector<GameObject *>() });

	// bind uniforms
	shaderBank[name].use();

	unsigned int projectionId = glGetUniformLocation(shaderBank[name].id, "projection");
	glUniformMatrix4fv(projectionId, 1, GL_FALSE, &projection[0][0]);

	
	std::cout << "bound uniforms" << std::endl;
	return &shaderBank[name];
}

void BatchSpriteRenderer::addGameObject(std::string name, GameObject* gameObject, Shader* s) {
	gameObjects.insert({ name,gameObject });
	if (bigDumDum.find(s) != bigDumDum.end())
		bigDumDum[s].push_back(gameObject);
	else
		std::cout << "woops" << std::endl;
}

void BatchSpriteRenderer::draw() const {
	glBindVertexArray(VAO);
	for (const pair<Shader*, vector<GameObject *>>& renderPass : bigDumDum) {
		renderPass.first->use();

		for (const GameObject* gameObject : renderPass.second) {
			gameObject->draw(renderPass.first);
		}
	}
}
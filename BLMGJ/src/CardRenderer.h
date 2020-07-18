#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "sprite.h"
#include "settings.h"
#include <vector>
#include <glm/glm.hpp>

class CardRenderer {
public:
	static GLuint drawCard() {
		CardRenderer& instance = getInstance();

		instance.setupToTexture();

		instance.shader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, instance.defaultCardBack.getTextureID());

		glBindVertexArray(instance.VAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		instance.revertFrameBuffer();
		return instance.deferredTexture;
	}
private:
	GLuint deferredFrameBuffer;
	GLuint deferredTexture;
	GLenum drawBuffer[1] = { GL_COLOR_ATTACHMENT0 };
	GLuint VAO;
	GLuint VBOs[2];
	Shader shader;
	Sprite defaultCardBack;

	static CardRenderer& getInstance() {
		static CardRenderer cr(CARD_DEFAULT_PATH_VS, CARD_DEFAULT_PATH_FS);
		return cr;
	}

	CardRenderer(const char* vs, const char* fs) : shader(vs, fs), defaultCardBack(CARD_DEFAULT_PATH_BACKGROUND) {
		glGenFramebuffers(1, &deferredFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, deferredFrameBuffer);
		glGenTextures(1, &deferredTexture);
		glBindTexture(GL_TEXTURE_2D, deferredTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CARD_WIDTH, CARD_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, deferredTexture, 0);
		glDrawBuffers(1, drawBuffer);

		std::vector<glm::vec2> verticies = {
		{-1.0f, 1.0f},
		{1.0f, -1.0f},
		{-1.0f, -1.0f},


		{-1.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, -1.0f}
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
	};

	void setupToTexture() {
		glBindFramebuffer(GL_FRAMEBUFFER, deferredFrameBuffer);
		glViewport(0, 0, CARD_WIDTH, CARD_HEIGHT);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void revertFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};

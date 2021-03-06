#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glew.h>

class OffScreenRender {
protected:
	GLuint deferredFrameBuffer = 0;
	GLuint deferredTexture = 0;
	GLenum drawBuffer[1] = { GL_COLOR_ATTACHMENT0 };
	GLuint VAO = 0;
	GLuint VBOs[2] = { 0,0 };
	OffScreenRender() {
		glGenFramebuffers(1, &deferredFrameBuffer);
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

	void makeNewTexture(int width, int height) {
		glGenTextures(1, &deferredTexture);
		glBindTexture(GL_TEXTURE_2D, deferredTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, deferredTexture, 0);
		glDrawBuffers(1, drawBuffer);
	}

	void setupToTexture(int width, int height) {
		glBindFramebuffer(GL_FRAMEBUFFER, deferredFrameBuffer);
		makeNewTexture(width, height);
		glViewport(0, 0, width, height);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void revertFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
};
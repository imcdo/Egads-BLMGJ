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
	static unsigned int drawCard();
private:
	GLuint deferredFrameBuffer;
	GLuint deferredTexture;
	GLenum drawBuffer[1] = { GL_COLOR_ATTACHMENT0 };
	GLuint VAO;
	GLuint VBOs[2];
	Shader shader;
	Sprite defaultCardBack;

	static CardRenderer& getInstance() {
		static CardRenderer cr(settings::CARD_DEFAULT_PATH_VS, settings::CARD_DEFAULT_PATH_FS);
		return cr;
	}

	CardRenderer(const char* vs, const char* fs);

	void setupToTexture();

	void revertFrameBuffer();
};

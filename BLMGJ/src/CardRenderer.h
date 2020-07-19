#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "sprite.h"
#include "settings.h"
#include <vector>
#include <glm/glm.hpp>
#include "OffScreenRender.h"
#include <map>

class CardRenderer : public OffScreenRender {
public:
	static Sprite drawCard(std::string name, std::string description, std::string spriteName, int durability, int rarity, settings::COLOR color = settings::COLOR_WHITE) {
		return drawCard(name, description, spriteName, durability, rarity, settings::colors[color]);
	}
	static Sprite drawCard(std::string name, std::string description, std::string spriteName, int durability, int rarity, glm::vec3 color);
private:
	Shader shader;
	Shader cardBackShader;
	Sprite defaultCardBack;
	std::map<std::string, GLuint> cache;


	static CardRenderer& getInstance() {
		static CardRenderer cr(settings::CARD_DEFAULT_PATH_VS, settings::CARD_DEFAULT_PATH_FS);
		return cr;
	}

	CardRenderer(const char* vs, const char* fs);
	Sprite renderFromCache(std::string name, int durability);
};

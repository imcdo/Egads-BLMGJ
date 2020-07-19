#pragma once
#include "settings.h"
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include "shader.h"
#include "OffScreenRender.h"

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class TextManager : public OffScreenRender {
public:
	static GLuint renderText(std::string text, float size, glm::ivec2 textureSize = { 200,200 }, glm::vec2 topLeft = { -1.0,1.0 }, glm::vec2 topRight = { 1.0, 1.0 }, std::string font = "default");
	static void loadFont(std::string name, std::string path);
private:
	Shader textShader;
	std::map<std::string, std::map<char, Character>> fonts;
	FT_Library freeType;
	TextManager();

	std::vector<Character> charactersForString(std::string input, std::string font = "default");

	static TextManager& getInstance() {
		static TextManager tm;
		return tm;
	}
};
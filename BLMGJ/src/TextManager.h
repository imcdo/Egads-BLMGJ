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

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class TextManager {
public:

	static std::vector<Character> charactersForString(std::string input, std::string font = "default") {
		TextManager& tm = getInstance();
		if (std::strcmp(font.c_str(), "default") == 0) {
			if (tm.fonts.find(font) == tm.fonts.end()) {
				loadFont("default", settings::FONT_DEFAULT_PATH);
			}
		}
		std::map<char, Character>& fontTable = tm.fonts[font];
		std::vector<Character> message;
		for (char& c : input) {
			message.push_back(tm.fonts[font][c]);
		}
		return message;
	}

	static void loadFont(std::string name, std::string path) {
		TextManager& tm = getInstance();

		FT_Face newFont;
		if (FT_New_Face(tm.freeType, path.c_str(), 0, &newFont)) {
			std::cout << "ERROR: FREETYPE COULDN'T LOAD " << name << " " << path << std::endl;
		}

		FT_Set_Pixel_Sizes(newFont, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		std::map<char, Character> font;

		for (unsigned char i = 0; i < 127; i++) {
			if (FT_Load_Char(newFont, i, FT_LOAD_RENDER)) {
				std::cout << "ERROR: NO GLYPTH FOR " << i;
			}

			// Texture generation
			GLuint tex;
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 
				newFont->glyph->bitmap.width, newFont->glyph->bitmap.rows, 
				0, GL_RED, GL_UNSIGNED_BYTE, newFont->glyph->bitmap.buffer);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = { tex, glm::ivec2(newFont->glyph->bitmap.width, newFont->glyph->bitmap.rows),
				glm::ivec2(newFont->glyph->bitmap_left, newFont->glyph->bitmap_top), newFont->glyph->advance.x };

			font.insert(std::make_pair(i, character));
		}

		tm.fonts.insert(std::make_pair(name, font));

		FT_Done_Face(newFont);
	}
private:
	std::map<std::string, std::map<char, Character>> fonts;
	FT_Library freeType;
	TextManager() : freeType() {
		if (FT_Init_FreeType(&freeType)) {
			std::cout << "ERROR: FREETYPE COULDN'T INIT" << std::endl;
		}
	};

	static TextManager& getInstance() {
		static TextManager tm;
		return tm;
	}
};
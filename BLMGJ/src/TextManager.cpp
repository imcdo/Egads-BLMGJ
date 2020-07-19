#include "TextManager.h"



std::vector<Character> TextManager::charactersForString(std::string input, std::string font) {
	if (std::strcmp(font.c_str(), "default") == 0) {
		if (fonts.find(font) == fonts.end()) {
			loadFont("default", settings::FONT_DEFAULT_PATH);
		}
	}
	std::map<char, Character>& fontTable = fonts[font];
	std::vector<Character> message;
	for (char& c : input) {
		message.push_back(fonts[font][c]);
	}
	return message;
}

GLuint TextManager::renderText(std::string text, float size, glm::ivec2 textureSize, glm::vec2 topLeft, glm::vec2 topRight, std::string font) {
	TextManager& tm = getInstance();
	tm.setupToTexture(textureSize.x, textureSize.y);
	std::vector<Character> textCharacter = tm.charactersForString(text, font);
	glm::vec2 curPos = topLeft;
	glm::vec2 letterPos = curPos;
	glm::vec2 scale = { 1.0, 1.0 };

	tm.textShader.use();
	glBindVertexArray(tm.VAO);

	for (const Character& ch : textCharacter) {
		letterPos.x += ch.Bearing.x * size;
		letterPos.y -= (ch.Size.y - ch.Bearing.y) * size;
		scale.x = ch.Size.x * size;
		scale.y = ch.Size.y * size;
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glUniform2fv(glGetUniformLocation(tm.textShader.id, "pos"), 1, &letterPos[0]);
		glUniform2fv(glGetUniformLocation(tm.textShader.id, "scale"), 1, &scale[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		curPos.x += (ch.Advance >> 6) * size;
		if (curPos.x - 0.01 > topRight.x) {
			curPos.x = topLeft.x;
			curPos.y -= size * 120;
		}
		letterPos = curPos;
	}
	tm.revertFrameBuffer();
	return tm.deferredTexture;
}

void TextManager::loadFont(std::string name, std::string path) {
	TextManager& tm = getInstance();
	if (tm.fonts.find(name) != tm.fonts.end()) {
		//std::cout << "We already have this font loaded" << std::endl;
		return;
	}
	FT_Face newFont;
	if (FT_New_Face(tm.freeType, path.c_str(), 0, &newFont)) {
		std::cout << "ERROR: FREETYPE COULDN'T LOAD " << name << " " << path << std::endl;
	}

	FT_Set_Pixel_Sizes(newFont, 0, 96);

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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Character character = { tex, glm::ivec2(newFont->glyph->bitmap.width, newFont->glyph->bitmap.rows),
			glm::ivec2(newFont->glyph->bitmap_left, newFont->glyph->bitmap_top), newFont->glyph->advance.x };

		font.insert(std::make_pair(i, character));
	}

	tm.fonts.insert(std::make_pair(name, font));

	FT_Done_Face(newFont);
}

TextManager::TextManager() : OffScreenRender(), freeType(), textShader(settings::TEXT_DEFAULT_VS, settings::TEXT_DEFAULT_FS) {
	if (FT_Init_FreeType(&freeType)) {
		std::cout << "ERROR: FREETYPE COULDN'T INIT" << std::endl;
	}

}

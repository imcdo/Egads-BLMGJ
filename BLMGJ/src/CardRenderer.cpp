#include "CardRenderer.h"
#include "TextManager.h"
GLuint CardRenderer::drawCard(std::string name, std::string description, std::string spriteName, int durability, int rarity, glm::vec3 color) {
	CardRenderer& instance = getInstance();
	if (instance.cache.find(name) != instance.cache.end()) {
		return instance.renderFromCache(name, durability);
	}

	Sprite icon(spriteName);
	if (rarity < 1) throw std::exception("Come on, I thought we agreed to only accept positive rarity?");
	Sprite border(settings::CARD_DEFAULT_PATH_BORDER[rarity-1]);

	TextManager::loadFont("thin", "src\\fonts\\thinner.ttf");
	glm::ivec2 texSize(settings::CARD_WIDTH, settings::CARD_HEIGHT);
	GLuint nameTex = TextManager::renderText(name, 0.002f, texSize, glm::vec2(-0.9, 0.05), glm::vec2(0.9, 0.05));
	GLuint descTex = TextManager::renderText(description, 0.0015f, texSize, glm::vec2(-0.9, -0.1), glm::vec2(0.9, -0.1), "thin");
	GLuint durabilityText = TextManager::renderText(std::to_string(durability), 0.002f, texSize, glm::vec2(-0.1, -0.8), glm::vec2(0.9, -0.8));

	instance.setupToTexture(settings::CARD_WIDTH, settings::CARD_HEIGHT);

	instance.shader.use();

	glBindVertexArray(instance.VAO);

	glActiveTexture(GL_TEXTURE0);

	instance.cardBackShader.use();
	glUniform3fv(glGetUniformLocation(instance.cardBackShader.id, "colorTint"), 1, &color.x);
	glBindTexture(GL_TEXTURE_2D, instance.defaultCardBack.getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	instance.shader.use();
	glBindTexture(GL_TEXTURE_2D, border.getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, nameTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, descTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glViewport(settings::CARD_WIDTH / 4, settings::CARD_HEIGHT / 3 * 2, settings::CARD_WIDTH / 2, settings::CARD_WIDTH / 2);
	glBindTexture(GL_TEXTURE_2D, icon.getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glViewport(0, 0, settings::CARD_WIDTH, settings::CARD_HEIGHT);
	
	instance.cache.insert(make_pair(name, instance.deferredTexture));
	// Here is where the variable stuff gets bound, so we'll save to cache before
	instance.setupToTexture(settings::CARD_WIDTH, settings::CARD_HEIGHT);
	glBindTexture(GL_TEXTURE_2D, instance.cache[name]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, durabilityText);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);

	instance.revertFrameBuffer();
	return instance.deferredTexture;
}

CardRenderer::CardRenderer(const char* vs, const char* fs) : OffScreenRender(), shader(vs, fs), defaultCardBack(settings::CARD_DEFAULT_PATH_BACKGROUND), cardBackShader(settings::CARD_DEFAULT_PATH_VS, settings::CARD_DEFAULT_PATH_FS_BACK) {
}

GLuint CardRenderer::renderFromCache(std::string name, int durability) {
	// Faster render, no need to do the text
	glm::ivec2 texSize(settings::CARD_WIDTH, settings::CARD_HEIGHT);
	GLuint durabilityText = TextManager::renderText(std::to_string(durability), 0.002f, texSize, glm::vec2(-0.1, -0.8), glm::vec2(0.9, -0.8));

	setupToTexture(settings::CARD_WIDTH, settings::CARD_HEIGHT);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cache[name]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, durabilityText);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	revertFrameBuffer();
	return deferredTexture;
}

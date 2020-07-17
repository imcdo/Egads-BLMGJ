#pragma once
#include <string>
#include <GL/glew.h>

typedef enum SpriteType {
	Default,
	Transparent
} SpriteType;


struct LoadSpriteData {
	int height;
	int width;
	unsigned int textureID;

	LoadSpriteData() = default;
};

class Sprite {
private:

	
	LoadSpriteData _loadData;
	LoadSpriteData TextureFromFile(const char* path, const std::string& directory, bool gamma);
	int height;
	int width;
	unsigned int textureID;
public:

	const SpriteType spriteType;
	
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	int getTextureID() const { return textureID;  }

	Sprite(std::string path, SpriteType spriteType = Default);
	Sprite(const Sprite& s) = default;
	Sprite& operator= (const Sprite& s);

};
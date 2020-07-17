#pragma once
#include <string>
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

	
	const LoadSpriteData _loadData;
	LoadSpriteData TextureFromFile(const char* path, const std::string& directory, bool gamma);

public:

	const SpriteType spriteType;
	const int height;
	const int width;
	const unsigned int textureID;


	Sprite(std::string path, SpriteType spriteType = Default);
	Sprite(const Sprite& s) = default;
};
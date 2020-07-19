#pragma once
#include <glm/glm.hpp>

namespace settings {
	constexpr int SCREEN_WIDTH = 1280;
	constexpr int SCREEN_HEIGHT = 720;

	constexpr int PLAYER_HEALTH = 50;
	constexpr int HAND_SIZE = 4;
	constexpr int DECK_SIZE = 20;

	constexpr int CARD_WIDTH = 900;
	constexpr int CARD_HEIGHT = 1400;
	constexpr const char* CARD_DEFAULT_PATH_VS = "src\\shaders\\cardBackDefault.vert";
	constexpr const char* CARD_DEFAULT_PATH_FS = "src\\shaders\\cardBackDefault.frag";
	constexpr const char* CARD_DEFAULT_PATH_FS_BACK = "src\\shaders\\cardBackHueShift.frag";
	constexpr const char* TEXT_DEFAULT_FS = "src\\shaders\\cardTextDefault.frag";
	constexpr const char* TEXT_DEFAULT_VS = "src\\shaders\\cardTextDefault.vert";

	constexpr const char* CARD_DEFAULT_PATH_BACKGROUND = "src\\sprites\\uwu.png";

	constexpr const char* FONT_DEFAULT_PATH = "src\\fonts\\default.TTF";

	constexpr glm::vec3 colors[] = { glm::vec3(1.0,1.0,1.0),
										glm::vec3(1.0,0.0,0.0),
										glm::vec3(0.0,1.0,0.0),
										glm::vec3(0.0,0.0,1.0) };
	enum COLOR { COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_BLUE };

	constexpr const char* const CARD_DEFAULT_PATH_BORDER[] = { "src\\sprites\\BORDERBORDER.png", 
										"src\\sprites\\BORDERBORDER.png",
										"src\\sprites\\BORDERBORDER.png",
										"src\\sprites\\BORDERBORDER.png",
										"src\\sprites\\BORDERBORDER.png" };
}
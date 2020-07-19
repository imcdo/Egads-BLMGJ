#pragma once

namespace settings {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 400;

	constexpr int PLAYER_HEALTH = 50;
	constexpr int HAND_SIZE = 4;
	constexpr int DECK_SIZE = 20;

	constexpr int CARD_WIDTH = 900;
	constexpr int CARD_HEIGHT = 1400;
	constexpr const char* CARD_DEFAULT_PATH_VS = "src\\shaders\\cardBackDefault.vert";
	constexpr const char* CARD_DEFAULT_PATH_FS = "src\\shaders\\cardBackDefault.frag";

	constexpr const char* CARD_DEFAULT_PATH_BACKGROUND = "src\\sprites\\uwu.png";

	constexpr const char* FONT_DEFAULT_PATH = "src\\fonts\\default.TTF";
}
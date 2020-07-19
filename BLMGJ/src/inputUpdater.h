#pragma once
#include <vector>
#include "game.h"

class InputUpdater {
private:
	static std::vector<InputUpdater*> _inputUpdaters;
	int _iu_idx;
public:
	virtual void MouseInput(int key, int action) = 0;
	InputUpdater();
	~InputUpdater();

	friend Game;
};
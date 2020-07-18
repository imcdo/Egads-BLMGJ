#pragma once
#include <vector>
#include "game.h"

class FrameUpdater {
private:
	static std::vector<FrameUpdater *> _frameUpdaters;
	int _fu_idx;
public:
	virtual void Update() = 0;
	FrameUpdater();
	~FrameUpdater();

	friend Game;
};
#pragma once

#include <vector>
#include "game.h"

class CursorMoveUpdater {
private:
	static std::vector<CursorMoveUpdater*> _cursorMoveUpdaters;
	int _cmu_idx;
public:
	virtual void CursorMove(float x, float y) = 0;
	CursorMoveUpdater();
	~CursorMoveUpdater();

	friend Game;
};

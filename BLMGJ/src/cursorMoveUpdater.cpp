#include "CursorMoveUpdater.h"

std::vector<CursorMoveUpdater*>CursorMoveUpdater::_cursorMoveUpdaters = {};


CursorMoveUpdater::CursorMoveUpdater() {
	_cmu_idx = _cursorMoveUpdaters.size();
	_cursorMoveUpdaters.push_back(this);
}

CursorMoveUpdater::~CursorMoveUpdater() {
	_cursorMoveUpdaters.erase(_cursorMoveUpdaters.begin() + _cmu_idx, _cursorMoveUpdaters.begin() + _cmu_idx + 1);
}
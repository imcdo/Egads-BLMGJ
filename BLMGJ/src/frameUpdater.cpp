#include "frameUpdater.h"

std::vector<FrameUpdater*>FrameUpdater::_frameUpdaters = {};


FrameUpdater::FrameUpdater() {
	_fu_idx = _frameUpdaters.size();
	_frameUpdaters.push_back(this);
}

FrameUpdater::~FrameUpdater() {
	_frameUpdaters.erase(_frameUpdaters.begin() + _fu_idx);
	for (std::vector<FrameUpdater*>::iterator it = _frameUpdaters.begin() + _fu_idx; it < _frameUpdaters.end(); ++it) {
		--((*it)->_fu_idx);
	}
}
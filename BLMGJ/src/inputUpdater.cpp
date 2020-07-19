#include "inputUpdater.h"

std::vector<InputUpdater*>InputUpdater::_inputUpdaters = {};


InputUpdater::InputUpdater() {
	_iu_idx = _inputUpdaters.size();
	_inputUpdaters.push_back(this);
}

InputUpdater::~InputUpdater() {
	_inputUpdaters.erase(_inputUpdaters.begin() + _iu_idx);
}
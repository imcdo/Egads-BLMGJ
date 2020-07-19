#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "frameUpdater.h"


class Time : public FrameUpdater{
public:
	static float getCurrentTime() {
		return instance->getCurrentTimeHelper();
	}
	static float getDeltaTime() {
		return instance->getDeltaTimeHelper();
	}


private:
	static Time* instance;
	float currentTime, prevTime, deltaTime = 0;

	float getCurrentTimeHelper() {
		prevTime = currentTime;
		currentTime = glfwGetTime();
		return currentTime;
	}

	float getDeltaTimeHelper() {
		deltaTime = currentTime - prevTime;
		return deltaTime;
	}

public:
	void Update() override {
		getCurrentTime();
		// std::cout << "Time update " << getDeltaTime() << std::endl;
	}

};

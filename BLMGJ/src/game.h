#pragma once
#include <GLFW/glfw3.h>

class Game {
private:
    GLFWwindow* window;

public:
    Game() = default;

    void init();
    void loop();
    void cleanup();

};
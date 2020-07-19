#pragma once
#include <GLFW/glfw3.h>

class Game {
private:
    GLFWwindow* window;
    static void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCursorCallback(GLFWwindow* window, double mouseX, double mouseY);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
public:
    Game() = default;

    void init();
    void loop();
    void cleanup();

};
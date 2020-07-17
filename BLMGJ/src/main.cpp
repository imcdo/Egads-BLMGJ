#include <iostream>
#include <GLFW/glfw3.h>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HIGHT = 400;

class Game {
private:
    GLFWwindow* window;
public:
   


    Game() = default;
    void init() {
        /* Initialize the library */
        if (!glfwInit())
            throw std::exception("window initialization failure");


        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Hello World", NULL, NULL);
        if (!window) {
            glfwTerminate();
            throw std::exception("window creation failure");
        }
    }

    void loop() {
        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    
    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};


int main(void) {
    try {
        Game game;
        game.init();
        game.loop();
        game.cleanup();
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}
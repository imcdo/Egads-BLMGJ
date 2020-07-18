#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gameObject.h";
#include "sprite.h";
#include "batchSpriteRenderer.h"
#include "shader.h"
#include "settings.h"
#include "game.h"
#include "frameUpdater.h"
#include "hand.h"
#include "monsterData.h"
#include "battlefield.h"
// #include "monsterData.cpp";

Hand* hand;
Card* nextDraw;
static void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        hand->drawCard(nextDraw);
        nextDraw++;
    }
}


void Game::init() {
    /* Initialize the library */
    if (!glfwInit())
        throw std::exception("window initialization failure");


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow((int)settings::SCREEN_WIDTH, (int)settings::SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::exception("window creation failure");
    }
        
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cerr << "Error initializing GLEW! %s\n" << glewGetErrorString(glewError) << std::endl;
		exit(-1);
	}

	//Sometimes glew just throws errors, so we'll clear them
	glGetError();
}

void Game::loop() {
    Sprite s = Sprite("src\\sprites\\UwU.png");
    Sprite ms = Sprite("src\\sprites\\mat.png");


    BatchSpriteRenderer sr = BatchSpriteRenderer();
    sr.init();

    GameObject test = GameObject(0, 0, s, { 5,5 });
    Shader* sh = sr.addShader("default", 
        "src\\shaders\\default.vert",
        "src\\shaders\\default.frag");
    Hand h = Hand(Math::Rect({-300,-300}, {300,100}));
    hand = &h;

    GameObject mat = GameObject(0, -100, ms, { 100, 100 });
    sr.addGameObject("mat", &mat, sh);

    std::vector<Card> cards = { Card(-300,0,s, {1,1}),Card(-300,0,s, {3,6}), Card(-300,0,s, {3,6}), Card(-300,0,s, {3,6}), Card(-300,0,s, {3,6}), };
    size_t idx = 0;
    nextDraw = &cards[2];

    glfwSetKeyCallback(window, inputCallback);

    h.drawCard(&cards[idx]);
    for (const Card& c : cards) {
        sr.addGameObject("card " + idx++, &c, sh);
    }
    sr.addGameObject("test", &test, sh);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);


        /* Render here */
        sr.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
             
        // test.scale({ .99f, .99f });
        // test.rotate(.01f);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            test.move(0, 2);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            test.move(-2, 0);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            test.move(0, -2);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            test.move(2, 0);

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            test.rotate(1);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            test.rotate(-1);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            test.scale({ 1.25f, 1.25f });
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            test.scale({.8f, .8f});

        for (FrameUpdater* fu : FrameUpdater::_frameUpdaters) fu->Update();
    }

}
    
void Game::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}


int main(void) {
    try {
		Battlefield grid = Battlefield(0, 0, Sprite(""));
		//Bestiary();

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
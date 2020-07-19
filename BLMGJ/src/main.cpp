#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gameObject.h"
#include "sprite.h"
#include "batchSpriteRenderer.h"
#include "shader.h"
#include "settings.h"
#include "game.h"
#include "frameUpdater.h"
#include "hand.h"
#include "monsterData.h"
#include "battlefield.h"
#include "player.h"
#include "projectile.h"
#include "shooter.h"
#include "inputUpdater.h"

float _currentMouseX;
float _currentMouseY;
float _lastMouseX;
float _lastMouseY;
 

// should be in player
//Hand* hand;
//Card* nextDraw;

Player* player;

//don't need dis
/*
void Game::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        hand->drawCard(nextDraw);
        nextDraw++;
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        nextDraw->warp(100, 200);
    }
    for (InputUpdater* iu : InputUpdater::_inputUpdaters) iu->MouseInput(key, action);
}
*/

void Game::mouseCursorCallback(GLFWwindow* window, double mouseX, double mouseY) {
    _lastMouseX = _currentMouseX;
    _lastMouseY = _currentMouseY;

    _currentMouseX = mouseX - settings::SCREEN_WIDTH / 2;
    _currentMouseY = settings::SCREEN_HEIGHT / 2 - mouseY;

    for (CursorMoveUpdater* cmu : CursorMoveUpdater::_cursorMoveUpdaters) cmu->CursorMove(_currentMouseX, _currentMouseY);

}

void Game::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        for (Card* c : player->getHand().cards) {
            
            
            if (c->getRect().Contains(glm::vec2(_currentMouseX , _currentMouseY))) {
                player->cardPlayInputHandler(c);
                break;
            }
        }
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

    BatchSpriteRenderer* sr = BatchSpriteRenderer::getInstance();
    sr->init();
}

void Game::loop() {
    Sprite s = Sprite("src\\sprites\\UwU.png");
    Sprite ms = Sprite("src\\sprites\\mat.png");

    Sprite shooterSprite = Sprite("src\\sprites\\shooter.png", Default, 2);

    BatchSpriteRenderer& sr = *BatchSpriteRenderer::getInstance();
    //sr->init();
    
    /*Shader* sh = sr.addShader("default", 
        "src\\shaders\\default.vert",
        "src\\shaders\\default.frag");*/
    Shader* sh = sr.getShader("default");
    sr.addShader("cardStuff", "src\\shaders\\default.vert", "src\\shaders\\cardInHandShader.frag");
    Shader* handShader = sr.getShader("cardStuff");


    GameObject mat = GameObject(0, -settings::SCREEN_HEIGHT / 2 + 100, ms, { 100, 100 });
    Shooter shooter = Shooter(0, -settings::SCREEN_HEIGHT / 2 + mat.getRect().getHeight(), shooterSprite, { 2,2 });
    sr.addGameObject("mat", &mat, sh);
    std::cout << mat.getRect().getMin().x << " "
        << mat.getRect().getMin().y << " | "
        << mat.getRect().getMax().x << " "
        << mat.getRect().getMax().y << std::endl;

	//Battlefield grid = Battlefield(0, 0, s, { 1,1 }, 0, 0, 50, 50, 1);
	Battlefield grid = Battlefield(0, 0, s, { 1,1 }, 0, 0, 35, 14, 32);
	grid.Populate(0.5f);
    Bestiary bestiary = Bestiary();
    Player p = Player(&bestiary, &grid, mat.getRect(), { -350, -settings::SCREEN_HEIGHT / 2 + mat.getRect().getHeight() }, { 350,-settings::SCREEN_HEIGHT / 2 + mat.getRect().getHeight() });

    MonsterData* testMonster = GetBestiary()->getRandomMonster();
    Card* testCard = new Card(-350, 200, "src\\sprites\\UwU.png", { 5,5 }, 0, 0, testMonster);


    Projectile test = Projectile(0, -400, s, { 2,2 }, 0, 0, testMonster, { 1,1 }, &grid, testCard);
	sr.addGameObject("proj ", &test, sh);

    test.active = true;
    player = &p;

    

    //glfwSetKeyCallback(window, inputCallback);
    glfwSetCursorPosCallback(window, mouseCursorCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);


    sr.addGameObject("shooter", &shooter, sh);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);


        /* Render here */
        sr.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
             
        for (FrameUpdater* fu : FrameUpdater::_frameUpdaters) fu->Update();

    }

}
    
void Game::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}


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
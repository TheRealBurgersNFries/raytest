#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "inc/IDrawable.hpp"
#include "inc/Background.hpp"
#include "inc/Sprite.hpp"


int windowWidth = 1920;
int windowHeight = 1080;
std::string windowTitle = "RayTest";

std::mutex stacklock;

DrawStack stack = DrawStack();

Vector2 playerPos;
float playerSpeed = 200.0f;
Sprite playerSprite = Sprite(BLUE);
bool running;

void render() {

}

void game() {
    float dt = 0.0167;
    while(running) {
        playerPos = playerSprite.getPosition();
        if (IsKeyDown(KEY_UP)) 
            playerPos.y -= playerSpeed * dt;
        if (IsKeyDown(KEY_LEFT))
            playerPos.x -= playerSpeed * dt;
        if (IsKeyDown(KEY_DOWN)) 
            playerPos.y += playerSpeed * dt;
        if (IsKeyDown(KEY_RIGHT)) 
            playerPos.x += playerSpeed * dt;

        if (playerPos.x < 0)  playerPos.x = 0;
        if (playerPos.y < 0)  playerPos.y = 0;
        if (playerPos.x > windowWidth) playerPos.x = windowWidth;
        if (playerPos.y > windowHeight) playerPos.x = windowHeight;
        stacklock.lock();
        playerSprite.setPosition(playerPos);
        stacklock.unlock();
    }
}
int main(int argc, char* argv[]) {
 

    
    stacklock.lock();
    Background bg = Background(RED);
    bg.setZHeight(0);
    stack.addToStack(&bg);

    playerSprite.setPosition({400, 200});
    stack.addToStack(&playerSprite);
    stacklock.unlock();

    running = true;
    std::thread gameThread = std::thread(game);
    gameThread.join();

    float dt;
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        
        //processEngineUpdates();
        dt = GetFrameTime();
        stacklock.lock();
        stack.Draw();
        stacklock.unlock();

    }
    CloseWindow();
    return 0;
}
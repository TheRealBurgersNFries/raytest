#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "inc/IDrawable.hpp"
#include "inc/Background.hpp"
#include "inc/Sprite.hpp"

#define THREAD_ATTEMPT

int windowWidth = 1920;
int windowHeight = 1080;
std::string windowTitle = "RayTest";

std::mutex stacklock;

DrawStack stack = DrawStack();

Vector2 playerPos;
float playerSpeed = 2000.0f;
Sprite playerSprite = Sprite(BLUE);
bool running;

std::array<bool,338> inputs;


void processInputs() {
    float engineTick = 0.0167f;
    while(running) {
        playerPos = playerSprite.getPosition();
        if (inputs.at(KEY_UP)) 
            playerPos.y -= playerSpeed * engineTick;
        if (inputs.at(KEY_LEFT))
            playerPos.x -= playerSpeed * engineTick;
        if (inputs.at(KEY_DOWN)) 
            playerPos.y += playerSpeed * engineTick;
        if (inputs.at(KEY_RIGHT)) 
            playerPos.x += playerSpeed * engineTick;

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


    

    float dt;
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        #ifdef THREAD_ATTEMPT
        if (!running) {
            running = true;
            std::thread inputProcessor(processInputs);
            inputProcessor.detach();
        } 
        #endif
    
        //processEngineUpdates();
        dt = GetFrameTime();
        stacklock.lock();
        stack.Draw();
        #ifdef THREAD_ATTEMPT
        stack.getInputs(&inputs);
        #else
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
        if (playerPos.y > windowHeight) playerPos.y = windowHeight;
        
        playerSprite.setPosition(playerPos);
        #endif
        stacklock.unlock();
        
    }
    running = false;
    CloseWindow();
    return 0;
}
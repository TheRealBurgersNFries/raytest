#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
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
float playerSpeed = 200.0f;
Sprite playerSprite = Sprite(BLUE);
std::atomic<bool> running = false;

std::array<bool,338> inputs;


void processInputs() {
    float engineTick = 0.0167f;
    while(running) {
        playerPos = playerSprite.getPosition();
        stacklock.lock();
        stack.getInputs(&inputs);
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
        playerSprite.setPosition(playerPos);
        stacklock.unlock();
        inputs.fill(false);
    }
}

int main(int argc, char* argv[]) {
    
    Background bg = Background(RED);
    bg.setZHeight(0);
    
    playerSprite.setPosition({400, 200});
    playerSprite.setZHeight(200);
    
    stacklock.lock();
    stack.addToStack(&bg);
    stack.addToStack(&playerSprite);
    stacklock.unlock();

    float dt;
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);
    #ifdef THREAD_ATTEMPT
    std::thread inputProcessor(processInputs);
    #endif
    while (!WindowShouldClose()) {
        #ifdef THREAD_ATTEMPT
        if (!running) {
            running = true;
            inputProcessor.detach();
        } 
        #endif
    
        //processEngineUpdates();
        dt = GetFrameTime();
        stacklock.lock();
        stack.Draw();
        #ifndef THREAD_ATTEMPT
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
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        
    }
    running = false;
    #ifdef THREAD_ATTEMPT
    inputProcessor.join();
    #endif
    CloseWindow();
    return 0;
}
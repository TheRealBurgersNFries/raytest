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


void inputThread() {
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

void renderThread() {
    float dt;
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
    
        //processEngineUpdates();
        dt = GetFrameTime();
        stacklock.lock();
        stack.Draw();
        
        stacklock.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    CloseWindow();
    running = false;
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
    running = true;
    std::thread T_InputThread(inputThread);
    std::thread T_RenderThread(renderThread);
    T_InputThread.detach();
    T_RenderThread.detach();
    while(running) {

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    if (T_InputThread.joinable())
        T_InputThread.join();
    if (T_RenderThread.joinable())
        T_RenderThread.join();
    
    return 0;
}
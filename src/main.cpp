#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

#include "raylib.h"

#include "inc/IDrawable.hpp"
#include "inc/Background.hpp"
#include "inc/Sprite.hpp"
#include "inc/T_Render.hpp"

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

int main(int argc, char* argv[]) {
    
    Background bg = Background(RED);
    bg.setZHeight(0);
    
    playerSprite.setPosition({400, 200});
    playerSprite.setZHeight(200);
    
    stacklock.lock();
    stack.addToStack(&bg);
    stack.addToStack(&playerSprite);
    stacklock.unlock();
    T_Render renderer(&running, 1920, 1080, "raytest", 60, &stack);
    
    running = true;
    renderer.Start();
    std::thread T_InputThread(inputThread);
    T_InputThread.detach();
    while(running) {

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    renderer.Kill();
    if (T_InputThread.joinable())
        T_InputThread.join();
    
    
    return 0;
}
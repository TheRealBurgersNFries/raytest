
#include <cmath>

#include "inc/T_Render.hpp"



T_Render::T_Render(std::atomic<bool>* running, int width, int height,
    std::string title, int target, DrawStack* stack) {
        p_running = running;
        _windowWidth = width;
        _windowHeight = height;
        _Title = title;
        _targetFrameRate = target;
        _targetFrameTime =  std::ceil(1000000.0f / target);
        _stack = stack;
    }

void T_Render::renderThread() {
    InitWindow(_windowWidth, _windowHeight, _Title.c_str());
    SetTargetFPS(_targetFrameRate);
    const auto interval = std::chrono::microseconds(_targetFrameTime);
    while (!WindowShouldClose() && p_running && render) {
        auto startTime = std::chrono::steady_clock::now();
        {
            std::lock_guard<std::mutex> lock(m_stackLock);
            _stack->Draw();
        }
        auto endTime = std::chrono::steady_clock::now();
        auto elapsed = endTime - startTime;
        _renderTimeuS =  (std::chrono::duration_cast<std::chrono::microseconds>(elapsed)).count();
        if (elapsed < interval)
            std::this_thread::sleep_for(interval - elapsed);

    }
}

int T_Render::getFrameTime() {
    return _renderTimeuS;
}

int T_Render::getFrameRate() {
    return _realFrameRate;
}

void T_Render::Start() {
    render = true;
    T_RenderThread = std::thread(&T_Render::renderThread, this);
    T_RenderThread.detach();
}

void T_Render::Kill() {
    if (T_RenderThread.joinable()){
        render = false;
        T_RenderThread.join();
    }
        
}
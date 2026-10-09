#ifndef RENDER_THREAD_H
#define RENDER_THREAD_H

#include <string>

#include <thread>
#include <atomic>
#include <mutex>

#include "raylib.h"

#include "IDrawable.hpp"


class T_Render {
    private:
        int _renderTimeuS;
        int _realFrameRate;
        
        DrawStack* _stack;
        
        std::atomic<bool>* p_running;
        std::atomic<bool> _render;
        std::atomic<bool>* p_inputsAvailable; 
        std::mutex m_stackLock;

        int _windowWidth;
        int _windowHeight;
        int _targetFrameRate;
        int _targetFrameTime;
        std::string _Title;
        std::thread T_RenderThread;
        void renderThread();

    public:
        T_Render(std::atomic<bool>* running, int width, int height, 
            std::string title, int target, DrawStack* stack, std::atomic<bool>* inputs);
        int getFrameTime();
        int getFrameRate();
        void Start();
        void Kill();
};



#endif //RENDER_THREAD_H
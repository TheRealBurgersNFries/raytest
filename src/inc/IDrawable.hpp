#ifndef INTERFACE_DRAWABLE_H
#define INTERFACE_DRAWABLE_H

#include "raylib.h"
#include <vector>
#include <array>


class DrawStack;
class IDrawable;

class DrawStack {
    private:
        std::vector<IDrawable*> drawList;
        std::vector<IDrawable*> addList;
        std::vector<IDrawable*> subList;
        std::array<bool,338> inputs;
    public:
        void Draw();

        void addToStack(IDrawable *drawable);
        void removeFromStack(IDrawable *drawable);

        void getInputs(std::array<bool,338> *array);
        
        DrawStack();
};

class IDrawable {
    private:
        int heightZ;
        DrawStack* stack;
        bool inStack = false;
    public:
        virtual ~IDrawable() = default;
        virtual void Draw() const = 0;

        int getZHeight() const;
        bool operator>(const IDrawable &other) const {
            return (getZHeight() > other.getZHeight());
        };
        bool operator<(const IDrawable &other) const {
            return (getZHeight() < other.getZHeight());
        };
        
        void removeFromStack();
        void setZHeight(int newZHeight);
        void setInStack(DrawStack* newStack);
        bool getInStack();
        bool isThisStack(DrawStack* compStack);

};



#endif //INTERFACE_DRAWABLE_H
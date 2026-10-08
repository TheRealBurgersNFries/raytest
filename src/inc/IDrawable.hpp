#ifndef INTERFACE_DRAWABLE_H
#define INTERFACE_DRAWABLE_H

#include "raylib.h"
#include <vector>


class DrawStack;
class IDrawable;

class DrawStack {
    private:
        std::vector<IDrawable*> drawList;
        std::vector<IDrawable*> addList;
    public:
        void Draw();

        void addToStack(IDrawable *drawable);
        void removeFromStack(IDrawable *drawable);
        
        DrawStack();
};

class IDrawable {
    private:
        int heightZ;
        DrawStack stack;
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
        void setInStack(DrawStack newStack);

};



#endif //INTERFACE_DRAWABLE_H
#include "inc/IDrawable.hpp"
#include "inc/helper.hpp"
#include <algorithm>
DrawStack::DrawStack() {
}
void DrawStack::Draw() {
    for (std::vector<IDrawable*>::iterator drawable = addList.begin(); drawable != //
        addList.end(); drawable++) {
            drawList.push_back(*drawable);
        }
    addList.clear();
    std::stable_sort(drawList.begin(), drawList.end(), lesserDepthComparer{});

    BeginDrawing();
    for (std::vector<IDrawable*>::iterator drawable = drawList.begin(); drawable !=  //
            drawList.end(); drawable++) {
        (*drawable)->Draw();
    }
    EndDrawing();
}

void DrawStack::addToStack(IDrawable *drawable) {
    drawList.insert(drawable);
    drawable->setInStack(*this);
}

void DrawStack::removeFromStack(IDrawable *drawable) {
    drawList.erase(drawable);
}

int IDrawable::getZHeight() const{
    return heightZ;
}

void IDrawable::removeFromStack() {
    if (inStack){
        stack.removeFromStack(this);
        inStack = false;
    }   

}

void IDrawable::setZHeight(int newZHeight) {
    heightZ = newZHeight;
}

void IDrawable::setInStack(DrawStack newStack) {
    stack = newStack;
    inStack = true;
}
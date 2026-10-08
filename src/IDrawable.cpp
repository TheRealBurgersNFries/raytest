#include "inc/IDrawable.hpp"
#include "inc/helper.hpp"
#include <algorithm>
#include <iterator>

DrawStack::DrawStack() {
    
}

void DrawStack::Draw() {
    std::stable_sort(subList.begin(), subList.end(), lesserDepthComparer{});
    auto ib = std::begin(drawList);
    auto iter = std::remove_if (
        std::begin(subList), std::end(subList),
        [&ib, this](IDrawable* x) -> bool {
            while (ib != std::end(drawList) && *ib != x) ++ib;
            return (ib != std::end(drawList) && *ib == x );
        });
    

    for (std::vector<IDrawable*>::iterator drawable = addList.begin(); drawable != //
        addList.end(); drawable++) {
            drawList.push_back(*drawable);
            (*drawable)->setInStack(this);
        }
    addList.clear();

    std::stable_sort(drawList.begin(), drawList.end(), lesserDepthComparer{});

    BeginDrawing();
    for (std::vector<IDrawable*>::iterator drawable = drawList.begin(); drawable !=  //
            drawList.end(); drawable++) {
        (*drawable)->Draw();
    }
    EndDrawing();
    for (int pressed = 1; pressed != 0; pressed = GetKeyPressed())
    {
        inputs.at(pressed) = true;
    }

}


void DrawStack::addToStack(IDrawable *drawable) {
    addList.push_back(drawable);
}

void DrawStack::removeFromStack(IDrawable *drawable) {
    if (drawable->isThisStack(this))
    {
        if (drawable->getInStack())
            subList.push_back(drawable);
        //else
            //handle premature removal;
            
    }
    //do something with bad state
}

void DrawStack::getInputs( std::array<bool,338> *array) {
    std::copy(std::begin(inputs), std::end(inputs), std::begin(*array));
    inputs.fill(false);
}

int IDrawable::getZHeight() const{
    return heightZ;
}

void IDrawable::removeFromStack() {
    if (inStack){
        stack->removeFromStack(this);
        inStack = false;
    }   
}

void IDrawable::setZHeight(int newZHeight) {
    heightZ = newZHeight;
}

void IDrawable::setInStack(DrawStack* newStack) {
    stack = newStack;
    inStack = true;
}

bool IDrawable::getInStack() {
    return inStack;
}

bool IDrawable::isThisStack(DrawStack* compStack) {
    return compStack == stack;
}

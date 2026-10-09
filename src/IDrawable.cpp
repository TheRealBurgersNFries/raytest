#include "inc/IDrawable.hpp"
#include "inc/helper.hpp"
#include <algorithm>
#include <iterator>

DrawStack::DrawStack() {
    
}

void DrawStack::Draw() {
    std::stable_sort(_subList.begin(), _subList.end(), lesserDepthComparer{});
    auto ib = std::begin(_drawList);
    auto iter = std::remove_if (
        std::begin(_subList), std::end(_subList),
        [&ib, this](IDrawable* x) -> bool {
            while (ib != std::end(_drawList) && *ib != x) ++ib;
            return (ib != std::end(_drawList) && *ib == x );
        });
    

    for (std::vector<IDrawable*>::iterator drawable = _addList.begin(); drawable != //
        _addList.end(); drawable++) {
            _drawList.push_back(*drawable);
            (*drawable)->setInStack(this);
        }
    _addList.clear();

    std::stable_sort(_drawList.begin(), _drawList.end(), lesserDepthComparer{});

    BeginDrawing();
    for (std::vector<IDrawable*>::iterator drawable = _drawList.begin(); drawable !=  //
            _drawList.end(); drawable++) {
        (*drawable)->Draw();
    }
    EndDrawing();
    
    _inputs.at(KEY_UP) = IsKeyDown(KEY_UP);
    _inputs.at(KEY_DOWN) = IsKeyDown(KEY_DOWN);
    _inputs.at(KEY_LEFT) = IsKeyDown(KEY_LEFT);
    _inputs.at(KEY_RIGHT) = IsKeyDown(KEY_RIGHT);
   

}


void DrawStack::addToStack(IDrawable *drawable) {
    _addList.push_back(drawable);
}

void DrawStack::removeFromStack(IDrawable *drawable) {
    if (drawable->isThisStack(this))
    {
        if (drawable->getInStack())
            _subList.push_back(drawable);
        //else
            //handle premature removal;
            
    }
    //do something with bad state
}

void DrawStack::getInputs( std::array<bool,338> *array) {
    std::copy(std::begin(_inputs), std::end(_inputs), std::begin(*array));
    _inputs.fill(false);
}

int IDrawable::getZHeight() const{
    return _heightZ;
}

void IDrawable::removeFromStack() {
    if (_inStack){
        _stack->removeFromStack(this);
        _inStack = false;
    }   
}

void IDrawable::setZHeight(int newZHeight) {
    _heightZ = newZHeight;
}

void IDrawable::setInStack(DrawStack* newStack) {
    _stack = newStack;
    _inStack = true;
}

bool IDrawable::getInStack() {
    return _inStack;
}

bool IDrawable::isThisStack(DrawStack* compStack) {
    return compStack == _stack;
}

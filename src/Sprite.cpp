#include "inc/Sprite.hpp"

Sprite::Sprite(Color color) {
    Type = SPRITE_SHAPE;
    spriteColor = color;
    position = {0, 0};
}

Sprite::Sprite(Image *image) {
    Type = SPRITE_IMAGE;
    spriteImage = image;
    position = {0, 0};
}

Sprite::Sprite(Image *image, bool texture) {
    Type = SPRITE_TEXTURE;
    spriteImage = image;
    position = {0, 0};
}

void Sprite::setPosition(Vector2 newPosition) {
    position = newPosition;
}

Vector2 const Sprite::getPosition () {
    return position;
}

void Sprite::Draw() const {
    switch(Type) {
        case SPRITE_SHAPE:
            DrawRectangle(position.x, position.y, 10, 10, spriteColor);
            //Handle other shapes. implement shape interface?
            break;
        case SPRITE_IMAGE:
            ImageDrawRectangle(spriteImage, position.x, position.y,  //
                spriteImage->width, spriteImage->width, BLANK);
            break;
        case SPRITE_TEXTURE:
            //TODO
            break;
        default:
            //UNREACHABLE
            break;
    }
}



#include "inc/Background.hpp"

Background::Background(Color backgroundColor) {
    Type = BACKGROUND_SOLID;
    solidColor = backgroundColor;
}

Background::Background(Image *backgroundImage) {
    Type = BACKGROUND_IMAGE;
    image = backgroundImage;
    solidColor = (Color){0, 0, 0, 255};
}

void Background::Draw() const {
    switch(Type) {
        case BACKGROUND_SOLID:
            ClearBackground(solidColor);
            break;
        case BACKGROUND_IMAGE:
            ImageClearBackground(image, solidColor);
            break;
        default:
            //Inaccessible
            break;
    }
}
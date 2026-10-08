#ifndef SPRITE_DRAWABLE_H
#define SPRITE_DRAWABLE_H

#include "IDrawable.hpp"

enum SpriteType {
    SPRITE_SHAPE,
    SPRITE_IMAGE,
    SPRITE_TEXTURE
};

class Sprite : public IDrawable {
    private:
        Color spriteColor;
        Image *spriteImage;
        Vector2 position;
        SpriteType Type;
        
    public:
        Sprite(Color color);
        Sprite(Image *image);
        Sprite(Image *image, bool texture);
        void setPosition(Vector2 newPosition);
        Vector2 const getPosition();

        void Draw() const override;

        //void setType(SpriteType newType);
        //void setColor(Color newColor);
        //void setImage(Image *newImage);

        

};


#endif //SPRITE_DRAWABLE_H
#ifndef BACKGROUND_DRAWABLE_H
#define BACKGROUND_DRAWABLE_H

#include "raylib.h"
#include "inc/IDrawable.hpp"


enum BackgroundType {
    BACKGROUND_SOLID,
    BACKGROUND_IMAGE

};

class Background : public IDrawable {
    private:
        Color solidColor;
        Image *image;
        BackgroundType Type = BACKGROUND_SOLID;
        Background();    
    public:
        void Draw() const override;

        void setType(BackgroundType newType);
        void setColor(Color newColor);
        void setImage(Image *newImage);
        
        Background(Color backgroundColor);
        Background(Image *backgroundImage);       
};



#endif //BACKGROUND_DRAWABLE_H
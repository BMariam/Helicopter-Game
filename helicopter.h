#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <SFML/Graphics.hpp>

class Helicopter {
public:
    sf :: Sprite* helicopterSprite;
    Helicopter();
    void handleEvent(sf :: Event&);
    void moveDown();
    void show();
    void resetHelicopter();
private:
    int posX = 30;
    int posY = 150;
    int dy = 10;
    sf :: Texture helicopterTexture;               
};

#endif 

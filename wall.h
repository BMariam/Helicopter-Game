#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall {
public:
    sf :: Sprite* wallSprite;
    Wall(int posX);
    void move();
    void show();
    void resetWall(int positionX);
private:
    int posX;
    int posY;
    int dx = 5;
    sf :: Texture wallTexture;  
    void setRandomYPosition();              
};

#endif 

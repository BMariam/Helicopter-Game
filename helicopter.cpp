#include "gameInit.h"
#include "helicopter.h"

Helicopter :: Helicopter() {
    helicopterTexture.loadFromFile("images/helicopter.png");
    helicopterSprite = new sf :: Sprite(helicopterTexture);
    show();
}

void Helicopter :: handleEvent(sf :: Event& e) {
    bool upKey = false;
    bool downKey = false;
    if (e.type == sf :: Event :: KeyPressed) {
        switch (e.key.code) {
            case sf :: Keyboard :: Up: {
                upKey = true;
                break;
            }
            case sf :: Keyboard :: Down: {
                downKey = true;
                break;
            }
        }
    }
    if (e.type == sf :: Event :: KeyReleased) {
        switch (e.key.code) {
            case sf :: Keyboard :: Up: {
                upKey = false;
                break;
            }
            case sf :: Keyboard :: Down: {
                downKey = false;
                break;
            }
        }
    }
    if (upKey && posY > 0) {
        posY -= dy;
    }
    if (downKey && posY < Init :: height - helicopterTexture.getSize().y) {
        posY += dy;
    }
    show();    
}

void Helicopter :: moveDown() {
    posY += Init :: level;
    show();
}

void Helicopter :: show() {
    helicopterSprite -> setPosition(posX, posY);
}

void Helicopter :: resetHelicopter() {
    posY = 150;
    show();
}

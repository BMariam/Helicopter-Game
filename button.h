#ifndef BUTTON_H
#define BUTTON_H

#include "rectShape.h"
#include <SFML/Graphics.hpp>

class Button : public RectShape {
public:
    Button(std :: string, int, sf :: Color, sf :: Vector2f, sf :: Color);
    bool isMouseClicked(sf :: RenderWindow& window);          
};

#endif 

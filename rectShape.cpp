#include "gameInit.h"
#include "rectShape.h"
#include <iostream>

RectShape :: RectShape(std :: string text, int charSize, sf :: Color textColor, 
        sf :: Vector2f rectSize, sf :: Color rectColor) {
    this -> text.setString(text);
    this -> text.setCharacterSize(charSize);
    this -> text.setFillColor(textColor);

    this -> rect.setSize(rectSize);
    this -> rect.setFillColor(rectColor);  
}

void RectShape :: setPosition() {
    sf :: FloatRect textRect = text.getLocalBounds();
    // Center text on the screen 
    text.setPosition(Init :: width / 2.0f - textRect.width / 2.0f, 
        Init :: height / 2.0f - textRect.height / 2.0f);

    // Center rect on the screen 
    sf :: FloatRect shapeRect = rect.getLocalBounds(); 
    rect.setPosition(Init :: width / 2.0f - shapeRect.width / 2.0f,
        Init :: height / 2.0f - shapeRect.height / 2.0f); 
}

void RectShape :: draw(sf :: RenderWindow& window) {
    window.draw(rect);
    window.draw(text);
}

void RectShape :: setFont(sf :: Font& font) {
    text.setFont(font);
}

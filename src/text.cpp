// File: text.cpp
// Folder: src

#include "text.h"

Text :: Text(std :: string string, int characterSize,
		sf :: Color fillColor, int positionX, int positionY) {
	text.setString(string);
	text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
    text.setPosition(positionX, positionY);	
}

void Text :: setString(const std :: string& string) {
	text.setString(string);
}

void Text :: setFont(const sf :: Font& font) {
	text.setFont(font);
}

void Text :: draw(sf :: RenderWindow& window) {
	window.draw(text);
}

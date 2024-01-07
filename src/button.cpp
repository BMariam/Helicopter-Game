// File: button.cpp
// Folder: src

#include "button.h"

Button :: Button(std :: string text, int charSize, sf :: Color textColor, 
		sf :: Vector2f rectSize, 
		sf :: Color rectColor) 
	: RectShape(text, charSize, textColor, rectSize, rectColor) {}

	bool Button :: isMouseClicked(sf :: RenderWindow& window) {
		float mouseX = sf :: Mouse :: getPosition(window).x;
		float mouseY = sf :: Mouse :: getPosition(window).y;

		float buttonPosX = rect.getPosition().x;
		float buttonPosY = rect.getPosition().y;

		float buttonXPosWidth = buttonPosX + rect.getLocalBounds().width; 
		float buttonYPosHeight = buttonPosY + rect.getLocalBounds().height;

		if (mouseX < buttonXPosWidth && mouseX > buttonPosX 
				&& mouseY < buttonYPosHeight && mouseY > buttonPosY) {
			return true;
		}
		return false; 
	}

// File: rectShape.h
// Folder: inc

#ifndef RECT_SHAPE_H
#define RECT_SHAPE_H

#include <SFML/Graphics.hpp>

class RectShape {
	public:
		RectShape(std :: string, int, sf :: Color, sf :: Vector2f, sf :: Color);
		void setPosition();
		void draw(sf :: RenderWindow& window);
		void setFont(sf :: Font& font);
	protected:
		sf :: Text text;    
		sf :: RectangleShape rect;           
};

#endif 

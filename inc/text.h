// File: text.h
// Folder: inc

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp> 

class Text {
	public:
		Text(std :: string, int, sf :: Color, int, int);
		void setString(const std :: string&);
		void setFont(const sf :: Font&);
		void draw(sf :: RenderWindow&);
		~Text() = default;
	private:
		sf :: Text text;
};

#endif 

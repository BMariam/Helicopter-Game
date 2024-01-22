// File: collision.h
// Folder: inc

#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace Collision {
	bool checkCollision(sf :: Sprite& sprite1, sf :: Sprite& sprite2) {
		sf :: FloatRect shape1 = sprite1.getGlobalBounds();
		sf :: FloatRect shape2 = sprite2.getGlobalBounds();
		if (sprite1.getPosition().x < sprite2.getPosition().x + shape2.width 
				&& sprite1.getPosition().x + shape1.width > sprite2.getPosition().x 
				&& sprite1.getPosition().y < sprite2.getPosition().y + shape2.height 
				&& shape1.height + sprite1.getPosition().y > sprite2.getPosition().y
				|| sprite1.getPosition().y + shape1.height >= Init :: height) {
			return true;
		}
		return false;
	}
}

#endif

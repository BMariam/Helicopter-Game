// File: main.cpp
// Folder: src

#include "gameInit.h"
#include "text.h"
#include "helicopter.h"
#include "wall.h"
#include "button.h"
#include "collision.h"
#include <iostream>
#include <vector>

int main() {
	sf :: RenderWindow window(sf :: VideoMode(Init :: width, Init :: height), 
			"Helicopter Game", sf :: Style :: Titlebar | sf :: Style :: Close);

	sf :: Font font;   
	if (!font.loadFromFile("res/arial.ttf")) {
		std :: cout << "Can't load font" << std :: endl;
	}

	Text levelText("Level: " + std :: to_string(Init :: level),
			20, sf :: Color :: Black, 10, 0);
	levelText.setFont(font);

	Text scoreText("Score: " + std :: to_string(static_cast<int>(Init :: score)),
			20, sf :: Color :: Black, Init :: width / 4, 0);
	scoreText.setFont(font);

	Text highestScoreText("Highest score: " + std :: to_string(static_cast<int>(Init :: highScore)),
			 20, sf :: Color :: Black, Init :: width / 2, 0);
	highestScoreText.setFont(font);

	sf :: Texture backgroundTexture;
	sf :: Texture skyTexture;

	backgroundTexture.loadFromFile("res/images/background.png");
	skyTexture.loadFromFile("res/images/sky.jpg");

	sf :: Sprite background(backgroundTexture);
	background.setPosition(0, 
			Init :: height - backgroundTexture.getSize().y);

	sf :: Sprite sky(skyTexture);
	sky.setPosition(0, 0);

	Helicopter helicopter;
	int wallCount = 4;
	std::vector<Wall*> walls;
	std :: srand(std :: time(0));
	for (int i = 0; i < wallCount; ++i) {
		walls.push_back(new Wall(i * (Init :: width / wallCount)));
	}

	Button playButton("Play", 30, sf :: Color(241, 170, 32), 
			sf :: Vector2f(200, 50), sf :: Color(191, 4, 4));
	playButton.setFont(font);
	playButton.setPosition();

	while(window.isOpen()) {
		sf :: Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf :: Event :: Closed) {
				window.close();
			}
			if ((event.type == sf :: Event :: KeyPressed
						|| event.type == sf :: Event :: KeyReleased)
					&& (event.key.code == sf :: Keyboard :: Up
						|| event.key.code == sf :: Keyboard :: Down)) {
				if (Init :: isGameActive) {
					helicopter.handleEvent(event);
				}
			}
			if (event.type == sf :: Event :: MouseButtonPressed) {
				if (event.mouseButton.button == sf :: Mouse :: Left) {
					if (playButton.isMouseClicked(window)) {
						Init :: isGameActive = true;
					}
				}
			}            
		} 
		window.clear(sf :: Color(135, 206, 235));
		window.draw(background);
		window.draw(sky);  
		levelText.draw(window);
		scoreText.draw(window);
		highestScoreText.draw(window);
		for (int i = 0; i < wallCount; ++i) {
			window.draw(*(walls[i] -> wallSprite));
		}
		window.draw(*(helicopter.helicopterSprite));
		sf :: sleep(sf :: milliseconds(100)); 
		if (Init :: isGameActive) {        
			for (int i = 0; i < wallCount; ++i) { 
				walls[i] -> move();
			} 
			helicopter.moveDown();
			Init :: score += 0.5;
			if (0 == ((int)(10 * Init :: score) % 10)) {
					scoreText.setString("Score: " + std :: to_string((int)Init :: score));
					Init :: highScore = Init :: score <= Init :: highScore 
						? Init :: highScore : Init :: score;
					highestScoreText.setString("Highest score: " 
							+ std :: to_string((int)Init :: highScore));
				}
			if (Init :: score / Init :: level >= 200) {
				++Init :: level;
				levelText.setString("Level: " + std :: to_string(Init :: level));
			}
			for (int i = 0; i < wallCount; ++i) { 
				if (Collision :: checkCollision(*(helicopter.helicopterSprite), 
							*(walls[i] -> wallSprite))) {
					Init :: isGameActive = false;
					std :: string gameOverText = "Game Over\nScore: " 
						+ std :: to_string((int)Init :: score) 
						+ "\nHighest Score: " 
						+ std :: to_string((int)Init :: highScore);
					RectShape gameOver(gameOverText, 25, sf :: Color :: Red,
							sf :: Vector2f(Init :: width / 4.0f, Init :: height / 4.0f),
							sf :: Color :: Black);
					gameOver.setFont(font);
					gameOver.setPosition(); 
					gameOver.draw(window);
					window.display();
					sf :: sleep(sf :: seconds(3)); 
					helicopter.resetHelicopter(); 
					for (int i = 0; i < wallCount; ++i) {
						walls[i] -> resetWall(i * (Init :: width / wallCount));
					}                                                          
				}
			}           
		} else {
			Init :: score = 0;
			Init :: level = 1;

			playButton.draw(window);

			levelText.setString("Level: " + std :: to_string(Init :: level));
			scoreText.setString("Score: " + std :: to_string((int)Init :: score));
		}
		window.display();               
	}
	for (int i = 0; i < wallCount; ++i) {
		delete walls[i];
	}

	return 0;
}

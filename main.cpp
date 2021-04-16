#include "gameInit.h"
#include "helicopter.h"
#include "wall.h"
#include "button.h"
#include <iostream>

bool collision(sf :: Sprite& sprite1, sf :: Sprite& sprite2) {
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

int main() {
    sf :: RenderWindow window(sf :: VideoMode(Init :: width, Init :: height), 
        "Helicopter Game", sf :: Style :: Titlebar | sf :: Style :: Close);

    
    sf :: Font font;   
    if (!font.loadFromFile("arial.ttf")) {
        std :: cout << "Can't load font" << std :: endl;
    }

    sf :: Text levelText;
    levelText.setFont(font);
    levelText.setString("Level: " + std :: to_string(Init :: level));
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf :: Color :: Black);
    levelText.setPosition(10, 0);

    sf :: Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std :: to_string((int)Init :: score));
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf :: Color :: Black);
    scoreText.setPosition(Init :: width / 4, 0);

    sf :: Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setString("High score: " 
        + std :: to_string((int)Init :: highScore));
    highScoreText.setCharacterSize(20);
    highScoreText.setFillColor(sf :: Color :: Black);
    highScoreText.setPosition(Init :: width / 2, 0);

    sf :: Texture backgroundTexture_1;
    sf :: Texture backgroundTexture_2;
    sf :: Texture skyTexture;
    
    backgroundTexture_1.loadFromFile("images/background_1.png");
    backgroundTexture_2.loadFromFile("images/background_2.png");
    skyTexture.loadFromFile("images/sky.jpg");

    sf :: Sprite background_1(backgroundTexture_1);
    background_1.setPosition(0, 
        Init :: height - backgroundTexture_1.getSize().y);

    sf :: Sprite background_2(backgroundTexture_2);
    background_2.setPosition(Init :: width / 2, 
        Init :: height - backgroundTexture_1.getSize().y);

    sf :: Sprite sky(skyTexture);
    sky.setPosition(0, 0);
  
    Helicopter helicopter;
    int wallCount = 4;
    Wall* walls[wallCount];
    for (int i = 0; i < wallCount; ++i) {
        walls[i] = new Wall(i * (Init :: width / wallCount));
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
                    || event.key.code == sf :: Keyboard :: Down)) 
                /* If Up or Down key is pressed or released */ {
                helicopter.handleEvent(event);
            }
            if (event.type == sf :: Event :: MouseButtonPressed) {
                if (event.mouseButton.button == sf :: Mouse :: Left) {
                    if (playButton.isMouseClicked(window)) 
                    /* If left mouse button is pressed on the playButton */ {
                        Init :: isGameActive = true;
                    }
                }
            }            
        } 
        window.clear(sf :: Color(135, 206, 235));
        window.draw(background_1);
        window.draw(background_2);
        window.draw(sky);  
        window.draw(levelText);   
        window.draw(scoreText);  
        window.draw(highScoreText);
        for (int i = 0; i < wallCount; ++i) { 
            window.draw(*(walls[i] -> wallSprite));
        }         
        window.draw(*(helicopter.helicopterSprite));
        sf :: sleep(sf :: milliseconds(100)); 
        if (Init :: isGameActive) {        
            for (int i = 0; i < wallCount; ++i) { 
                walls[i] -> move(); // Move walls to the left 
            } 
            helicopter.moveDown(); // Move helicopter to the down
            Init :: score += 0.5;
            if (0 == ((int)(10 * Init :: score) % 10)) 
                /* If score is a whole number */ {
                scoreText.setString("Score: " + std :: to_string((int)Init :: score));
                Init :: highScore = Init :: score <= Init :: highScore 
                        ? Init :: highScore : Init :: score;
                highScoreText.setString("High score: " 
                    + std :: to_string((int)Init :: highScore));
            }
            if (Init :: score / Init :: level >= 200) {
                ++Init :: level;
                levelText.setString("Level: " + std :: to_string(Init :: level));
            }
            for (int i = 0; i < wallCount; ++i) { 
                if (collision(*(helicopter.helicopterSprite), 
                        *(walls[i] -> wallSprite))) 
                    /* Collision of helicopter and wall or helicopter and ground */ {
                    Init :: isGameActive = false;
                    std :: string gameOverText = "Game Over\nScore: " 
                       + std :: to_string((int)Init :: score) 
                       + "\nHigh Score: " 
                       + std :: to_string((int)Init :: highScore);
                    RectShape gameOver(gameOverText, 25, sf :: Color :: Red,
                        sf :: Vector2f(Init :: width / 4.0f, Init :: height / 4.0f),
                        sf :: Color :: Black);
                    gameOver.setFont(font);
                    gameOver.setPosition(); 
                    gameOver.draw(window);
                    window.display();
                    sf :: sleep(sf :: seconds(3)); 
                    helicopter.resetHelicopter(); // Reset helicopter y position
                    for (int i = 0; i < wallCount; ++i) {
                        // Reset each wall x and y positions
                        walls[i] -> resetWall(i * (Init :: width / wallCount));
                    }                                                          
                }
            }           
        } else {
            // Reset score and level
            Init :: score = 0;
            Init :: level = 1;

            playButton.draw(window);
           
            // Update levelText and scoreText
            levelText.setString("Level: " + std :: to_string(Init :: level));
            scoreText.setString("Score: " + std :: to_string((int)Init :: score));
        }
        window.display();               
    }

    for (int i = 0; i < wallCount; ++i) {
        delete walls[i];
        walls[i] = nullptr;
    }

    return 0;
}

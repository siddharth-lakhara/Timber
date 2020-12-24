//
//  main.cpp
//  Timber
//
//  Created by slakhara on 23/12/20.
//

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const string baseFolder = "/Users/slakhara/personal/game-dev/Timber/Timber/";

int main() {
    VideoMode vm(1680, 1048);
    RenderWindow window(vm, "Timber", Style::Default);

    Texture textureBg;
    textureBg.loadFromFile(baseFolder + "graphics/background.png");
    Sprite spriteBg;
    spriteBg.setTexture(textureBg);
    spriteBg.setPosition(0,0);
    
    Texture textureTree;
    textureTree.loadFromFile(baseFolder + "graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(700, 0);
    
    Texture textureBee;
    textureBee.loadFromFile(baseFolder + "graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 700);
    bool isBeeActive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud;
    textureCloud.loadFromFile(baseFolder + "graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 150);
    spriteCloud3.setPosition(0, 300);
    bool isCloud1Active = false;
    bool isCloud2Active = false;
    bool isCloud3Active = false;
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
    
    Clock clock;
    
    bool isGamePaused = true;
    
    int score = 0;
    Text msgText;
    Text scoreText;
    
    Font font;
    font.loadFromFile(baseFolder + "fonts/KOMIKAP_.ttf");
    
    msgText.setFont(font);
    msgText.setString("Press Enter to start!");
    msgText.setCharacterSize(75);
    msgText.setFillColor(Color::White);
    
    FloatRect textRect = msgText.getLocalBounds();
    msgText.setOrigin(
          textRect.left + textRect.width/2.0f,
          textRect.top + textRect.height/2.0f
      );
    msgText.setPosition(1680/2.0f, 1048/2.0f);
    
    scoreText.setFont(font);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);
    
    while (window.isOpen()) {
        Event evt;

        while (window.pollEvent(evt)) {
            switch (evt.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if (evt.key.code == Keyboard::Escape) {
                        window.close();
                    } else if (evt.key.code == Keyboard::Return) {
                        isGamePaused = !isGamePaused;
                    }
                    cout << "Key press detected: ";
                    cout << evt.key.code << endl;
                    break;
                default:
                    break;
            }
        }
        
        Time dt = clock.restart();
        if (!isGamePaused) {
            if (!isBeeActive) {
    //            Initialise Bee variables
    //            Bee speed
                srand( (int)time(0) );
                beeSpeed = (rand() % 200) + 200;
                
    //            Bee height
                srand( (int)time(0)*10 );
                float beeHeight = (rand() % 500) + 500;
                spriteBee.setPosition(2000, beeHeight);
                isBeeActive = true;
            } else {
    //            Move Bee
                spriteBee.setPosition(
                          spriteBee.getPosition().x - beeSpeed*dt.asSeconds(),
                          spriteBee.getPosition().y
                );
                
                if (spriteBee.getPosition().x < -100) {
                    isBeeActive = false;
                }
            }
            
            if (!isCloud1Active) {
    //            Initialise Cloud1 variables
    //            Cloud speed
                srand( (int)time(0)*10 );
                cloud1Speed = (rand() % 200);
                
    //            Cloud height
                srand( (int)time(0)*10 );
                float cloud1Height = (rand() % 150);
                spriteCloud1.setPosition(-200, cloud1Height);
                isCloud1Active = true;
            } else {
    //            Move Cloud
                spriteCloud1.setPosition(
                             spriteCloud1.getPosition().x + cloud1Speed*dt.asSeconds(),
                             spriteCloud1.getPosition().y
                );
                
                if (spriteCloud1.getPosition().x > 1680) {
                    isCloud1Active = false;
                }
            }
            
            if (!isCloud2Active) {
    //            Initialise Cloud2 variables
    //            Cloud speed
                srand( (int)time(0)*20 );
                cloud2Speed = (rand() % 200);

    //            Cloud height
                srand( (int)time(0)*20 );
                float cloud2Height = (rand() % 200) - 50;
                spriteCloud2.setPosition(-200, cloud2Height);
                isCloud2Active = true;
            } else {
    //            Move Cloud
                spriteCloud2.setPosition(
                             spriteCloud2.getPosition().x + cloud2Speed*dt.asSeconds(),
                             spriteCloud2.getPosition().y
                );

                if (spriteCloud2.getPosition().x > 1680) {
                    isCloud2Active = false;
                }
            }

            if (!isCloud3Active) {
    //            Initialise Cloud3 variables
    //            Cloud speed
                srand( (int)time(0)*30 );
                cloud3Speed = (rand() % 200);

    //            Cloud height
                srand( (int)time(0)*30 );
                float cloud3Height = (rand() % 250) - 50;
                spriteCloud3.setPosition(-200, cloud3Height);
                isCloud3Active = true;
            } else {
    //            Move Cloud
                spriteCloud3.setPosition(
                             spriteCloud3.getPosition().x + cloud3Speed*dt.asSeconds(),
                             spriteCloud3.getPosition().y
                );

                if (spriteCloud3.getPosition().x > 1680) {
                    isCloud3Active = false;
                }
            }
            
            stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }
        
        

        window.clear();
        window.draw(spriteBg);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(scoreText);
        if (isGamePaused) {
            window.draw(msgText);
        }
        window.display();
    }
    return 0;
}

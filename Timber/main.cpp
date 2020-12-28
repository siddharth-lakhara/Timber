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

void updateBranch(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];

int main() {
    const int screenWidth = 1680;
    const int screenHeight = 1048;
    VideoMode vm(screenWidth, screenHeight);
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
    msgText.setPosition(screenWidth/2.0f, screenHeight/2.0f);
    
    scoreText.setFont(font);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);
    
//    Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(screenWidth/2 - timeBarStartWidth/2, 980);
    
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth/timeRemaining;
    
    Texture textureBranch;
    textureBranch.loadFromFile(baseFolder + "graphics/branch.png");
    
    for (int i=0; i<NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
//        Set origin to center of sprite
        branches[i].setPosition(220, 40);
    }
    
    updateBranch(1);
    updateBranch(2);
    updateBranch(3);
    updateBranch(4);
    updateBranch(5);
    
    const float playerPositionLeft = 520;
    const float playerPositionRight = 1050;
    Texture texturePlayer;
    texturePlayer.loadFromFile(baseFolder + "graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(playerPositionLeft, 720);
    side playerSide = side::LEFT;
    
    Texture textureRIP;
    textureRIP.loadFromFile(baseFolder + "graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(520, 860);
    
    const float axePositionLeft = 630;
    const float axePositionRight = 925;
    Texture textureAxe;
    textureAxe.loadFromFile(baseFolder + "graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(axePositionLeft, 830);
    
    const float logPositionLeft = 700;
    const float logHeight = 780;
    Texture textureLog;
    textureLog.loadFromFile(baseFolder + "graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(logPositionLeft, logHeight);
    
    bool isLogActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    
    bool isAcceptingInput = true;
    bool isGameInitialised = false;
    
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
                        
                        if (timeRemaining <= 0.0f || !isGameInitialised) {
//                            Restart the game
                            score = 0;
                            msgText.setString("Press Enter to start!");
                            FloatRect textRect = msgText.getLocalBounds();
                            msgText.setOrigin(
                                  textRect.left + textRect.width/2.0f,
                                  textRect.top + textRect.height/2.0f
                              );
                            msgText.setPosition(screenWidth/2.0f, screenHeight/2.0f);
                            timeRemaining = 6.0f;
                            for (int i=1; i<NUM_BRANCHES; i++) {
                                branchPositions[i] = side::NONE;
                            }
                            
                            spriteRIP.setPosition(6756, 2000);
                            spritePlayer.setPosition(playerPositionLeft, 720);
                            spriteAxe.setPosition(axePositionLeft, 830);

                            isGameInitialised = true;
                        }
                    }
                    
                    if (isAcceptingInput) {
                        cout << "Accepting input" << endl;
                        if (evt.key.code == Keyboard::Right) {
                            playerSide = side::RIGHT;
                            score++;
                            
                            timeRemaining += (2/score) + 0.40;
                            
                            spriteAxe.setPosition(axePositionRight, spriteAxe.getPosition().y);
                            spritePlayer.setPosition(playerPositionRight, spritePlayer.getPosition().y);
                            
                            updateBranch(score);
                            spriteLog.setPosition(logPositionLeft, logHeight);
                            logSpeedX = -5000;
                            isLogActive = true;
                            isAcceptingInput = false;
                        }
                        
                        else if (evt.key.code == Keyboard::Left) {
                            playerSide = side::LEFT;
                            score++;
                            
                            timeRemaining += (2/score) + 0.40;
                            
                            spriteAxe.setPosition(axePositionLeft, spriteAxe.getPosition().y);
                            spritePlayer.setPosition(playerPositionLeft, spritePlayer.getPosition().y);
                            
                            updateBranch(score);
                            spriteLog.setPosition(logPositionLeft, logHeight);
                            logSpeedX = 5000;
                            isLogActive = true;
                            isAcceptingInput = false;
                        }
                    }
                    
                    cout << "Key press detected: ";
                    cout << evt.key.code << endl;
                    break;
                case (Event::KeyReleased):
                    if (!isGamePaused) {
                        isAcceptingInput = true;
                    }
                    break;
                default:
                    break;
            }
        }
        
        Time dt = clock.restart();
        if (!isGamePaused) {
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(
                     timeBarWidthPerSecond*timeRemaining, timeBarHeight
             ));
            
            if (timeRemaining <= 0.0f) {
                isGamePaused = true;
                msgText.setString("Out of time!");
                FloatRect textRect = msgText.getLocalBounds();
                msgText.setOrigin(
                      textRect.left+textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f
                );
                msgText.setPosition(screenWidth/2.0f, screenHeight/2.0f);
            }
            
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
                
                if (spriteCloud1.getPosition().x > screenWidth) {
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

                if (spriteCloud2.getPosition().x > screenWidth) {
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

                if (spriteCloud3.getPosition().x > screenWidth) {
                    isCloud3Active = false;
                }
            }
            
            if (isLogActive) {
                spriteLog.setPosition(
                      spriteLog.getPosition().x + (logSpeedX*dt.asSeconds()),
                      spriteLog.getPosition().y + (logSpeedY*dt.asSeconds())
                  );
                
//                Check if log has flown off screen
                if (spriteLog.getPosition().x < -100 ||
                    spriteLog.getPosition().x > 2000) {
                    isLogActive = false;
                    spriteLog.setPosition(logPositionLeft, logHeight);
                }
                
            }
            
            if (branchPositions[5] == playerSide) {
                isGamePaused = true;
                isAcceptingInput = false;
                isGameInitialised = false;
                spriteRIP.setPosition(520, 860);
                spritePlayer.setPosition(2000, 660);
                spriteAxe.setPosition(2000, 660);
                msgText.setString("Squished !!");
                FloatRect textRect = msgText.getLocalBounds();
                msgText.setOrigin(
                      textRect.left + textRect.width/2,
                      textRect.top + textRect.height/2
                  );
                msgText.setPosition(screenWidth/2.0f, screenHeight/2.0f);
            }
            
            stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
            
            for (int i=0; i<NUM_BRANCHES; i++) {
                float height = i*150;
                if (branchPositions[i] == side::LEFT) {
                    branches[i].setPosition(700, height);
                    branches[i].setRotation(180);
                } else if (branchPositions[i] == side::RIGHT) {
                    branches[i].setPosition(995, height);
                    branches[i].setRotation(0);
                } else {
                    branches[i].setPosition(3000, height);
                }
            }
        }

        window.clear();
        window.draw(spriteBg);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteBee);
        window.draw(spriteTree);
        window.draw(spriteLog);
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteRIP);
        if (isGamePaused) {
            window.draw(msgText);
        }
        window.draw(timeBar);
        for (int i=0; i<NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }
        window.draw(scoreText);
        window.display();
    }
    return 0;
}

void updateBranch(int seed) {
    for (int i = NUM_BRANCHES-1; i>0; i--) {
        branchPositions[i] = branchPositions[i-1];
    }
    
    srand((int)time(0) + seed);
    int r = rand()%5;
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}

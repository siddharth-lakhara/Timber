//
//  main.cpp
//  Timber
//
//  Created by slakhara on 23/12/20.
//

#include <iostream>
#include <string>
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
    
    while (window.isOpen()) {
        Event evt;

        while (window.pollEvent(evt)) {
            switch (evt.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:

                    cout << "Key press detected: ";
                    cout << evt.key.code << endl;
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.draw(spriteBg);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.display();
    }
    return 0;
}

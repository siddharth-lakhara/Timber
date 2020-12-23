//
//  main.cpp
//  Timber
//
//  Created by slakhara on 23/12/20.
//

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
    VideoMode vm(1024, 768, 32);
    RenderWindow window(vm, "Timber", Style::Default);
    
    Texture textureBg;
    textureBg.loadFromFile("/Users/slakhara/personal/game-dev/Timber/Timber/graphics/background.png");
    Sprite spriteBg;
    spriteBg.setTexture(textureBg);
    spriteBg.setPosition(0,0);
    
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
        window.display();
    }
    return 0;
}

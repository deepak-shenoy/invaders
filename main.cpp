#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "shields.h"

#include "settings.h"
#include "defender.h"
#include "aliens.h"

/*
 * ===============================================================================================================
 * Main code/logic
 * ===============================================================================================================
 */
int main() {
    //tt.display();
    sf::RenderWindow window(sf::VideoMode(MAX_SCREEN_X_DISTANCE,MAX_SCREEN_Y_DISTANCE), "Alien Invaders");
    window.setKeyRepeatEnabled(true);
    AlienFleet fleet = AlienFleet(3);
    Shields shields = Shields();
    Defender defender = Defender();
    window.setFramerateLimit(60);
    window.display();
    sf::Event::EventType previousState = sf::Event::MouseEntered;
    sf::Keyboard::Key previousKey = sf::Keyboard::Unknown;
    sf::Keyboard::Key pressedButton;
    while(window.isOpen()) {
        // Clear window
        window.clear();
        shields.drawShields(window);
        fleet.march();
        fleet.drawFleet(window);
        fleet.manageAlienBullets(window, shields);
        defender.draw(window);
        if(defender.firedShot()) {
            defender.moveBullet(window, fleet, shields);
        }
        sf::Event event;
        while(window.pollEvent(event)){
            // Terminate application
            if(event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Handle event closed" << std::endl;
                exit(EXIT_SUCCESS);
            }
            if(event.type == sf::Event::KeyPressed) {
                pressedButton = event.key.code;
                if(pressedButton == sf::Keyboard::Right) {
                    defender.moveRight(previousState == event.type && previousKey == sf::Keyboard::Right);
                    defender.draw(window);
                }
                if(pressedButton == sf::Keyboard::Left) {
                    defender.moveLeft(previousState == event.type && previousKey == sf::Keyboard::Left);
                    defender.draw(window);
                }
                if(pressedButton == sf::Keyboard::Space) {
                    defender.fireShot();
                }
            }
            previousState = event.type;
            previousKey = pressedButton;
          }
        window.display();
    }
    return 0;
}

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "shields.h"

#include "settings.h"
#include "shields.h"
#include "defender.h"
#include "aliens.h"

/*
 * ===============================================================================================================
 * Defender (user/player)
 * ===============================================================================================================
 */
class Defender {
public:
    Defender() {
        // Constructor
    }
    ~Defender() {
        //Destroyer
    }
    void draw(sf::RenderWindow& renderWindowsReference) {
        if(shotFired) defender_m_texture.loadFromFile(defenderImage + "defender-01.png");
        else defender_m_texture.loadFromFile(defenderImage + "defender-00.png");
        defender_m_sprite.setTexture(defender_m_texture);
        defender_m_sprite.setPosition(XPos, DEFENDER__Y_POSITION);
        renderWindowsReference.draw(defender_m_sprite);
    }
    void moveLeft(bool moveFast) {
        if(XPos - DEFENDER_MOVE___DIST > DEFENDER___FROM_WALL) {
            XPos -= moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST;
        }
    }
    void moveRight(bool moveFast) {
        if(XPos < DEFENDER_RIGHT_BORDR  ) {
            std::cout << (moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST);
            std::cout << "\n";
            XPos += moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST;
        }
    }
    void fireShot() {
        if(!shotFired) {
            shotFired = true;
            bulletXPos=XPos + DEFENDER_______WIDTH / 2 - 2;
            bulletYPos=DEFENDER__Y_POSITION - DEFENDER_BULLET_HGHT;
        }
    }
    void moveBullet(sf::RenderWindow& renderWindowsReference, AlienFleet& alienFleet, Shields& shields) {
        if(shotFired) {
            bullet_m_texture.loadFromFile(bulletImage + "bullet-00.png");
            bullet_m_sprite.setTexture(bullet_m_texture);
            bullet_m_sprite.setPosition(bulletXPos, bulletYPos);
            if((bulletYPos - DEFENDER_BULLET_SPED) > BULLET__TOP___BORDER) {
                bulletYPos -= DEFENDER_BULLET_SPED;
            } else {
                shotFired = false;
            }
            renderWindowsReference.draw(bullet_m_sprite);
            if(alienFleet.alienAreaImpacted(bulletXPos, bulletYPos)) shotFired = false;
            if(shields.shieldAreaImpacted(bulletXPos, bulletYPos, defenderBullet)) shotFired = false;
        }
    }
    bool firedShot() {
        return shotFired;
    }
private:
    std::string defenderImage{DEFENDER__PATH};
    bool shotFired{false};
    sf::Texture defender_m_texture;
    sf::Sprite defender_m_sprite;
    float XPos{MAX_SCREEN_X_DISTANCE/2};
    float bulletXPos{0};
    float bulletYPos{0};
    std::string bulletImage{DEFENDER__PATH};
    sf::Texture bullet_m_texture;
    sf::Sprite bullet_m_sprite;
};

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

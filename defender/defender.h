//
// Created by Deepak Shenoy on 4/9/23.
//

#ifndef INVADER_V_01_DEFENDER_H
#define INVADER_V_01_DEFENDER_H

#include <SFML/Graphics.hpp>
#include "aliens.h"

#define DEFENDER______HEIGHT 72
#define DEFENDER_______WIDTH 72
#define DEFENDER_FROM_BORDER 5
#define DEFENDER___FROM_WALL 10
#define DEFENDER_MOVE___DIST 15
#define DEFENDER_MV_FAST_DIS 30
#define DEFENDER__Y_POSITION MAX_SCREEN_Y_DISTANCE - DEFENDER______HEIGHT- DEFENDER_FROM_BORDER - BORDER_HEIGHT_BOTTOM
#define DEFENDER_LEFT_BORDER DEFENDER_FROM_BORDER
#define DEFENDER_RIGHT_BORDR MAX_SCREEN_X_DISTANCE - DEFENDER_______WIDTH - DEFENDER_FROM_BORDER

#define DEFENDER_BULLET_HGHT 11
#define DEFENDER_BULLET_WIDT 7
#define DEFENDER_BULLET_SPED 20
#define BULLET__TOP___BORDER 12
#define DEFENDER__PATH "./assets/defender/"

class Defender {
public:
    Defender();
    ~Defender();
    void draw(sf::RenderWindow& renderWindowsReference);
    void moveLeft(bool moveFast);
    void moveRight(bool moveFast);
    void fireShot();
    void moveBullet(sf::RenderWindow& renderWindowsReference, AlienFleet& alienFleet, Shields& shields);
    bool firedShot();
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

#endif //INVADER_V_01_DEFENDER_H

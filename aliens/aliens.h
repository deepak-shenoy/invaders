//
// Created by Deepak Shenoy on 4/9/23.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

#include "settings.h"
#include "shields.h"

#ifndef INVADER_V_01_ALIENS_H
#define INVADER_V_01_ALIENS_H

#define MAX_ALIENS__IN_A_ROW 10
#define MAX_NO_OF_ALIEN_ROWS 2
#define NO_OF_ALIEN___IMAGES 7
#define NO_OF_ALEX_EXPL_IMGS 24

#define XDIST_BETWEEN_ALIENS 20
#define YDIST_BETWEEN_ALIENS 20
#define ALIEN___PIXEL__WIDTH 64
#define ALIEN__PIXEL__HEIGHT 64

#define ALIEN___STARTING___X 100
#define ALIEN___STARTING___Y 100

#define ALIEN__LEFT___MARGIN 10
#define ALIEN__RIGHT__MARGIN MAX_SCREEN_X_DISTANCE - ALIEN___PIXEL__WIDTH - BORDER_HEIGHT_BOTTOM
#define ALIEN__BOTTOM_MARGIN MAX_SCREEN_Y_DISTANCE - ALIEN__PIXEL__HEIGHT- BORDER_HEIGHT_BOTTOM
#define ALIENT_MARCH__H_DIST 10
#define ALIENT_MARCH__V_DIST 20

#define ALIEN_BULLET_SPEED00 20
#define ALIEN_BULLET_SPEED01 10
#define ALIEN_BULLET_SPEED02 15

#define ALIEN_____PATH "./assets/aliens/"

class Alien {
public:
    Alien(float x, float y, AlienType alienType);
    void draw(sf::RenderWindow& renderWindowsReference);
    bool isAlive();
    void setAliveOff();
    void setExplosionOn();
    float getX();
    void setX(float xCordVal);
    float getY();
    void setY(float yCordVal);
    void marchStepMovement();
    ~Alien();
private:
    bool alive{true};
    bool exploding{false};
    short int imageMovement{0};
    short int explodingImage{0};
    float XLocation; //{0.0f};
    float YLocation; //{0.0f};
    AlienType alienType;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

class AlienBullet {
public:
    AlienBullet();
    ~AlienBullet();
    void start(float xStartCord, float yStartCord, bool variableBulletSpeed);
    void move(sf::RenderWindow& renderWindowsReference, Shields& shields);
    bool isActive();
private:
    float xCord, yCord;
    bool activeBullet{false};
    float bulletSpeed{ALIEN_BULLET_SPEED00};
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

#endif //INVADER_V_01_ALIENS_H

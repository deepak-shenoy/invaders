/*
 * ===============================================================================================================
 * Shields (coordinates management of all shield components)
 * ===============================================================================================================
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

#include "settings.h"
#include "defender.h"

#ifndef INVADER_V_01_SHIELDS_H
#define INVADER_V_01_SHIELDS_H

#define MAX_SHIELD__GRAPHICS 16
#define NUMBER___OF__SHIELDS 4
#define SHIELD_SPRITE_XCOUNT 2
#define SHIELD_SPRITE_YCOUNT 2
#define SHIELD_SPRITE__WIDTH 64
#define SHIELD_SPRITE_HEIGHT 32
#define SHIELD_BASE_FILE_NAM "./assets/shield/shield-"
#define SHIELD_BASE_BRAK_NAM "./assets/shield/top-"
#define SHIELD_X_SCREEN_DIST (MAX_SCREEN_X_DISTANCE / NUMBER___OF__SHIELDS)
#define SHIELD_OFSET_X_VALUE (MAX_SCREEN_X_DISTANCE / NUMBER___OF__SHIELDS / 2) - ((SHIELD_SPRITE_XCOUNT * SHIELD_SPRITE__WIDTH) /2)
#define SHIELD_HEIGHT_YCOORD DEFENDER__Y_POSITION - (SHIELD_SPRITE_HEIGHT * SHIELD_SPRITE_YCOUNT) - 100

class ShieldUnit {
public:
    ShieldUnit(float xCoord, float yCoord, uint8_t xComponent, uint8_t yComponent);
    void drawUnit(sf::RenderWindow& renderWindowRef);
    float getX();
    float getY();
    bool componentIsUp();
    void decreaseTopShieldState(BulletType bulletType);
    void decreaseBottomShieldState(BulletType bulletType);
private:
    float x;
    float y;
    std::string unitHeightCode;
    unsigned short int unitHeight;
    std::string unitWidthCode;
    unsigned short int unitWidth;
    std::string baseFileName;
    bool up{true};

    sf::Image shieldBaseImage;
    sf::Image shieldTopImage;
    sf::Image shieldBottomImage;

    sf::Texture shieldBaseTexture;
    sf::Texture shieldTopTexture;
    sf::Texture shieldBottomTexture;

    sf::Sprite shieldBaseSprite;
    sf::Sprite shieldTopSprite;
    sf::Sprite shieldBottomSprite;

    sf::RenderTexture combinedShield;

    unsigned short int shieldTopState{0};
    unsigned short int shieldBottomState{0};

    std::string shieldTopStateCode;
    std::string shieldBottomStateCode;
};

class Shields {
public:
    Shields();
    ~Shields();
    void drawShields(sf::RenderWindow& renderWindowRef);
    bool shieldAreaFromTopImpacted(float x, float y, BulletType bulletType);
    bool shieldAreaFromBottomImpacted(float x, float y, BulletType bulletType);
private:
    ShieldUnit* shieldUnits [NUMBER___OF__SHIELDS][SHIELD_SPRITE_XCOUNT][SHIELD_SPRITE_YCOUNT];
};

#endif //INVADER_V_01_SHIELDS_H

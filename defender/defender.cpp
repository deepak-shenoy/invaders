//
// Created by Deepak Shenoy on 4/9/23.
//

#include "defender.h"


Defender::Defender() {
        // Constructor
    }
Defender::~Defender() {
        //Destroyer
    }
    void Defender::draw(sf::RenderWindow& renderWindowsReference) {
        if(shotFired) defender_m_texture.loadFromFile(defenderImage + "defender-01.png");
        else defender_m_texture.loadFromFile(defenderImage + "defender-00.png");
        defender_m_sprite.setTexture(defender_m_texture);
        defender_m_sprite.setPosition(XPos, DEFENDER__Y_POSITION);
        renderWindowsReference.draw(defender_m_sprite);
    }
    void Defender::moveLeft(bool moveFast) {
        if(XPos - DEFENDER_MOVE___DIST > DEFENDER___FROM_WALL) {
            XPos -= moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST;
        }
    }
    void Defender::moveRight(bool moveFast) {
        if(XPos < DEFENDER_RIGHT_BORDR  ) {
            std::cout << (moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST);
            std::cout << "\n";
            XPos += moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST;
        }
    }
    void Defender::fireShot() {
        if(!shotFired) {
            shotFired = true;
            bulletXPos=XPos + DEFENDER_______WIDTH / 2 - 2;
            bulletYPos=DEFENDER__Y_POSITION - DEFENDER_BULLET_HGHT;
        }
    }
    void Defender::moveBullet(sf::RenderWindow& renderWindowsReference, AlienFleet& alienFleet, Shields& shields) {
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
            if(shields.shieldAreaFromTopImpacted(bulletXPos, bulletYPos, defenderBullet)) shotFired = false;
        }
    }
    bool Defender::firedShot() {
        return shotFired;
    }
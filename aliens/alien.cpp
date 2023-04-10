//
// Created by Deepak Shenoy on 4/9/23.
//

#include "aliens.h"

Alien::Alien(float x, float y, AlienType alienType) {
    XLocation = x;
    YLocation = y;
    this->alienType = alienType;
    // Empty constructor
}
void Alien::draw(sf::RenderWindow& renderWindowsReference) {
    if(alive) {
        std::string alientImage{ALIEN_____PATH};
        if (alienType == defender) {
            alientImage.append("row-01-0" + std::to_string(imageMovement));
        } else if (alienType == striker) {
            alientImage.append("row-02-0" + std::to_string(imageMovement));
        }
        alientImage.append(".png");
        m_texture.loadFromFile(alientImage);
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(XLocation, YLocation);
        renderWindowsReference.draw(m_sprite);
    } else if (exploding) {
        std::string alientImage{ALIEN_____PATH};
        std::stringstream filePostfix;
        filePostfix << std::setfill('0') << std::setw(2) << std::to_string(explodingImage);
        alientImage.append("explode-" +      filePostfix.str());
        alientImage.append(".png");
        m_texture.loadFromFile(alientImage);
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(XLocation, YLocation);
        renderWindowsReference.draw(m_sprite);
        explodingImage++;
        if(explodingImage>NO_OF_ALEX_EXPL_IMGS) exploding=false;

    }
}
bool Alien::isAlive() {
    return alive;
}
void Alien::setAliveOff() {
    alive=false;
}
void Alien::setExplosionOn() {
    exploding=true;
}
float Alien::getX() {
    return XLocation;
}
void Alien::setX(float xCordVal) {
    XLocation = xCordVal;
}
float Alien::getY() {
    return YLocation;
}
void Alien::setY(float yCordVal) {
    YLocation = yCordVal;
}
void Alien::marchStepMovement() {
    ++imageMovement %= NO_OF_ALIEN___IMAGES;
}
Alien::~Alien() {
    // Empty de-constructor
}

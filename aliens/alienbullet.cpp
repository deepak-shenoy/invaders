/*
 * ===============================================================================================================
 * Alien Bullet
 * ===============================================================================================================
 */
#include "aliens.h"
AlienBullet::AlienBullet() {
    // Constructor
}
AlienBullet::~AlienBullet() {
    // Destructor
}
void AlienBullet::start(float xStartCord, float yStartCord, bool variableBulletSpeed) {
    if (!activeBullet) {
        xCord = xStartCord + ALIEN___PIXEL__WIDTH / 2;
        yCord = yStartCord + ALIEN__PIXEL__HEIGHT;
        activeBullet = true;
        if(variableBulletSpeed) {
            switch(rand() % 3) {
                case 1:
                    bulletSpeed=ALIEN_BULLET_SPEED01;
                    break;
                case 2:
                    bulletSpeed=ALIEN_BULLET_SPEED02;
                    break;
                case 0:
                default:
                    bulletSpeed=ALIEN_BULLET_SPEED00;
                    break;
            }
        } // Initialized with default setting
    }
}
void AlienBullet::move(sf::RenderWindow& renderWindowsReference, Shields& shields) {
    if(activeBullet) {
        std::string alientBulletImage{ALIEN_____PATH};
        m_texture.loadFromFile(alientBulletImage.append("bullet-00.png"));
        if(shields.shieldAreaFromTopImpacted(xCord, yCord, alienBullet)) {
            activeBullet=false;
            return;
        }
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(xCord, yCord);
        renderWindowsReference.draw(m_sprite);
        yCord+=bulletSpeed;
        if(yCord>DEFENDER__Y_POSITION + DEFENDER______HEIGHT) activeBullet=false;
    }
}
bool AlienBullet::isActive() {
    return activeBullet;
}
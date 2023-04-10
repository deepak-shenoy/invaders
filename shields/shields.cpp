/*
 * ===============================================================================================================
 * Shield
 * ===============================================================================================================
 */

#include "shields.h"

Shields::Shields() {
    // Constructor
    for (int si = 0; si < NUMBER___OF__SHIELDS; si++) {
        for (int sx = 0; sx < SHIELD_SPRITE_XCOUNT; sx++) {
            for (int sy = 0; sy < SHIELD_SPRITE_YCOUNT; sy++) {
                float xCoord = si * SHIELD_X_SCREEN_DIST + SHIELD_OFSET_X_VALUE + (sx * SHIELD_SPRITE__WIDTH);
                float yCoord = sy * SHIELD_SPRITE_HEIGHT + SHIELD_HEIGHT_YCOORD;
                shieldUnits[si][sx][sy] = new ShieldUnit(xCoord, yCoord, sx, sy);
            }
        }
    }
}
Shields::~Shields() {
    // Destructor
}
void Shields::drawShields(sf::RenderWindow& renderWindowRef) {
    for (int si = 0; si < NUMBER___OF__SHIELDS; si ++) {
        for (int sx = 0; sx < SHIELD_SPRITE_XCOUNT; sx++ ) {
            for (int sy = 0; sy < SHIELD_SPRITE_YCOUNT; sy++) {
                shieldUnits[si][sx][sy]->drawUnit(renderWindowRef);
            }
        }
    }
}
bool Shields::shieldAreaImpacted(float x, float y, BulletType bulletType) {
    for (int si = 0; si < NUMBER___OF__SHIELDS; si ++) {
        for (int sx = 0; sx < SHIELD_SPRITE_XCOUNT; sx++ ) {
            for (int sy = 0; sy < SHIELD_SPRITE_YCOUNT; sy++) {
                if(shieldUnits[si][sx][sy]->componentIsUp()) {
                    float shieldX{shieldUnits[si][sx][sy]->getX()};
                    float shieldY{shieldUnits[si][sx][sy]->getY()};
                    if(x>=shieldX && x<=(shieldX + SHIELD_SPRITE__WIDTH) && y>=shieldY && y<=(shieldY + SHIELD_SPRITE_HEIGHT)) {
                        shieldUnits[si][sx][sy]->decreaseShieldState(bulletType);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

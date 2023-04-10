//
// Created by Deepak Shenoy on 4/9/23.
//

#include "shields.h"

ShieldUnit::ShieldUnit(float xCoord, float yCoord, uint8_t xComponent, uint8_t yComponent) {
    x = xCoord;
    y = yCoord;
    std::stringstream tmpXNumberConverter, tmpYNumberConverter, tmpShieldStateCode;
    tmpXNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(xComponent);
    unitHeightCode = tmpXNumberConverter.str();

    tmpYNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(yComponent);
    unitWidthCode = tmpYNumberConverter.str();

    shieldState = 0;

    tmpShieldStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldState);
    shieldStateCode = tmpShieldStateCode.str();

    unitWidth = xComponent;
    unitHeight = yComponent;

}
void ShieldUnit::drawUnit(sf::RenderWindow& renderWindowRef) {
    // Only draw the shield if any part of it exists
    if(up) {
        std::stringstream tmpXNumberConverter, tmpYNumberConverter, tmpShieldStateCode;
        tmpXNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(unitWidth);
        unitHeightCode = tmpXNumberConverter.str();

        tmpYNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(unitHeight);
        unitWidthCode = tmpYNumberConverter.str();

        tmpShieldStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldState);
        shieldStateCode = tmpShieldStateCode.str();

        shieldTexture.loadFromFile(
                SHIELD_BASE_FILE_NAM + unitHeightCode + "-" + unitWidthCode + "-" + shieldStateCode + ".png");
//            std::cout<<SHIELD_BASE_FILE_NAM + unitWidthCode + "-" + unitHeightCode + "-" + shieldStateCode + ".png"<<std::endl;
        shieldSprite.setTexture(shieldTexture);
        shieldSprite.setPosition(x, y);
        renderWindowRef.draw(shieldSprite);
    }
}
float ShieldUnit::getX() {
    return x;
}
float ShieldUnit::getY() {
    return y;
}
bool ShieldUnit::componentIsUp() {
    return up;
}
void ShieldUnit::decreaseShieldState(BulletType bulletType) {
    if (up && ++shieldState<MAX_SHIELD__GRAPHICS) {
        std::cout<<"Shot "<<shieldState<<std::endl;
    } else up = false;
}

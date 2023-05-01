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

    shieldBaseTexture.loadFromFile(
            SHIELD_BASE_FILE_NAM + unitHeightCode + "-" + unitWidthCode + "-00" + ".png");

    shieldBaseImage = shieldBaseTexture.copyToImage();
    shieldBaseImage.createMaskFromColor(sf::Color::Black);
    shieldBaseTexture.loadFromImage(shieldBaseImage);
    shieldBaseSprite.setTexture(shieldBaseTexture);
    shieldBaseSprite.setPosition(x,y);

    shieldTopSprite.setPosition(x, y);
    shieldBottomSprite.setPosition(x, y);

    shieldTopState = 0;
    shieldBottomState = 0;

    tmpShieldStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldTopState);
    shieldTopStateCode = tmpShieldStateCode.str();

    unitWidth = xComponent;
    unitHeight = yComponent;

    combinedShield.create(64, 32);

}
void ShieldUnit::drawUnit(sf::RenderWindow& renderWindowRef) {
    // Only draw the shield if any part of it exists
    if(up) {
        std::stringstream tmpXNumberConverter, tmpYNumberConverter, tmpShieldTopStateCode, tmpShieldBottomStateCode;
        tmpXNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(unitWidth);
        unitHeightCode = tmpXNumberConverter.str();

        tmpYNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(unitHeight);
        unitWidthCode = tmpYNumberConverter.str();

        tmpShieldTopStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldTopState);
        shieldTopStateCode = tmpShieldTopStateCode.str();

        tmpShieldBottomStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldBottomState);
        shieldBottomStateCode = tmpShieldBottomStateCode.str();

        shieldTopTexture.loadFromFile(
                SHIELD_BASE_FILE_NAM + unitHeightCode + "-" + unitWidthCode + "-" + shieldTopStateCode + ".png");

        shieldBottomTexture.loadFromFile(
                SHIELD_BASE_FILE_NAM + unitHeightCode + "-" + unitWidthCode + "-" + shieldBottomStateCode + ".png");

        shieldTopImage = shieldTopTexture.copyToImage();
        shieldBottomImage = shieldBottomTexture.copyToImage();

        shieldTopImage.createMaskFromColor(sf::Color::White);
        shieldBottomImage.createMaskFromColor(sf::Color::White);

        shieldTopSprite.setTexture(shieldTopTexture);
        renderWindowRef.draw(shieldTopSprite);
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
void ShieldUnit::decreaseTopShieldState(BulletType bulletType) {
    if (up && ++shieldTopState<MAX_SHIELD__GRAPHICS) {
        std::cout<<"Shot "<<shieldTopState<<std::endl;
    } else up = false;
}
void ShieldUnit::decreaseBottomShieldState(BulletType bulletType) {
    if (up && ++shieldBottomState<MAX_SHIELD__GRAPHICS) {
        std::cout<<"Shot "<<shieldBottomState<<std::endl;
    } else up = false;
}

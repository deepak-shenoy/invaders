//
// Created by Deepak Shenoy on 4/9/23.
//

#include "shields.h"

ShieldUnit::ShieldUnit(float xCoord, float yCoord, uint8_t xComponent, uint8_t yComponent) {
    x = xCoord;
    y = yCoord;
    std::stringstream tmpXNumberConverter, tmpYNumberConverter, tmpShieldStateCode;
    tmpXNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(xComponent);
    unitWidthCode = tmpXNumberConverter.str();

    tmpYNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(yComponent);
    unitHeightCode = tmpYNumberConverter.str();

    shieldBaseTexture.loadFromFile(
            SHIELD_BASE_FILE_NAM + unitWidthCode + "-" + unitHeightCode + "-00" + ".png");

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
        unitWidthCode = tmpXNumberConverter.str();

        tmpYNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(unitHeight);
        unitHeightCode = tmpYNumberConverter.str();

        tmpShieldTopStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldTopState);
        shieldTopStateCode = tmpShieldTopStateCode.str();

        tmpShieldBottomStateCode << std::setfill('0') << std::setw(2) << std::to_string(shieldBottomState);
        shieldBottomStateCode = tmpShieldBottomStateCode.str();

        shieldTopTexture.loadFromFile(
                SHIELD_BASE_BRAK_NAM + shieldTopStateCode + ".png");

        shieldBottomTexture.loadFromFile(
                SHIELD_BASE_FILE_NAM + unitWidthCode  + "-" + unitHeightCode + "-" + shieldBottomStateCode + ".png");

        shieldTopImage = shieldTopTexture.copyToImage();
        shieldBottomImage = shieldBottomTexture.copyToImage();

        shieldTopImage.createMaskFromColor(sf::Color::White);
        shieldBottomImage.createMaskFromColor(sf::Color::White);

        shieldTopTexture.loadFromImage(shieldTopImage);
        shieldBottomTexture.loadFromImage(shieldBottomImage);

        shieldTopSprite.setTexture(shieldTopTexture);
        shieldBottomSprite.setTexture(shieldBottomTexture);

        renderWindowRef.draw(shieldBaseSprite);
        if(shieldTopState!=0) renderWindowRef.draw(shieldTopSprite);
        if(shieldBottomState!=0) renderWindowRef.draw(shieldBottomSprite);
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
    shieldTopState++;
    if (up && (shieldBottomState + shieldTopState)<MAX_SHIELD__GRAPHICS) {
        std::cout<<"Shield top "<<shieldTopState<<" Shield bottom "<<shieldBottomState<<std::endl;
    } else up = false;
}
void ShieldUnit::decreaseBottomShieldState(BulletType bulletType) {
    shieldBottomState++;
    if (up && (shieldBottomState + shieldTopState)<MAX_SHIELD__GRAPHICS) {
        std::cout<<"Shield top "<<shieldTopState<<" Shield bottom "<<shieldBottomState<<std::endl;
    } else up = false;
}

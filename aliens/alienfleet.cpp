/*
 * ===============================================================================================================
 * Alien Fleet
 * ===============================================================================================================
 */

#include "aliens.h"

AlienFleet::AlienFleet(int maxAlienShots) {
    // Constructor
    maxAlienBullets = maxAlienShots;
    for(int i=0; i<maxAlienBullets; i++) {
        AlienBullet alienBullet = AlienBullet();
        alienBullets.push_back(alienBullet);
    }
    for(int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row ++) {
        for(int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
            float xCord = ALIEN___STARTING___X + alienInRow * (ALIEN___PIXEL__WIDTH + XDIST_BETWEEN_ALIENS);
            float yCord = ALIEN___STARTING___Y + row * (ALIEN__PIXEL__HEIGHT + YDIST_BETWEEN_ALIENS);
            fleet[row][alienInRow] = new Alien(xCord, yCord, AlienType(row % 2));
        }
    }
}
AlienFleet::~AlienFleet() {
    // De-constructor
}
void AlienFleet::drawFleet(sf::RenderWindow& renderWindowsReference) {
    for(int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row ++) {
        for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
            fleet[row][alienInRow]->draw(renderWindowsReference);
        }
    }
}
void AlienFleet::march() {
    if(!reachedBottom) {
        bool nextDirection{moveLeft};
        for (int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row++) {
            for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
                if (moveLeft && fleet[row][alienInRow]->isAlive()) {
                    float xCord{fleet[row][alienInRow]->getX()};
                    if (xCord <= ALIEN__LEFT___MARGIN) nextDirection = !moveLeft;
                    xCord -= ALIENT_MARCH__H_DIST;
                    fleet[row][alienInRow]->marchStepMovement();
                    fleet[row][alienInRow]->setX(xCord);
                } else if (fleet[row][alienInRow]->isAlive()) {
                    float xCord{fleet[row][alienInRow]->getX()};
                    if (xCord >= ALIEN__RIGHT__MARGIN) nextDirection = !moveLeft;
                    xCord += ALIENT_MARCH__H_DIST;
                    fleet[row][alienInRow]->marchStepMovement();
                    fleet[row][alienInRow]->setX(xCord);
                }
            }
        }
        if (nextDirection != moveLeft) {
            for (int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row++) {
                for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
                    if (fleet[row][alienInRow]->isAlive()) {
                        float yCord{fleet[row][alienInRow]->getY()};
                        yCord += ALIENT_MARCH__V_DIST;
                        fleet[row][alienInRow]->setY(yCord);
                        if (yCord >= ALIEN__BOTTOM_MARGIN) reachedBottom = true;
                    }
                }
            }
        }
        moveLeft = nextDirection;
    }
}
bool AlienFleet::alienAreaImpacted(float x, float y) {
    for (int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row++) {
        for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
            if(fleet[row][alienInRow]->isAlive()){
                float yCord{fleet[row][alienInRow]->getY()};
                if(y<yCord || y>(yCord+ALIEN__PIXEL__HEIGHT)) break;
                float xCord{fleet[row][alienInRow]->getX()};
                if(x>=xCord && x<=(xCord+ALIEN___PIXEL__WIDTH)) {
                    fleet[row][alienInRow]->setAliveOff();
                    fleet[row][alienInRow]->setExplosionOn();
                    --activeAliensInFleet;
                    return true;
                }
            }
        }
    }
    return false;
}
void AlienFleet::manageAlienBullets(sf::RenderWindow& renderWindowsReference, Shields& shields) {
    if(activeAliensInFleet > 0) {
        // Prevent continous fire when we have one alien
        if(activeAliensInFleet < maxAlienBullets) maxAlienBullets = activeAliensInFleet;
        for (int i = 0; i < maxAlienBullets; i++) {
            AlienBullet *alienBullet = &alienBullets[i];
            if (!alienBullet->isActive()) {
                int selectedShootingAlien = rand() % (activeAliensInFleet + 1);
                selectedShootingAlien %= (MAX_ALIENS__IN_A_ROW + 1);
                bool foundAlien = false;
                // Search backwards
                for (int row = MAX_NO_OF_ALIEN_ROWS - 1; row >= 0 && !foundAlien; row--) {
                    for (int alienInRow = MAX_ALIENS__IN_A_ROW - 1; alienInRow >= 0 && !foundAlien; alienInRow--) {
                        if (!fleet[row][alienInRow]->isAlive()) continue;
                        if (selectedShootingAlien == 0) {
                            foundAlien = true;
                            float alienXCord = fleet[row][alienInRow]->getX();
                            float alienYCord = fleet[row][alienInRow]->getY();
                            bool variableSpeed{false};
                            if(activeAliensInFleet > 3) variableSpeed=true;
                            alienBullet->start(alienXCord, alienYCord, variableSpeed);
                        }
                        selectedShootingAlien--;
                    }
                }
            }
            alienBullet->move(renderWindowsReference, shields);
        }
    }
}
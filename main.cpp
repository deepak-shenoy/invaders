#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#define MAX_SCREEN_X_DISTANCE 1600
#define MAX_SCREEN_Y_DISTANCE 1600
#define BORDER_HEIGHT_BOTTOM 10
#define BORDER_HEIGHT____TOP 80

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

#define DEFENDER______HEIGHT 72
#define DEFENDER_______WIDTH 72
#define DEFENFER_FROM_BORDER 5
#define DEFEENDER__FROM_WALL 10
#define DEFENDER_MOVE___DIST 15
#define DEFENDER_MV_FAST_DIS 30
#define DEFENDER__Y_POSITION MAX_SCREEN_Y_DISTANCE - DEFENDER______HEIGHT- DEFENFER_FROM_BORDER - BORDER_HEIGHT_BOTTOM
#define DEFENDER_LEFT_BORDER DEFENFER_FROM_BORDER
#define DEFENDER_RIGHT_BORDR MAX_SCREEN_X_DISTANCE - DEFENDER_______WIDTH - DEFENFER_FROM_BORDER

#define DEFENDER_BULLET_HGHT 11
#define DEFENDER_BULLET_WIDT 7
#define DEFENDER_BULLET_SPED 20
#define BULLET__TOP___BORDER 12

#define SHEILD_HEIGHT_YCOORD 90
#define MAX_SHEILD__GRAPHICS 15
#define NUMBER___OF__SHEILDS 4
#define SHIELD_SPRITE_XCOUNT 2
#define SHIELD_SPRITE_YCOUNT 2
#define SHEILD_SPRITE__WIDTH 64
#define SHEILD_SPRITE_HEIGHT 32
#define SHEILD_X_SCREEN_DIST (MAX_SCREEN_X_DISTANCE / NUMBER___OF__SHEILDS)
#define SHIELD_OFSET_X_VALUE (MAX_SCREEN_X_DISTANCE / NUMBER___OF__SHEILDS / 2) - ((SHIELD_SPRITE_XCOUNT * SHEILD_SPRITE__WIDTH) /2)

#define ALIEN_____PATH "./assets/aliens/"
#define DEFENDER__PATH "./assets/defender/"

enum AlienType {defender, striker};

/*
 * ===============================================================================================================
 * Single Alien Definition
 * ===============================================================================================================
 */
class Alien {
public:
    Alien(float x, float y, AlienType alienType) {
        XLocation = x;
        YLocation = y;
        this->alienType = alienType;
        // Empty constructor
    }
    void draw(sf::RenderWindow& renderWindowsReference) {
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
    bool isAilve() {
        return alive;
    }
    void setAliveOff() {
        alive=false;
    }
    void setExplosionOn() {
        exploding=true;
    }
    float getX() {
        return XLocation;
    }
    void setX(float xCordVal) {
        XLocation = xCordVal;
    }
    float getY() {
        return YLocation;
    }
    void setY(float yCordVal) {
        YLocation = yCordVal;
    }
    void marchStepMovement() {
        ++imageMovement %= NO_OF_ALIEN___IMAGES;
    }
    ~Alien() {
        // Empty de-constructor
    }
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

/*
 * ===============================================================================================================
 * Alien Bullet
 * ===============================================================================================================
 */
class AlienBullet {
public:
    AlienBullet() {
        // Constructor
    }
    ~AlienBullet() {
        // Destructor
    }
    void start(float xStartCord, float yStartCord, bool variableBulletSpeed) {
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
    void move(sf::RenderWindow& renderWindowsReference) {
        if(activeBullet) {
            std::string alientBulletImage{ALIEN_____PATH};
            m_texture.loadFromFile(alientBulletImage.append("bullet-00.png"));
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(xCord, yCord);
            renderWindowsReference.draw(m_sprite);
            yCord+=bulletSpeed;
            if(yCord>DEFENDER__Y_POSITION + DEFENDER______HEIGHT) activeBullet=false;
        }
    }
    bool isActive() {
        return activeBullet;
    }
private:
    float xCord, yCord;
    bool activeBullet{false};
    float bulletSpeed{ALIEN_BULLET_SPEED00};
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};
/*
 * ===============================================================================================================
 * Alien Fleet
 * ===============================================================================================================
 */
class AlienFleet {
public:
    AlienFleet(int maxAlienShots) {
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
    ~AlienFleet() {
        // De-constructor
    }
    void drawFleet(sf::RenderWindow& renderWindowsReference) {
        for(int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row ++) {
            for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
                fleet[row][alienInRow]->draw(renderWindowsReference);
            }
        }
    }
    void march() {
        if(!reachedBottom) {
            bool nextDirection{moveLeft};
            for (int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row++) {
                for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
                    if (moveLeft && fleet[row][alienInRow]->isAilve()) {
                        float xCord{fleet[row][alienInRow]->getX()};
                        if (xCord <= ALIEN__LEFT___MARGIN) nextDirection = !moveLeft;
                        xCord -= ALIENT_MARCH__H_DIST;
                        fleet[row][alienInRow]->marchStepMovement();
                        fleet[row][alienInRow]->setX(xCord);
                    } else if (fleet[row][alienInRow]->isAilve()) {
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
                        if (fleet[row][alienInRow]->isAilve()) {
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
    bool alientAreaImpacted(float x, float y) {
        for (int row = 0; row < MAX_NO_OF_ALIEN_ROWS; row++) {
            for (int alienInRow = 0; alienInRow < MAX_ALIENS__IN_A_ROW; alienInRow++) {
                if(fleet[row][alienInRow]->isAilve()){
                    float yCord{fleet[row][alienInRow]->getY()};
                    if(y<yCord || y>(yCord+ALIEN__PIXEL__HEIGHT)) break;
                    float xCord{fleet[row][alienInRow]->getX()};
                    if(x>=xCord && x<=(xCord+ALIEN___PIXEL__WIDTH)) {
                        fleet[row][alienInRow]->setAliveOff();
                        fleet[row][alienInRow]->setExplosionOn();
                        --activeAlientsInFleet;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void manageAlienBullets(sf::RenderWindow& renderWindowsReference) {
        if(activeAlientsInFleet>0) {
            // Prevent continous fire when we have one alien
            if(activeAlientsInFleet<maxAlienBullets) maxAlienBullets = activeAlientsInFleet;
            for (int i = 0; i < maxAlienBullets; i++) {
                AlienBullet *alienBullet = &alienBullets[i];
                if (!alienBullet->isActive()) {
                    int selectedShootingAlien = rand() % (activeAlientsInFleet + 1);
                    selectedShootingAlien %= (MAX_ALIENS__IN_A_ROW + 1);
                    bool foundAlien = false;
                    // Search backwards
                    for (int row = MAX_NO_OF_ALIEN_ROWS - 1; row >= 0 && !foundAlien; row--) {
                        for (int alienInRow = MAX_ALIENS__IN_A_ROW - 1; alienInRow >= 0 && !foundAlien; alienInRow--) {
                            if (!fleet[row][alienInRow]->isAilve()) continue;
                            if (selectedShootingAlien == 0) {
                                foundAlien = true;
                                float alientXCord = fleet[row][alienInRow]->getX();
                                float alientYCord = fleet[row][alienInRow]->getY();
                                bool variableSpeed{false};
                                if(activeAlientsInFleet>3) variableSpeed=true;
                                alienBullet->start(alientXCord, alientYCord, variableSpeed);
                            }
                            selectedShootingAlien--;
                        }
                    }
                }
                alienBullet->move(renderWindowsReference);
            }
        }
    }
private:
    Alien* fleet[MAX_NO_OF_ALIEN_ROWS][MAX_ALIENS__IN_A_ROW];
    bool moveLeft{true};
    bool reachedBottom{false};
    short int activeAlientsInFleet{MAX_NO_OF_ALIEN_ROWS * MAX_ALIENS__IN_A_ROW};
    short int maxAlienBullets;
    std::vector<AlienBullet> alienBullets;
};
/*
 * ===============================================================================================================
 * Sheild
 * ===============================================================================================================
 */
class SheildUnit {
public:
    SheildUnit(float xCoord, float yCoord, uint8_t xComponent, uint8_t yComponent) {
        x = xCoord;
        y = yCoord;
        std::stringstream tmpXNumberConverter, tmpYNumberConverter;
        tmpXNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(xComponent);
        tmpYNumberConverter << std::setfill('0') << std::setw(2) << std::to_string(yComponent);
        baseFileName = "shield-" + tmpXNumberConverter.str() + "-" + tmpYNumberConverter.str() + "-";
    }
private:
    float x;
    float y;
    uint8_t shieldVisibleState{MAX_SHEILD__GRAPHICS};
    std::string baseFileName;
    bool up{true};
};

class Sheilds {
public:
    Sheilds() {
        // Constructor
        for (int si = 0; si < NUMBER___OF__SHEILDS; si++) {
            for (int sx = 0; sx < SHIELD_SPRITE_XCOUNT; sx++) {
                for (int sy = 0; sy < SHIELD_SPRITE_YCOUNT; sy++) {
                    float xCoord = si * SHEILD_X_SCREEN_DIST + SHIELD_OFSET_X_VALUE;
                    float yCoord = sy * SHEILD_SPRITE_HEIGHT + SHEILD_HEIGHT_YCOORD;
                    SheildUnit sheildUnit = SheildUnit(xCoord, yCoord, sx, sy);
                }
            }
        }
    }
    ~Sheilds() {

    }
private:
    SheildUnit* sheildUnit [NUMBER___OF__SHEILDS];
};
/*
 * ===============================================================================================================
 * Defender (user/player)
 * ===============================================================================================================
 */
class Defender {
public:
    Defender() {
        // Constructor
    }
    ~Defender() {
        //Destroyer
    }
    void draw(sf::RenderWindow& renderWindowsReference) {
        if(shotFired) defender_m_texture.loadFromFile(defenderImage + "defender-01.png");
        else defender_m_texture.loadFromFile(defenderImage + "defender-00.png");
        defender_m_sprite.setTexture(defender_m_texture);
        defender_m_sprite.setPosition(XPos, DEFENDER__Y_POSITION);
        renderWindowsReference.draw(defender_m_sprite);
    }
    void moveLeft(bool moveFast) {
        if(XPos - DEFENDER_MOVE___DIST > DEFEENDER__FROM_WALL) {
            XPos -= moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST;
        }
    }
    void moveRight(bool moveFast) {
        if(XPos < DEFENDER_RIGHT_BORDR  ) {
            std::cout << (moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST);
            std::cout << "\n";
            XPos += moveFast? DEFENDER_MV_FAST_DIS : DEFENDER_MOVE___DIST;
        }
    }
    void fireShot() {
        if(!shotFired) {
            shotFired = true;
            bulletXPos=XPos + DEFENDER_______WIDTH / 2 - 2;
            bulletYPos=DEFENDER__Y_POSITION - DEFENDER_BULLET_HGHT;
        }
    }
    void moveBullet(sf::RenderWindow& renderWindowsReference, AlienFleet& alienFleet) {
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
            if (alienFleet.alientAreaImpacted(bulletXPos, bulletYPos)) shotFired = false;
        }
    }
    bool firedShot() {
        return shotFired;
    }
private:
    std::string defenderImage{DEFENDER__PATH};
    bool shotFired{false};
    sf::Texture defender_m_texture;
    sf::Sprite defender_m_sprite;
    float XPos{MAX_SCREEN_X_DISTANCE/2};
    float bulletXPos{0};
    float bulletYPos{0};
    std::string bulletImage{DEFENDER__PATH};
    sf::Texture bullet_m_texture;
    sf::Sprite bullet_m_sprite;
};

/*
 * ===============================================================================================================
 * Main code/logic
 * ===============================================================================================================
 */
int main() {
    sf::RenderWindow window(sf::VideoMode(MAX_SCREEN_X_DISTANCE,MAX_SCREEN_Y_DISTANCE), "Alien Invaders");
    window.setKeyRepeatEnabled(true);
    AlienFleet fleet = AlienFleet(3);
    Sheilds sheilds = Sheilds();
    Defender defender = Defender();
    window.setFramerateLimit(60);
    window.display();
    sf::Event::EventType previousState = sf::Event::MouseEntered;
    sf::Keyboard::Key previousKey = sf::Keyboard::Unknown;
    sf::Keyboard::Key pressedButton;
    while(window.isOpen()) {
        // Clear window
        window.clear();
        fleet.march();
        fleet.drawFleet(window);
        fleet.manageAlienBullets(window);
        defender.draw(window);
        if(defender.firedShot()) {
            defender.moveBullet(window, fleet);
        }
        sf::Event event;
        while(window.pollEvent(event)){
            // Terminate application
            if(event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Handle event closed" << std::endl;
                exit(EXIT_SUCCESS);
            }
            if(event.type == sf::Event::KeyPressed) {
                pressedButton = event.key.code;
                if(pressedButton == sf::Keyboard::Right) {
                    defender.moveRight(previousState == event.type && previousKey == sf::Keyboard::Right);
                    defender.draw(window);
                }
                if(pressedButton == sf::Keyboard::Left) {
                    defender.moveLeft(previousState == event.type && previousKey == sf::Keyboard::Left);
                    defender.draw(window);
                }
                if(pressedButton == sf::Keyboard::Space) {
                    defender.fireShot();
                }
            }
            previousState = event.type;
            previousKey = pressedButton;
        }
        window.display();
    }
    return 0;
}

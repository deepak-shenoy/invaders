#include <iostream>
#include <SFML/Graphics.hpp>

#define MAX_SCREEN_X_DISTANCE 1600
#define MAX_SCREEN_Y_DISTANCE 1600
#define BORDER_HEIGHT_BOTTOM 10

#define MAX_ALIENS__IN_A_ROW 10
#define MAX_NO_OF_ALIEN_ROWS 2
#define NO_OF_ALIEN___IMAGES 7

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

#define DEFENDER______HEIGHT 72
#define DEFENDER_______WIDTH 72
#define DEFENFER_FROM_BORDER 5
#define DEFEENDER__FROM_WALL 10
#define DEFENDER_MOVE___DIST 10
#define DEFENDER__Y_POSITION MAX_SCREEN_Y_DISTANCE - DEFENDER______HEIGHT- DEFENFER_FROM_BORDER - BORDER_HEIGHT_BOTTOM
#define DEFENDER_LEFT_BORDER DEFENFER_FROM_BORDER
#define DEFENDER_RIGHT_BORDR MAX_SCREEN_X_DISTANCE - DEFENDER_______WIDTH - DEFENFER_FROM_BORDER

#define ALIEN_____PATH "./assets/aliens/row-0"
#define DEFENDER__PATH "./assets/defender/defender-0"

enum AlienType {defender, striker};

/*
 *
 * Single Alien Definition
 *
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
                alientImage.append("1-0" + std::to_string(imageMovement));
            } else if (alienType == striker) {
                alientImage.append("2-0" + std::to_string(imageMovement));
            }
            alientImage.append(".png");
            m_texture.loadFromFile(alientImage);
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(XLocation, YLocation);
            renderWindowsReference.draw(m_sprite);
        }
    }
    bool isAilve() {
        return alive;
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
    bool lastLeft{false};
    bool lastRight{false};
    bool alive{true};
    short int direction{0};
    short int imageMovement{0};
    float XLocation; //{0.0f};
    float YLocation; //{0.0f};
    AlienType alienType;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

/*
 *
 * Fleet of aliens
 *
 */
class AlienFleet {
public:
    AlienFleet() {
        // Constructor
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
            std::cout << reachedBottom << std::endl;
            moveLeft = nextDirection;
        }
    }
private:
    Alien* fleet[MAX_NO_OF_ALIEN_ROWS][MAX_ALIENS__IN_A_ROW];
    bool moveLeft{true};
    bool reachedBottom{false};
};

/*
 *
 * Defender (user)
 *
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
        m_texture.loadFromFile(defenderImage + "1.png");
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(XPos, DEFENDER__Y_POSITION);
        renderWindowsReference.draw(m_sprite);
    }
    void moveLeft() {
        if(XPos - DEFENDER_MOVE___DIST > DEFEENDER__FROM_WALL) {
            XPos -= DEFENDER_MOVE___DIST;
        }
    }
    void moveRight() {
        if(XPos < DEFENDER_RIGHT_BORDR  ) {
            XPos += DEFENDER_MOVE___DIST;
        }
    }
private:
    std::string defenderImage{DEFENDER__PATH};
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float XPos{MAX_SCREEN_X_DISTANCE/2};
};

int main() {
    sf::RenderWindow window(sf::VideoMode(MAX_SCREEN_X_DISTANCE,MAX_SCREEN_Y_DISTANCE), "Alien Invaders");
    AlienFleet fleet = AlienFleet();
    Defender defender = Defender();
    window.setFramerateLimit(60);
    window.display();
    while(window.isOpen()) {
        // Clear window
        window.clear();
        fleet.march();
        fleet.drawFleet(window);
        defender.draw(window);
        sf::Event event;
        while(window.pollEvent(event)){
            // Terminate application
            if(event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Handle event closed" << std::endl;
                exit(EXIT_SUCCESS);
            }
            if(event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key pressedButton = event.key.code;
                if(pressedButton == sf::Keyboard::Right) {
                    defender.moveRight();
                    defender.draw(window);
                }
                if(pressedButton == sf::Keyboard::Left) {
                    defender.moveLeft();
                    defender.draw(window);
                }

            }
        }
        window.display();
    }
    return 0;
}

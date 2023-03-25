#include <iostream>
#include <SFML/Graphics.hpp>

#define MAX_ALIENS__IN_A_ROW 10
#define MAX_NO_OF_ALIEN_ROWS 2

#define XDIST_BETWEEN_ALIENS 10
#define YDIST_BETWEEN_ALIENS 10
#define ALIEN___PIXEL__WIDTH 64
#define ALIEN__PIXEL__HEIGHT 64

#define ALIEN___STARTING___X 100
#define ALIEN___STARTING___Y 100

#define MAX_SCREEN_X_DISTANCE 1600
#define MAX_SCREEN_Y_DISTANCE 1600

#define MAIN_FILE_PATH "./assets/aliens/row-0"

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
            std::string alientImage{MAIN_FILE_PATH};
            if (alienType == defender) {
                alientImage.append("1-0" + std::to_string(imageMovement));
            } else if (alienType == striker) {
                alientImage.append("2-0" + std::to_string(imageMovement));
            }
            alientImage.append(".png");
            std::cout << "Selected defender using path " + alientImage + " drawing at " << std::to_string(XLocation)
                      << ", " << std::to_string(YLocation) << "\n";
            m_texture.loadFromFile(alientImage);
            //m_texture.loadFromFile("./assets/aliens/ghost.png");
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(XLocation, YLocation);
            renderWindowsReference.draw(m_sprite);
        }
    }
    void move(float x, float y) {
        XLocation = x;
        YLocation = y;
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
                std::cout<<"( "<<std::to_string(xCord)<<", "<<std::to_string(yCord)<<")  ";
                fleet[row][alienInRow] = new Alien(xCord, yCord, AlienType(row % 2));
            }
            std::cout<<"\n";
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
private:
    Alien* fleet[MAX_NO_OF_ALIEN_ROWS][MAX_ALIENS__IN_A_ROW];
};

int main() {
    sf::RenderWindow window(sf::VideoMode(MAX_SCREEN_X_DISTANCE,MAX_SCREEN_Y_DISTANCE), "Alien Invaders");
    AlienFleet fleet = AlienFleet();
    window.setFramerateLimit(60);
    window.display();
    while(window.isOpen()) {
        // Clear window
        window.clear();
        fleet.drawFleet(window);
        std::cout << "Hello, World!" << std::endl;
        sf::Event event;
        while(window.pollEvent(event)){
            // Terminate application
            if(event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Handle event closed" << std::endl;
                exit(EXIT_SUCCESS);
            }
        }
        window.display();
    }
    return 0;
}

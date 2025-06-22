#pragma once
#include <SFML/Graphics.hpp>
#include "../robot/robot.h"

class Graphics {
    sf::RenderWindow window;
    const int CELL_SIZE = 32;

    sf::Texture wallTexture;
    sf::Sprite wallSprite;
    sf::Texture exitTexture;
    sf::Sprite exitSprite;
    sf::Texture floorTexture;
    sf::Sprite floorSprite;
    sf::Texture robotTexture;
    sf::Sprite robotSprite;
    sf::Font font;
    sf::Font main_font;
    sf::Vector2u mapSize;

    sf::Clock frameClock;
    sf::Texture explosionTexture;
    sf::Sprite explosionSprite;
    int explosionFrameCount = 3;       
    int currentExplosionFrame = 0;     
    float explosionFrameTime = 0.1f;   
    float explosionAnimationTimer = 0; 
    bool explosionPlaying = false; 

    float explosionTotalTime = 0.5f;
    sf::Time explosionStartTime;
    sf::Clock explosionClock;  

public:
    Graphics() = default;
    explicit Graphics(const sf::Vector2u& mapSize);
    void render(const Robot& robot);
    bool isOpen() const { return window.isOpen(); }
    void handleEvents();
    void close() { window.close(); }

private:
    void loadTextures();
    sf::Vector2f calculateCellSize(const Robot& robot) const;
};
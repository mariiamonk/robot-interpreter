#include "graphics.h"
#include <stdexcept>
#include <unistd.h>
#include <limits.h>

Graphics::Graphics(const sf::Vector2u& mapSize) 
    : mapSize(mapSize)
{
    if (mapSize.x == 0 || mapSize.y == 0) {
        throw std::runtime_error("Invalid map size: (" + 
                                std::to_string(mapSize.x) + ", " + 
                                std::to_string(mapSize.y) + ")");
    }

    const unsigned int minCellSize = 128;
    
    unsigned int width = mapSize.x * minCellSize;
    unsigned int height = mapSize.y * minCellSize;
    
    window.create(sf::VideoMode(width, height), "Robot Maze", sf::Style::Resize | sf::Style::Close);
    
    loadTextures();
}
sf::Vector2f Graphics::calculateCellSize(const Robot& robot) const {
    const Environment& env = robot.getEnvironmentC();
    if (env.walls.empty() || env.walls[0].empty()) {
        return {32, 32};
    }

    size_t width = env.walls[0].size();
    size_t height = env.walls.size();

    float cellSize = std::min(
        static_cast<float>(window.getSize().x) / width,
        static_cast<float>(window.getSize().y) / height
    );

    return {cellSize, cellSize};
}



void Graphics::loadTextures() {
    if (!wallTexture.loadFromFile("graphics/sprites/wall.png") ||
        !exitTexture.loadFromFile("graphics/sprites/exit.png") ||
        !floorTexture.loadFromFile("graphics/sprites/ground.png") ||
        !robotTexture.loadFromFile("graphics/sprites/robot_front.png") ||
        !font.loadFromFile("graphics/sprites/font.ttf") ||
        !main_font.loadFromFile("graphics/sprites/mainfont.ttf")) {
        throw std::runtime_error("Failed to load textures or font");
    }

    wallSprite.setTexture(wallTexture);
    exitSprite.setTexture(exitTexture);
    floorSprite.setTexture(floorTexture);
    robotSprite.setTexture(robotTexture);
    
    robotSprite.setOrigin(robotSprite.getLocalBounds().width/2, 
                         robotSprite.getLocalBounds().height/2);

    if (!explosionTexture.loadFromFile("graphics/sprites/robot_front-sheet.png")) {
        throw std::runtime_error("Failed to load explosion texture");
    }
    explosionSprite.setTexture(explosionTexture);
    explosionSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Graphics::render(const Robot& robot) {
    window.clear(sf::Color::White);
    window.setKeyRepeatEnabled(false);

    float frameTime = frameClock.restart().asSeconds();

    const Environment& env = robot.getEnvironmentC();
    const Cell pos = robot.getPosition();
    const Direction dir = robot.getDirection();
    const auto& walls = env.walls;
    const auto& exits = env.exits;

    size_t height = walls.size();
    size_t width = height > 0 ? walls[0].size() : 0;
    
    if (width == 0 || height == 0) return;

    float cellSize = calculateCellSize(robot).x;

    float offsetX = (window.getSize().x - width * cellSize) / 2.0f;
    float offsetY = (window.getSize().y - height * cellSize) / 2.0f;

    auto scaleSprite = [&](sf::Sprite& sprite, const sf::Texture& texture) {
        float scale = cellSize / texture.getSize().x;
        sprite.setScale(scale, scale);
    };

    scaleSprite(floorSprite, floorTexture);
    scaleSprite(wallSprite, wallTexture);
    scaleSprite(exitSprite, exitTexture);
    scaleSprite(robotSprite, robotTexture);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            sf::Vector2f position(
                offsetX + x * cellSize,
                offsetY + y * cellSize
            );

            floorSprite.setPosition(position);
            window.draw(floorSprite);

            if (walls[y][x] == CellType::WALL) {
                wallSprite.setPosition(position);
                window.draw(wallSprite);
            }

            if (exits[y][x] == CellType::EXIT) {
                exitSprite.setPosition(position);
                window.draw(exitSprite);
            }
        }
    }

    if (!robot.isDestroyed()) {
        robotSprite.setPosition(
            offsetX + (pos.second + 0.5f) * cellSize,
            offsetY + (pos.first + 0.5f) * cellSize
        );
        
        switch(dir) {
            case Direction::NORTH: robotTexture.loadFromFile("graphics/sprites/robot_back.png"); break;
            case Direction::EAST:  robotTexture.loadFromFile("graphics/sprites/robot_left.png"); break;
            case Direction::SOUTH: robotTexture.loadFromFile("graphics/sprites/obot_front.png"); break;
            case Direction::WEST:  robotTexture.loadFromFile("graphics/sprites/robot_right.png"); break;
        }

        window.draw(robotSprite);
    }

    sf::Text statusText;
    statusText.setCharacterSize(70);
    statusText.setFont(font);

    sf::Vector2u windowSize = window.getSize();

    if (robot.isDestroyed()) {
        if (!explosionPlaying) {
            explosionPlaying = true;
            currentExplosionFrame = 0;
            explosionAnimationTimer = 0;
            explosionSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            explosionStartTime = explosionClock.restart(); 
        }

        explosionAnimationTimer += frameTime;
        if (explosionAnimationTimer >= explosionFrameTime && 
            currentExplosionFrame < explosionFrameCount - 1) {
            
            currentExplosionFrame++;
            explosionSprite.setTextureRect(sf::IntRect(currentExplosionFrame * 32, 0, 32, 32));
            explosionAnimationTimer = 0;
        }

        explosionSprite.setPosition(
            offsetX + (pos.second + 0.5f) * cellSize,
            offsetY + (pos.first + 0.5f) * cellSize
        );

        float scale = cellSize / 32.0f;
        explosionSprite.setScale(scale, scale);
        explosionSprite.setOrigin(16, 16);

        window.draw(explosionSprite);

        if (explosionClock.getElapsedTime().asSeconds() > explosionTotalTime) {
            statusText.setString("DESTROYED!");
            statusText.setFillColor(sf::Color(199,21,133));
            
            sf::FloatRect textRect = statusText.getLocalBounds();
            statusText.setOrigin(textRect.left + textRect.width/2.0f,
                            textRect.top + textRect.height/2.0f);
            statusText.setPosition(windowSize.x/2.0f, windowSize.y/2.0f);
            window.draw(statusText);
        }
        window.display();
    } 
    else if (robot.hasReachedExit()) {
        statusText.setString("EXIT REACHED!");
        statusText.setFillColor(sf::Color(139,58,131));
        
        sf::FloatRect textRect = statusText.getLocalBounds();
        statusText.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top + textRect.height/2.0f);
        statusText.setPosition(windowSize.x/2.0f, windowSize.y/2.0f);
        window.draw(statusText);
        window.display();
        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            handleEvents(); 
            if (!window.isOpen()) break; 
            sf::sleep(sf::milliseconds(100)); 
        }
        window.close();
    }
    window.display();
}

void Graphics::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
    }
}

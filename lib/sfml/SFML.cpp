/*
** EPITECH PROJECT, 2020
** sfml.cpp
** File description:
** sfml
*/

#include "SFML.hpp"

graphicals::SFML::SFML()
: window(sf::VideoMode(1920, 1080, 32), "Graphics!", sf::Style::Fullscreen)
{
    if (!font.loadFromFile("./assets/font.ttf"))
        std::exit(84);
    window.display();
}

graphicals::SFML::~SFML()
{
    window.close();
}

void graphicals::SFML::newGame(std::string newGame)
{
    assetsList.clear();
    _loadedGame = newGame;
    if (newGame == "./games/lib_arcade_nibbler.so")
        loadNibblerAssets();
    else if (newGame == "./games/lib_arcade_solarfox.so")
        loadSolarFoxAssets();
}

graphicals::Input graphicals::SFML::getInput()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                return (graphicals::Input::ESCAPE);
            if (event.key.code == sf::Keyboard::Left)
                return (graphicals::Input::LEFT);
            if (event.key.code == sf::Keyboard::Right)
                return (graphicals::Input::RIGHT);
            if (event.key.code == sf::Keyboard::Up)
                return (graphicals::Input::UP);
            if (event.key.code == sf::Keyboard::Down)
                return (graphicals::Input::DOWN);
            if (event.key.code == sf::Keyboard::Space)
                return (graphicals::Input::SPACE);
            if (event.key.code == sf::Keyboard::I)
                return (graphicals::Input::PREVLIB);
            if (event.key.code == sf::Keyboard::O)
                return (graphicals::Input::NEXTLIB);
            if (event.key.code == sf::Keyboard::K)
                return (graphicals::Input::PREVGAME);
            if (event.key.code == sf::Keyboard::L)
                return (graphicals::Input::NEXTGAME);
            if (event.key.code == sf::Keyboard::R)
                return (graphicals::Input::RESET);
            if (event.key.code == sf::Keyboard::M)
                return (graphicals::Input::MENU);
            if (event.key.code == sf::Keyboard::S)
                return (graphicals::Input::SPEED);
        }
    }
    return graphicals::Input::NONE;
}

void graphicals::SFML::printCommands()
{
    sf::Text prevLibText("PrevLib: i", font, 20);
    sf::Text nextLibText("NextLib: o", font, 20);
    sf::Text prevGameText("PrevGame: k", font, 20);
    sf::Text nextGameText("NextLib: l", font, 20);
    sf::Text resetText("Reset: r", font, 20);
    sf::Text menuText("Menu: M", font, 20);
    sf::Text quitText("Quit: Escape", font, 20);

    prevLibText.setPosition(sf::Vector2f(1730, 60));
    nextLibText.setPosition(sf::Vector2f(1730, 80));
    prevGameText.setPosition(sf::Vector2f(1730, 100));
    nextGameText.setPosition(sf::Vector2f(1730, 120));
    resetText.setPosition(sf::Vector2f(1730, 200));
    menuText.setPosition(sf::Vector2f(1730, 250));
    quitText.setPosition(sf::Vector2f(1730, 300));

    window.draw(prevLibText);
    window.draw(nextLibText);
    window.draw(prevGameText);
    window.draw(nextGameText);
    window.draw(resetText);
    window.draw(menuText);
    window.draw(quitText);
}

void graphicals::SFML::printScore(int score)
{
    std::string scoreString("Score: " + std::to_string(score));
    sf::Text scoreText(scoreString, font, 22);

    scoreText.setPosition(sf::Vector2f(60, 20));
    window.draw(scoreText);
}

void graphicals::SFML::printSprite(int asset, int x, int y)
{
    SFMLSprite obj = assetsList[asset];
    obj.setSpritePosition(x, y);
    window.draw(obj.getSprite());
}

void graphicals::SFML::drawMap(const utilitaries::GameMap &map)
{
    window.clear();

    if (_loadedGame == "./games/lib_arcade_nibbler.so")
        drawNibbler(map);
    else if (_loadedGame == "./games/lib_arcade_solarfox.so")
        drawSolarFox(map);
}

void graphicals::SFML::drawNibbler(const utilitaries::GameMap &map)
{
    int x = 60;
    int y = 60;

    std::vector<std::vector<int>> newMap = map.getMap();

    for (std::vector<int> assetLine : newMap) {
        for (int asset : assetLine) {
            printSprite(asset, x, y);
            x += 60;
        }
        y += 60;
        x = 60;
    }

    printCommands();
    printScore(map.getScore());
    window.display();
    sf::sleep(sf::microseconds(map.getSleep()));
}

void graphicals::SFML::drawSolarFox(const utilitaries::GameMap &map)
{
    int x = 60;
    int y = 60;

    std::vector<std::vector<int>> newMap = map.getMap();

    for (std::vector<int> assetLine : newMap) {
        for (int asset : assetLine) {
            if (asset == utilitaries::SOLAR_FOX_ASSETS_E::WALLLASERHORIZONTAL) {
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX, x, y);
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL, x, y);
            } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::WALLLASERVERTICAL) {
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX, x, y);
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL, x, y);
            } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::COINLASERHORIZONTAL) {
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::COIN, x, y);
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL, x, y);
            } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::COINLASERVERTICAL) {
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::COIN, x, y);
                printSprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL, x, y);
            } else
                printSprite(asset, x, y);
            x += 60;
        }
        y += 60;
        x = 60;
    }

    printCommands();
    printScore(map.getScore());
    window.display();
    sf::sleep(sf::microseconds(map.getSleep()));
}

void graphicals::SFML::loadNibblerAssets()
{
     assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 195, 0, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 260, 65, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 195, 65, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 260, 0, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 70, 0, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 130, 65, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 195, 130, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 258, 195, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 195, 192, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 260, 128, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 4, 0, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 4, 65, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 130, 0, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 130, 130, 60));
    assetsList.push_back(SFMLSprite("./assets/wall.png", 0, 0, 60));
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 65, 65, 60)); // blank
    assetsList.push_back(SFMLSprite("./assets/snake-graphics.png", 4, 195, 60));
}

void graphicals::SFML::loadSolarFoxAssets()
{
    assetsList.push_back(SFMLSprite("assets/ship-sprite.png", 141, 7, 60));
    assetsList.push_back(SFMLSprite("assets/ship-sprite.png", 141, 455, 60));
    assetsList.push_back(SFMLSprite("assets/ship-sprite.png", 130, 334, 60));
    assetsList.push_back(SFMLSprite("assets/ship-sprite.png", 136, 140, 60));
    assetsList.push_back(SFMLSprite("assets/horizontal_red_laser.png", 0, 0, 60));
    assetsList.push_back(SFMLSprite("assets/vertical_red_laser.png", 0, 0, 60));
    assetsList.push_back(SFMLSprite("assets/horizontal_blue_laser.png", 0, 0, 60));
    assetsList.push_back(SFMLSprite("assets/vertical_blue_laser.png", 0, 0, 60));
    assetsList.push_back(SFMLSprite("assets/skull-again.png", 0, 0, 58));
    assetsList.push_back(SFMLSprite("assets/coin-transparent.png", 2, 95, 60));
    assetsList.push_back(SFMLSprite("assets/wall.png", 0, 0, 60));
    assetsList.push_back(SFMLSprite("assets/snake-graphics.png", 65, 65, 60)); // blank
}

extern "C" std::unique_ptr<graphicals::IGraphicalModule> loadLib() {
    return std::make_unique<graphicals::SFML>();
}

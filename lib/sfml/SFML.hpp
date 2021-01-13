/*
** EPITECH PROJECT, 2020
** sfml.hpp
** File description:
** sfml
*/

#ifndef _SFML_
#define _SFML_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "IGraphicalModule.hpp"
#include "SFMLSprite.hpp"

namespace graphicals {
    class SFML : public IGraphicalModule
    {
    public:
        SFML();
        ~SFML();

        void newGame(std::string newGame) override;

        graphicals::Input getInput() override;
        void drawMap(const utilitaries::GameMap &map) override;

    private:
        void loadNibblerAssets();
        void loadSolarFoxAssets();

        void drawNibbler(const utilitaries::GameMap &map);
        void drawSolarFox(const utilitaries::GameMap &map);
        void printCommands();
        void printScore(int score);
        void printSprite(int sprite, int x, int y);

        std::string _loadedGame;
        std::vector<SFMLSprite> assetsList;
        sf::Font font;
        sf::RenderWindow window;
    };
}

#endif

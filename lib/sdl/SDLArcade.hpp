/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#ifndef SDLArcade_HPP_
#define SDLArcade_HPP_

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "IGraphicalModule.hpp"
#include "SDLSprite.hpp"

namespace graphicals {
    class SDLArcade: public IGraphicalModule {
        public:
            SDLArcade();
            ~SDLArcade();

            void newGame(std::string newGame) override;

            graphicals::Input getInput() override;
            void drawMap(const utilitaries::GameMap &map) override;

        private:
            void loadNibblerSprites();
            void loadSolarFoxSprites();

            void drawNibbler(std::vector<std::vector<int>> map);
            void drawSolarFox(std::vector<std::vector<int>> map);

            void displayCommands();
            void displayScore(int score);
            void displaySprite(int asset, int x, int y);

            SDL_Window *_window;
            SDL_Renderer *_renderer;
            TTF_Font *_font;
            std::string _loadedGame;
            std::vector<std::unique_ptr<SDLSprite>> _assetsList;
    };
}

#endif /* !SDL_HPP_ */

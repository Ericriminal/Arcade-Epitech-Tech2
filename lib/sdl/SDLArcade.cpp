/*
** EPITECH PROJECT, 6060
** OOP_arcade_6019
** File description:
** SDL
*/

#include "SDLArcade.hpp"

graphicals::SDLArcade::SDLArcade() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        exit(84);

    if (TTF_Init() != 0)
        exit(84);

    this->_window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    if (!this->_window)
        exit(84);

    if (SDL_SetWindowFullscreen(this->_window, SDL_WINDOW_FULLSCREEN) != 0)
        exit(84);

    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!this->_renderer)
        exit(84);

    this->_font = TTF_OpenFont("./assets/font.ttf", 30);
    if (!this->_font)
        exit(84);
}

graphicals::SDLArcade::~SDLArcade() {
    if (this->_renderer)
        SDL_DestroyRenderer(this->_renderer);
    if (this->_window)
        SDL_DestroyWindow(this->_window);

    TTF_CloseFont(this->_font);
    TTF_Quit();
    SDL_Quit();
}

void graphicals::SDLArcade::newGame(std::string newGame) {
    this->_assetsList.clear();

    if (newGame == "./games/lib_arcade_nibbler.so")
        this->loadNibblerSprites();
    else if (newGame == "./games/lib_arcade_solarfox.so")
        this->loadSolarFoxSprites();
    this->_loadedGame = newGame;
}

graphicals::Input graphicals::SDLArcade::getInput() {
    Input userInput = Input::NONE;
    SDL_Event event;

    if (SDL_PollEvent(&event) == 1) {
        switch (event.type) {
            case SDL_QUIT:
                userInput = Input::NONE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    userInput = Input::ESCAPE;
                else if (event.key.keysym.sym == SDLK_DOWN)
                    userInput = Input::DOWN;
                else if (event.key.keysym.sym == SDLK_UP)
                    userInput = Input::UP;
                else if (event.key.keysym.sym == SDLK_LEFT)
                    userInput = Input::LEFT;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    userInput = Input::RIGHT;
                else if (event.key.keysym.sym == SDLK_i)
                    userInput = Input::PREVLIB;
                else if (event.key.keysym.sym == SDLK_o)
                    userInput = Input::NEXTLIB;
                else if (event.key.keysym.sym == SDLK_k)
                    userInput = Input::PREVGAME;
                else if (event.key.keysym.sym == SDLK_l)
                    userInput = Input::NEXTGAME;
                else if (event.key.keysym.sym == SDLK_r)
                    userInput = Input::RESET;
                else if (event.key.keysym.sym == SDLK_m)
                    userInput = Input::MENU;
                else if (event.key.keysym.sym == SDLK_s)
                    userInput = Input::SPEED;
                else if (event.key.keysym.sym == SDLK_SPACE)
                    userInput = Input::SPACE;
                break;
            default:
                userInput = Input::NONE;
        }
    }
    SDL_FlushEvents(0, 2000);
    return (userInput);
}

void graphicals::SDLArcade::displayCommands() {
    std::string prevLibString("PrevLib: i");
    std::string nextLibString("NextLib: o");
    std::string prevGameString("PrevGame: k");
    std::string nextGameString("NextGame: l");
    std::string resetString("Reset: r");
    std::string menuString("Menu: m");
    std::string quitString("Quit: Escape");

    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *prevLibSurface = TTF_RenderText_Solid(this->_font, prevLibString.c_str(), color);
    SDL_Surface *nextLibSurface = TTF_RenderText_Solid(this->_font, nextLibString.c_str(), color);
    SDL_Surface *prevGameSurface = TTF_RenderText_Solid(this->_font, prevGameString.c_str(), color);
    SDL_Surface *nextGameSurface = TTF_RenderText_Solid(this->_font, nextGameString.c_str(), color);
    SDL_Surface *resetSurface = TTF_RenderText_Solid(this->_font, resetString.c_str(), color);
    SDL_Surface *menuSurface = TTF_RenderText_Solid(this->_font, menuString.c_str(), color);
    SDL_Surface *quitSurface = TTF_RenderText_Solid(this->_font, quitString.c_str(), color);

    SDL_Rect prevLibRect = {1860 - prevLibSurface->w, 60, prevLibSurface->w, prevLibSurface->h};
    SDL_Rect nextLibRect = {1860 - nextLibSurface->w, 100, nextLibSurface->w, nextLibSurface->h};
    SDL_Rect prevGameRect = {1860 - prevGameSurface->w, 140, prevGameSurface->w, prevGameSurface->h};
    SDL_Rect nextGameRect = {1860 - nextGameSurface->w, 180, nextGameSurface->w, nextGameSurface->h};
    SDL_Rect resetRect = {1860 - resetSurface->w, 280, resetSurface->w, resetSurface->h};
    SDL_Rect menuRect = {1860 - menuSurface->w, 320, menuSurface->w, menuSurface->h};
    SDL_Rect quitRect = {1860 - quitSurface->w, 450, quitSurface->w, quitSurface->h};

    SDL_Texture *prevLibTexture = SDL_CreateTextureFromSurface(this->_renderer, prevLibSurface);
    SDL_Texture *nextLibTexture = SDL_CreateTextureFromSurface(this->_renderer, nextLibSurface);
    SDL_Texture *prevGameTexture = SDL_CreateTextureFromSurface(this->_renderer, prevGameSurface);
    SDL_Texture *nextGameTexture = SDL_CreateTextureFromSurface(this->_renderer, nextGameSurface);
    SDL_Texture *resetTexture = SDL_CreateTextureFromSurface(this->_renderer, resetSurface);
    SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(this->_renderer, menuSurface);
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(this->_renderer, quitSurface);

    SDL_RenderCopy(this->_renderer, prevLibTexture, NULL, &prevLibRect);
    SDL_RenderCopy(this->_renderer, nextLibTexture, NULL, &nextLibRect);
    SDL_RenderCopy(this->_renderer, prevGameTexture, NULL, &prevGameRect);
    SDL_RenderCopy(this->_renderer, nextGameTexture, NULL, &nextGameRect);
    SDL_RenderCopy(this->_renderer, resetTexture, NULL, &resetRect);
    SDL_RenderCopy(this->_renderer, menuTexture, NULL, &menuRect);
    SDL_RenderCopy(this->_renderer, quitTexture, NULL, &quitRect);

    SDL_DestroyTexture(prevLibTexture);
    SDL_FreeSurface(prevLibSurface);
    SDL_DestroyTexture(nextLibTexture);
    SDL_FreeSurface(nextLibSurface);
    SDL_DestroyTexture(nextGameTexture);
    SDL_FreeSurface(nextGameSurface);
    SDL_DestroyTexture(prevGameTexture);
    SDL_FreeSurface(prevGameSurface);
    SDL_DestroyTexture(resetTexture);
    SDL_FreeSurface(resetSurface);
    SDL_DestroyTexture(menuTexture);
    SDL_FreeSurface(menuSurface);
    SDL_DestroyTexture(quitTexture);
    SDL_FreeSurface(quitSurface);
}

void graphicals::SDLArcade::displayScore(int score) {
    std::string scoreString("Score: " + std::to_string(score));
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(this->_font, scoreString.c_str(), color);
    SDL_Rect rect = {60, 15, surface->w, surface->h};
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, surface);


    SDL_RenderCopy(this->_renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void graphicals::SDLArcade::displaySprite(int asset, int x, int y) {
    SDL_Rect dest = {x, y, 60, 60};
    SDL_Rect src = this->_assetsList[asset]->getRect();
    SDL_Texture *texture = this->_assetsList[asset]->getTexture();

    SDL_RenderCopy(this->_renderer, texture, &src, &dest);
}

void graphicals::SDLArcade::drawMap(const utilitaries::GameMap &map) {
    SDL_RenderClear(this->_renderer);

    std::vector<std::vector<int>> newMap = map.getMap();

    if (this->_loadedGame == "./games/lib_arcade_nibbler.so")
        this->drawNibbler(newMap);
    else if (this->_loadedGame == "./games/lib_arcade_solarfox.so")
        this->drawSolarFox(newMap);

    this->displayCommands();
    this->displayScore(map.getScore());

    SDL_RenderPresent(this->_renderer);
    SDL_Delay(map.getSleep() / 1000);
}

void graphicals::SDLArcade::drawNibbler(std::vector<std::vector<int>> map) {
    int y = 60;
    int x = 60;

    for (std::vector<int> assetLine : map) {
        for (int asset : assetLine) {
            this->displaySprite(asset, x, y);
            x += 60;
        }
        y += 60;
        x = 60;
    }
}

void graphicals::SDLArcade::drawSolarFox(std::vector<std::vector<int>> map) {
    int x = 60;
    int y = 60;

    for (std::vector<int> assetLine : map) {
        for (int asset : assetLine) {
            if (asset == utilitaries::SOLAR_FOX_ASSETS_E::WALLLASERHORIZONTAL) {
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX, x, y);
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL, x, y);
            } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::WALLLASERVERTICAL) {
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX, x, y);
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL, x, y);
            } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::COINLASERHORIZONTAL) {
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::COIN, x, y);
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL, x, y);
            } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::COINLASERVERTICAL) {
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::COIN, x, y);
                displaySprite(utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL, x, y);
            } else
                displaySprite(asset, x, y);
            x += 60;
        }
        y += 60;
        x = 60;
    }
}

// Load Games and Menu sprites
void graphicals::SDLArcade::loadNibblerSprites() {
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 195, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 260, 65, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 195, 65, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 260, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 70, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 130, 65, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 195, 130, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 258, 195, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 195, 192, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 260, 128, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 4, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 4, 65, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 130, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 130, 130, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/wall.png", this->_renderer, 0, 0, 200));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 65, 65, 60)); // blank
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 4, 195, 60));
}

void graphicals::SDLArcade::loadSolarFoxSprites() {
    this->_assetsList.emplace_back(new SDLSprite("assets/ship-sprite.png", this->_renderer, 141, 7, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/ship-sprite.png", this->_renderer, 141, 455, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/ship-sprite.png", this->_renderer, 130, 334, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/ship-sprite.png", this->_renderer, 136, 140, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/horizontal_red_laser.png", this->_renderer, 0, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/vertical_red_laser.png", this->_renderer, 0, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/horizontal_blue_laser.png", this->_renderer, 0, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/vertical_blue_laser.png", this->_renderer, 0, 0, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/skull-again.png", this->_renderer, 0, 0, 58));
    this->_assetsList.emplace_back(new SDLSprite("assets/coin-transparent.png", this->_renderer, 2, 95, 60));
    this->_assetsList.emplace_back(new SDLSprite("assets/wall.png", this->_renderer, 0, 0, 200));
    this->_assetsList.emplace_back(new SDLSprite("assets/snake-graphics.png", this->_renderer, 65, 65, 60)); // blank
}

extern "C" std::unique_ptr<graphicals::IGraphicalModule> loadLib() {
    return std::make_unique<graphicals::SDLArcade>();
}

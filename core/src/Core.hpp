/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#ifndef _Core_
#define _Core_

#include <experimental/filesystem>
#include "Assets.hpp"
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <algorithm>
#include "../../lib/IGraphicalModule.hpp"
#include "../../games/IGamesModule.hpp"

class Core {
    public:
        Core();
        ~Core();

        void menu(const std::string &name, const std::string &libName);
        void checkLib(const std::string &libName);

    private:
        void scores();
        void loadLibrary(const std::string &libPath);
        void loadGame(const std::string &gamePath);
        void run(const std::string &libName, const std::string &gameName);
        void findLibraries();
        void findGames();
        void setLib(const std::string &libName);
        void setGame(const std::string &gameName);
        unsigned int whatPlay(bool err);

        std::unique_ptr<graphicals::IGraphicalModule> lib;
        std::unique_ptr<games::IGameModule> game;
        std::vector<std::string> libs;
        std::vector<std::string> games;
        std::string curLib;
        std::string curGame;
        int score;
        std::string userName;
        void *libHndl;
        void *gameHndl;
};

#endif /* _Core_ */

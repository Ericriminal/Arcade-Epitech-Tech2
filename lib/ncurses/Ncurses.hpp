/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#ifndef _NCurses_
#define _NCurses_

#include "IGraphicalModule.hpp"
#include <curses.h>

namespace graphicals {
    class NCurses : public graphicals::IGraphicalModule
    {
    public:
        NCurses();
        ~NCurses();
        void newGame(std::string newGame) override;
        graphicals::Input getInput() override;
        void drawMap(const utilitaries::GameMap &map) override;
        private:
        void printChar(std::string tmp, int x, int y);
        WINDOW *window;
        std::string assetsList;
    };
}

#endif /* _NCurses_ */

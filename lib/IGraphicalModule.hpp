/*
** EPITECH PROJECT, 2020
**
** File description:
**
*/

#ifndef _IGRAPHICALMODULE_
#define _IGRAPHICALMODULE_

#include "../core/src/Assets.hpp"

namespace graphicals {
    class IGraphicalModule
    {
    public:
        virtual ~IGraphicalModule() = default;

        virtual void newGame(std::string newGame) = 0;
        virtual Input getInput() = 0;
        virtual void drawMap(const utilitaries::GameMap &map) = 0;
    };
}

#endif /* _IGraphicalModule_ */

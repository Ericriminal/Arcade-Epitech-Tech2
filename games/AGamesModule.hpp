/*
** EPITECH PROJECT, 2020
** AGameModule
** File description:
** AGameModule
*/

#ifndef _AGAMEMODULE_
#define _AGAMEMODULE_

#include "IGamesModule.hpp"

namespace games {
    class AGameModule : public IGameModule
    {
    public:
        virtual ~AGameModule() = default;
    protected:
        utilitaries::GameMap _startMap;
        utilitaries::GameMap _map;
    };
}

#endif

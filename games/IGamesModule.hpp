/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#ifndef _IGAMEMODULE_
#define _IGAMEMODULE_

#include "../core/src/Assets.hpp"

namespace games {
    class IGameModule{
        public:
            virtual ~IGameModule() = default;

            virtual const utilitaries::GameMap &nextCycle(graphicals::Input input = graphicals::Input::NONE) = 0;
        };
}

#endif /* _IGameModule_ */

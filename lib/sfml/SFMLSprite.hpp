/*
** EPITECH PROJECT, 2020
** sfmlSprite
** File description:
** sfmlSprite
*/

#ifndef _SFMLSPRITE_
#define _SFMLSPRITE_

#include <SFML/Graphics.hpp>
#include "../../core/src/Assets.hpp"

namespace graphicals {
    class SFMLSprite
    {
    public:
        SFMLSprite(const std::string &filepath, int x, int y, int size);
        ~SFMLSprite();
        void setSpritePosition(int x, int y);
        const sf::Sprite &getSprite();

    private:
        sf::Texture texture;
        sf::Sprite sprite;
    };
}

#endif

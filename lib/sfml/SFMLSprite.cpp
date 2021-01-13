/*
** EPITECH PROJECT, 2020
** sfmlSprite
** File description:
** sfmlSprite
*/

#include "SFMLSprite.hpp"

graphicals::SFMLSprite::SFMLSprite(const std::string &filepath, int x, int y, int size)
{
    if (!this->texture.loadFromFile(filepath, sf::IntRect(x, y, size, size)))
        this->texture.create(60, 60);
}

graphicals::SFMLSprite::~SFMLSprite()
{
}

void graphicals::SFMLSprite::setSpritePosition(int x, int y)
{
    sf::Vector2f vec(x, y);
    this->sprite.move(vec);
}

const sf::Sprite &graphicals::SFMLSprite::getSprite()
{
    this->sprite.setTexture(this->texture);
    return this->sprite;
}

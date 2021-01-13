/*
** EPITECH PROJECT, 2020
** enum.cpp
** File description:
** enum
*/

#include "Assets.hpp"

utilitaries::GameMap::GameMap()
{
    this->score = 0;
}

std::vector<std::vector<int>> utilitaries::GameMap::getMap() const
{
    return _map;
}

void utilitaries::GameMap::setMap(std::vector<std::vector<int>> map)
{
    this->_map = map;
}

void utilitaries::GameMap::setAssetInMap(int x, int y, int asset)
{
    this->_map[y][x] = asset;
}

int utilitaries::GameMap::getAssetInMap(int x, int y)
{
    return this->_map[y][x];
}

void utilitaries::GameMap::setSleep(int sleepTime)
{
    this->sleepTime = sleepTime;
}

int utilitaries::GameMap::getSleep(void) const
{
    return this->sleepTime;
}

void utilitaries::GameMap::reduceSleep(int sleep)
{
    this->sleepTime -= sleep;
}

int utilitaries::GameMap::getScore(void) const
{
    return (score);
}

void utilitaries::GameMap::setScore(int new_score)
{
    this->score = new_score;
}

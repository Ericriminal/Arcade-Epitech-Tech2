/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Nibbler
*/

#include <utility>
#include <unistd.h>
#include "Nibbler.hpp"

games::Nibbler::Nibbler()
{
    std::vector<std::vector<int>> map = this->createMap();
    this->move = Movement::LEFT;
    this->oldMove = this->move;
    this->start = true;
    this->collision = false;
    this->win = false;
    this->_map.setSleep(500000);
    this->_startMap.setSleep(500000);
    this->_map.setMap(map);
    this->_startMap.setMap(map);
    this->AppleEat = false;
    srand (time(NULL));
}

games::Nibbler::~Nibbler()
{
}

std::vector<std::vector<int>> games::Nibbler::createMap()
{
    std::vector<std::vector<int>> map;
    int wall = static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::WALL_NIBBLER);
    int blank = static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER);

    std::vector<int> middleLine = {wall, blank, blank, blank, blank, blank, blank,
        blank, blank, blank, blank, blank, blank, blank, wall};
    std::vector<int> borderLine = {wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall};
    std::vector<int> snakeLine = {wall, blank, blank,
        static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::APPLE),
        blank, blank,
        static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADLEFT),
        static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYHORIZONTAL),
        static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYHORIZONTAL),
        static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILLEFT),
        blank, blank, blank, blank, wall};
    map.push_back(borderLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(snakeLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(middleLine);
    map.push_back(borderLine);
    return map;
}

void games::Nibbler::checkInput(graphicals::Input input)
{
    this->oldMove = this->move;
    switch (this->move) {
        case Movement::UP:
            if (input == graphicals::LEFT)
                move = Movement::LEFT;
            else if (input == graphicals::RIGHT)
                move = Movement::RIGHT;
            break;
        case Movement::DOWN:
            if (input == graphicals::LEFT)
                move = Movement::LEFT;
            else if (input == graphicals::RIGHT)
                move = Movement::RIGHT;
            break;
        case Movement::LEFT:
            if (input == graphicals::DOWN)
                move = Movement::DOWN;
            else if (input == graphicals::UP)
                move = Movement::UP;
            break;
        case Movement::RIGHT:
            if (input == graphicals::UP)
                move = Movement::UP;
            else if (input == graphicals::DOWN)
                move = Movement::DOWN;
            break;
    }
}

std::pair<int, int> games::Nibbler::findHead(const std::vector<std::vector<int>> map)
{
    int x = 0;
    int y = 0;

    for (std::vector<int> assetLine : map) {
        for (int asset : assetLine) {
            if (asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADUP
                || asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADDOWN
                || asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADLEFT
                || asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADRIGHT)
                return (std::make_pair(x, y));
            x++;
        }
        y++;
        x = 0;
    }
    return (std::make_pair(0, 0));
}

std::pair<int, int> games::Nibbler::findTail(const std::vector<std::vector<int>> map)
{
    int x = 0;
    int y = 0;

    for (std::vector<int> assetLine : map) {
        for (int asset : assetLine) {
            if (asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILUP
                || asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILDOWN
                || asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILLEFT
                || asset == utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILRIGHT)
                return (std::make_pair(x, y));
            x++;
        }
        y++;
        x = 0;
    }
    return (std::make_pair(0, 0));
}

void games::Nibbler::moveHead(std::pair<int, int> actualPos)
{
    int pos;

    switch (move) {
        case Movement::UP:
            pos = this->_map.getAssetInMap(actualPos.first, actualPos.second - 1);
            if (pos == utilitaries::NIBBLERS_ASSETS_E::APPLE)
                this->AppleEat = true;
            else if (pos != utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER)
                this->collision = true;
            this->_map.setAssetInMap(actualPos.first, actualPos.second - 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADUP);
            break;
        case Movement::DOWN:
        pos = this->_map.getAssetInMap(actualPos.first, actualPos.second + 1);
            if (pos == utilitaries::NIBBLERS_ASSETS_E::APPLE)
                this->AppleEat = true;
            else if (pos != utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER)
                this->collision = true;
            this->_map.setAssetInMap(actualPos.first, actualPos.second + 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADDOWN);
            break;
        case Movement::LEFT:
            pos = this->_map.getAssetInMap(actualPos.first - 1, actualPos.second);
            if (pos == utilitaries::NIBBLERS_ASSETS_E::APPLE)
                this->AppleEat = true;
            else if (pos != utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER)
                this->collision = true;
            this->_map.setAssetInMap(actualPos.first - 1, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADLEFT);
            break;
        case Movement::RIGHT:
            pos = this->_map.getAssetInMap(actualPos.first + 1, actualPos.second);
            if (pos == utilitaries::NIBBLERS_ASSETS_E::APPLE)
                this->AppleEat = true;
            else if (pos != utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER)
                this->collision = true;
            this->_map.setAssetInMap(actualPos.first + 1, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERHEADRIGHT);
            break;
        default:
            break;
    }
}

void games::Nibbler::moveBodyAfterHead(std::pair<int, int> actualPos)
{
    switch (this->move) {
        case Movement::UP:
            switch (this->oldMove) {
                case Movement::UP:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYVERTICAL);
                    break;
                case Movement::LEFT:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN2);
                    break;
                case Movement::RIGHT:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN4);
                    break;
                default:
                    break;
            }
            break;
        case Movement::DOWN:
            switch (this->oldMove) {
                case Movement::DOWN:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYVERTICAL);
                    break;
                case Movement::LEFT:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN1);
                    break;
                case Movement::RIGHT:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN3);
                    break;
                default:
                    break;
            }
            break;
        case Movement::LEFT:
            switch (this->oldMove) {
                case Movement::LEFT:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYHORIZONTAL);
                    break;
                case Movement::UP:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN3);
                    break;
                case Movement::DOWN:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN4);
                    break;
                default:
                    break;
            }
            break;
        case Movement::RIGHT:
            switch (this->oldMove) {
                case Movement::RIGHT:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYHORIZONTAL);
                    break;
                case Movement::UP:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN1);
                    break;
                case Movement::DOWN:
                    this->_map.setAssetInMap(actualPos.first, actualPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN2);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void games::Nibbler::moveTail(std::pair<int, int> tailPos)
{
    int tail = this->_map.getAssetInMap(tailPos.first, tailPos.second);
    int nextTailAsset;

    switch (tail) {
        case utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILUP:
            nextTailAsset = this->_map.getAssetInMap(tailPos.first, tailPos.second - 1);
            switch (nextTailAsset) {
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYVERTICAL:
                    this->_map.setAssetInMap(tailPos.first, tailPos.second - 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILUP);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN3:
                    this->_map.setAssetInMap(tailPos.first, tailPos.second - 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILLEFT);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN1:
                    this->_map.setAssetInMap(tailPos.first, tailPos.second - 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILRIGHT);
                    break;
                default:
                    break;
            }
            break;
        case utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILDOWN:
            nextTailAsset = this->_map.getAssetInMap(tailPos.first, tailPos.second + 1);
            switch (nextTailAsset) {
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYVERTICAL:
                    this->_map.setAssetInMap(tailPos.first, tailPos.second + 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILDOWN);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN4:
                    this->_map.setAssetInMap(tailPos.first, tailPos.second + 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILLEFT);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN2:
                    this->_map.setAssetInMap(tailPos.first, tailPos.second + 1, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILRIGHT);
                    break;
                default:
                    break;
            }
            break;
        case utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILLEFT:
            nextTailAsset = this->_map.getAssetInMap(tailPos.first - 1, tailPos.second);
            switch (nextTailAsset) {
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYHORIZONTAL:
                    this->_map.setAssetInMap(tailPos.first - 1, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILLEFT);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN2:
                    this->_map.setAssetInMap(tailPos.first - 1, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILUP);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN1:
                    this->_map.setAssetInMap(tailPos.first - 1, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILDOWN);
                    break;
                default:
                    break;
            }
            break;
        case utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILRIGHT:
            nextTailAsset = this->_map.getAssetInMap(tailPos.first + 1, tailPos.second);
            switch (nextTailAsset) {
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYHORIZONTAL:
                    this->_map.setAssetInMap(tailPos.first + 1, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILRIGHT);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN4:
                    this->_map.setAssetInMap(tailPos.first + 1, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILUP);
                    break;
                case utilitaries::NIBBLERS_ASSETS_E::NIBBLERBODYTURN3:
                    this->_map.setAssetInMap(tailPos.first + 1, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::NIBBLERTAILDOWN);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    this->_map.setAssetInMap(tailPos.first, tailPos.second, utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER);
}

std::vector<std::pair<int, int>> games::Nibbler::getAllPossiblePosition(const std::vector<std::vector<int>> map)
{
    std::vector<std::pair<int, int>> possiblePosition;
    int x = 0;
    int y = 0;

    for (std::vector<int> assetLine : map) {
        for (int asset : assetLine) {
            if (asset == static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::BLANK_NIBBLER))
                possiblePosition.push_back(std::make_pair(x, y));
            x++;
        }
        y++;
        x = 0;
    }
    return possiblePosition;
}

void games::Nibbler::spawnApple(const std::vector<std::vector<int>> map)
{
    std::vector<std::pair<int, int>> possiblePosition = this->getAllPossiblePosition(map);
    int random = rand() % possiblePosition.size();

    if (possiblePosition.size() != 0)
        this->_map.setAssetInMap(possiblePosition[random].first, possiblePosition[random].second, static_cast<int>(utilitaries::NIBBLERS_ASSETS_E::APPLE));
    else
        this->win = true;
}

void games::Nibbler::moveSnake(std::pair<int, int> actualPos)
{
    const std::vector<std::vector<int>> map = this->_map.getMap();
    std::pair<int, int> tailPos = this->findTail(map);


    if (this->AppleEat) {
        this->AppleEat = false;
    } else
        this->moveTail(tailPos);
    if (!this->win) {
        this->moveHead(actualPos);
        this->moveBodyAfterHead(actualPos);
    }
}

void games::Nibbler::reset()
{
    this->_map.setMap(this->_startMap.getMap());
    this->move = Movement::LEFT;
    this->oldMove = this->move;
    this->start = true;
    this->collision = false;
    this->win = false;
    this->_map.setSleep(500000);
    this->AppleEat = false;
    srand (time(NULL));
}

const utilitaries::GameMap &games::Nibbler::nextCycle(graphicals::Input input)
{
    if (this->start == true) {
        this->start = false;
        return this->_map;
    }
    this->checkInput(input);
    std::pair<int, int> headPos = this->findHead(this->_map.getMap());
    if (!this->win) {
        this->moveSnake(headPos);
    }
    if (this->AppleEat) {
        this->_map.setScore(this->_map.getScore() + 10);
        if (this->_map.getSleep() > 100000)
            this->_map.reduceSleep(25000);
        this->spawnApple(this->_map.getMap());
    }
    if (this->collision) {
        this->reset();
    }
    return this->_map;
}

extern "C" std::unique_ptr<games::IGameModule>loadLib() {
    return std::make_unique<games::Nibbler>();
}

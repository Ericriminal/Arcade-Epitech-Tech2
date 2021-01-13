/*
** EPITECH PROJECT, 2020
** IGames
** File description:
** Game Module Interface
*/

#ifndef _NIBBLERASSETS_
#define _NIBBLERASSETS_

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include <curses.h>

namespace graphicals
{
    enum Input {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ESCAPE,
        SPACE,
        NEXTLIB,
        PREVLIB,
        NEXTGAME,
        PREVGAME,
        RESET,
        MENU,
        SPEED
    };
}

namespace utilitaries {
    enum NIBBLERS_ASSETS_E {
        NIBBLERHEADUP,
        NIBBLERHEADDOWN,
        NIBBLERHEADLEFT,
        NIBBLERHEADRIGHT,
        NIBBLERBODYHORIZONTAL,
        NIBBLERBODYVERTICAL,
        NIBBLERTAILUP,
        NIBBLERTAILDOWN,
        NIBBLERTAILLEFT,
        NIBBLERTAILRIGHT,
        NIBBLERBODYTURN1,
        NIBBLERBODYTURN2,
        NIBBLERBODYTURN3,
        NIBBLERBODYTURN4,
        WALL_NIBBLER,
        BLANK_NIBBLER,
        APPLE
    };

    enum SOLAR_FOX_ASSETS_E {
        SPACESHIPUP,
        SPACESHIPDOWN,
        SPACESHIPLEFT,
        SPACESHIPRIGHT,
        ENEMYLASERHORIZONTAL,
        ENEMYLASERVERTICAL,
        PLAYERLASERHORIZONTAL,
        PLAYERLASERVERTICAL,
        POWERDEAD,
        COIN,
        WALL_SOLARFOX,
        BLANK_SOLARFOX,
        WALLLASERHORIZONTAL,
        WALLLASERVERTICAL,
        COINLASERHORIZONTAL,
        COINLASERVERTICAL
    };

    class GameMap {
    public:
        GameMap();
        ~GameMap() = default;

        std::vector<std::vector<int>> getMap() const;
        void setMap(std::vector<std::vector<int>> _map);
        void setAssetInMap(int x, int y, int asset);
        int getAssetInMap(int x, int y);
        void setSleep(int sleepTime);
        int getSleep(void) const;
        void reduceSleep(int sleep);
        void setScore(int new_score);
        int getScore(void) const;

    private:
        int sleepTime;
        int score;
        std::vector<std::vector<int>> _map;
    };
}

#endif /* _NIBBLERASSETS_ */

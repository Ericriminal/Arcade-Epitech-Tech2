/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#include <chrono>
#include <thread>
#include "Ncurses.hpp"

graphicals::NCurses::NCurses()
{
    window = initscr();
    timeout(1);
    cbreak();
    noecho();
    curs_set(0);
    keypad(window, true);
}

graphicals::NCurses::~NCurses()
{
    endwin();
}

void graphicals::NCurses::newGame(std::string newGame)
{
    if (newGame == "./games/lib_arcade_nibbler.so")
        assetsList = "^v<>-|||--++++0 a";
    else if (newGame == "./games/lib_arcade_solarfox.so")
        assetsList = "^v<>-|-|xa0 -|-|";
}

graphicals::Input graphicals::NCurses::getInput()
{
    int key = getch();

    switch (key) {
    case KEY_DOWN:
        return graphicals::DOWN;
    case KEY_UP:
        return graphicals::UP;
    case KEY_LEFT:
        return graphicals::LEFT;
    case KEY_RIGHT:
        return graphicals::RIGHT;
    case 27:
        return graphicals::ESCAPE;
    case 'i':
        return graphicals::PREVLIB;
    case 'o':
        return graphicals::NEXTLIB;
    case 'k':
        return graphicals::PREVGAME;
    case 'l':
        return graphicals::NEXTGAME;
    case 'r':
        return graphicals::RESET;
    case 'm':
        return graphicals::MENU;
    case ' ':
        return graphicals::SPACE;
    case 's':
        return graphicals::SPEED;
    }
    return graphicals::NONE;
}

void graphicals::NCurses::printChar(std::string tmp, int x, int y)
{
    mvprintw(x, y, tmp.c_str());
}

void graphicals::NCurses::drawMap(const utilitaries::GameMap &map)
{
    std::vector<std::vector<int>> _map = map.getMap();
    std::string tmp;
    int x = 12;
    int y = 5;

    refresh();
    clear();
    mvprintw(2, y, "Previous lib   I");
    mvprintw(3, y, "Next lib       O");
    mvprintw(4, y, "Previous game  K");
    mvprintw(5, y, "Next game      L");
    mvprintw(6, y, "Reset          R");
    mvprintw(7, y, "Back to menu   M");
    mvprintw(8, y, "Quit           ESC");

    mvprintw(10, y, "Score :");
    mvprintw(10, y + 7, std::to_string(map.getScore()).c_str());
    for (std::vector<int> lines : _map) {
        for (int c : lines)
            tmp.push_back(assetsList[c]);
        printChar(tmp, x, y);
        x += 1;
        tmp.clear();
    }
    refresh();
    std::this_thread::sleep_for(std::chrono::microseconds(map.getSleep()));
}

extern "C" std::unique_ptr<graphicals::IGraphicalModule> loadLib() {
    return std::make_unique<graphicals::NCurses>();
}

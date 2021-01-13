/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#include "Core.hpp"
#include <unistd.h>
#include <iostream>
#include <exception>

Core::Core()
{
    findLibraries();
    findGames();
    libHndl = nullptr;
    libHndl = nullptr;
    score = -1;
}

Core::~Core()
{
    lib.reset();
    game.reset();
    dlclose(libHndl);
    dlclose(gameHndl);
}

void Core::scores()
{
    std::ifstream reader;
    std::string file = "./scores/" + curGame.substr(19, curGame.find_last_of(".") - 19);
    std::vector<std::pair<int, std::string>> pr;
    std::vector<std::string> sc;
    std::vector<int> sco;
    std::string s;

    reader.open(file);
    if (reader.is_open())
        while (std::getline(reader, s)) {
            std::cerr << s.substr(s.find(":") + 2).c_str() << std::endl;
            pr.push_back(make_pair(std::atoi(s.substr(s.find(":") + 2).c_str()),
                                   s.substr(0, s.find(":"))));
        }

    std::ofstream rewrite;
    rewrite.open(file, std::ofstream::out | std::ofstream::trunc);
    pr.push_back(make_pair(score, userName));
    std::sort(pr.begin(), pr.end());
    for (int i = static_cast<int>(pr.size()) - 1;
         i > static_cast<int>(pr.size()) - 11 && i >= 0; i--)
        rewrite << pr[i].second << ": " << pr[i].first << "\n";
}

void Core::loadLibrary(const std::string &libPath)
{
    libHndl = dlopen(libPath.c_str(), RTLD_NOW);
    auto ptr = reinterpret_cast<std::unique_ptr<graphicals::IGraphicalModule>(*)()>(dlsym(libHndl, "loadLib"));

    if (!libHndl) {
        dlerror();
        std::cout << libPath.c_str() << std::endl;
        std::cout << "FAILURE LIB" << std::endl;
        throw;
    }
    if (!ptr) {
        std::cout << "FAILURE CAST/SYMBOL" << std::endl;
        throw;
    }
    lib = ptr();
}

void Core::loadGame(const std::string &gamePath)
{
    gameHndl = dlopen(gamePath.c_str(), RTLD_NOW);
    auto ptr = reinterpret_cast<std::unique_ptr<games::IGameModule>(*)()>(dlsym(gameHndl, "loadLib"));

    if (!gameHndl) {
        dlerror();
        std::cout << gamePath.c_str() << std::endl;
        std::cout << "FAILURE LIB" << std::endl;
        throw;
    }
    if (!ptr) {
        std::cout << "FAILURE CAST/SYMBOL" << std::endl;
        throw;
    }
    game = ptr();
}

void Core::findLibraries()
{
    for (const auto &file : std::experimental::filesystem::directory_iterator("./lib/"))
    {
        std::string tmp = file.path().filename().string();
        int dot = tmp.find_last_of(".");
        int totlen = tmp.length() - dot;
        if (tmp.substr(0, 11) == "lib_arcade_" && tmp.substr(dot, totlen) == ".so")
            libs.push_back("./lib/" + tmp);
    }
}

void Core::findGames()
{
    for (const auto &file : std::experimental::filesystem::directory_iterator("./games/"))
    {
        std::string tmp = file.path().filename().string();
        int dot = tmp.find_last_of(".");
        int totlen = tmp.length() - dot;
        if (tmp.substr(0, 11) == "lib_arcade_" && tmp.substr(dot, totlen) == ".so")
            games.push_back("./games/" + tmp);
    }
}

unsigned int Core::whatPlay(bool err)
{
    std::string reader;
    unsigned int num;

    if (err == false)
        std::cout << "What do you want to play today?" << std::endl;
    else
        std::cout << "Please type well your choice" << std::endl;
    for (unsigned int i = 0; i < games.size(); i++) {
        std::cout << "Type " << i + 1 << " in order to play ";
        std::cout << games[i].substr(19, games[i].find_last_of(".") - 19) << std::endl;
    }
    std::cout << "Type " << games.size() + 1 << " in order to exit" << std::endl;
    std::cout << ">";
    std::getline(std::cin, reader);

    if (reader == "")
        return (whatPlay(true));
    try
    {
        num = std::stoi(reader);
        if (num > games.size() + 1)
            throw std::exception();
        if (num == games.size() + 1)
        {
            std::cout << "Goodbye sir." << std::endl;
            exit(0);
        }
    }
    catch (const std::exception &) {
        return (whatPlay(true));
    }
    return (num);
}

void Core::menu(const std::string &name, const std::string &libName)
{
    unsigned int num;

    if (name != "null") {
        userName = name;
        std::cout << "Greetings sir " << userName << "." << std::endl;
    } else
        std::cout << "Welcome back sir " << userName << std::endl;

    num = whatPlay(false);
    run(libName, games[num - 1]);
}

void Core::setGame(const std::string &gameName)
{
    static unsigned int i = 0;

    if (gameName == "next") {
        (i == games.size()-1) ? i = 0 : ++i;
    } else if (gameName == "previous") {
        (i == 0) ? i = games.size() - 1 : --i;
    } else if (gameName == "reset") {
    } else {
        for (; games[i] != gameName; i++);
        if (i == games.size())
            throw;
    }
    game.reset();
    loadGame(games[i]);
    curGame = games[i];
    if (lib)
        lib->newGame(curGame);
}

void Core::setLib(const std::string &libName)
{
    static unsigned int i = 0;

    if (libName == "next") {
        (i == libs.size()-1) ? i = 0 : ++i;
    } else if (libName == "previous") {
        (i == 0) ? i = libs.size() - 1 : --i;
    } else {
        for (; libs[i] != libName && i < libs.size(); i++);
        if (i == libs.size())
            exit(84);
    }
    lib.reset();
    loadLibrary(libs[i]);
    curLib = libs[i];
    lib->newGame(curGame);
}

void Core::checkLib(const std::string &libName)
{
    unsigned int i = 0;

    for (; libs[i] != libName && i < libs.size(); i++);
    if (i == libs.size())
        exit(84);
}

void Core::run(const std::string &libName, const std::string &gameName)
{
    graphicals::Input input;
    utilitaries::GameMap tmp;

    setGame(gameName);
    setLib(libName);
    while (1)
    {
        input = lib->getInput();
        if (input == graphicals::NEXTLIB)
            setLib("next");
        if (input == graphicals::PREVLIB)
            setLib("previous");
        if (input == graphicals::NEXTGAME)
            setGame("next");
        if (input == graphicals::PREVGAME)
            setGame("previous");
        if (input == graphicals::RESET)
            setGame("reset");
        if (input == graphicals::MENU) {
            score = tmp.getScore();
            scores();
            lib.reset();
            game.reset();
            menu("null", curLib);
            exit(0);
        }
        if (input == graphicals::ESCAPE)
            break;
        tmp = game->nextCycle(input);
        lib->drawMap(tmp);
    }
    score = tmp.getScore();
    scores();
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    Core pp;
    std::string name;

    pp.checkLib(av[1]);
    std::cout << "What would this gentleman's name be?" << std::endl;
    std::getline(std::cin, name);
    pp.menu(name, av[1]);
}

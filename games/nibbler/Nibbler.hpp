/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "AGamesModule.hpp"

namespace games {
    class Nibbler : public AGameModule {
        public:
            Nibbler();
            ~Nibbler();
            const utilitaries::GameMap &nextCycle(graphicals::Input input) override;
            enum Movement{UP, DOWN, LEFT, RIGHT};
        protected:
        private:
            void reset();
            void checkInput(graphicals::Input input);
            void checkAppleEat(const std::vector<std::vector<int>> map);
            void moveSnake(std::pair<int, int> actualPos);
            void moveTail(std::pair<int, int> tailPos);
            void moveBodyAfterHead(std::pair<int, int> actualPos);
            void moveHead(std::pair<int, int> actualPos);
            void spawnApple(const std::vector<std::vector<int>> map);
            std::vector<std::vector<int>> createMap();
            std::vector<std::pair<int, int>> getAllPossiblePosition(const std::vector<std::vector<int>> map);
            std::pair<int, int> findTail(const std::vector<std::vector<int>> map);
            std::pair<int, int> findHead(const std::vector<std::vector<int>> map);
            Movement move;
            Movement oldMove;
            bool start;
            bool AppleEat;
            bool collision;
            bool win;
            int sleepTime;
    };
}

#endif /* !NIBBLER_HPP_ */

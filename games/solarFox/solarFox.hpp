/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** solarFox
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "AGamesModule.hpp"

namespace games {
    class solarFox : public AGameModule {
        public:
            solarFox();
            ~solarFox();
            const utilitaries::GameMap &nextCycle(graphicals::Input input) override;
            enum Movement{UP, DOWN, LEFT, RIGHT};
        protected:
        private:
            void checkPlayerInput(graphicals::Input input);
            std::vector<std::vector<int>> createMap();
            Movement move;
            Movement oldMove;
            Movement playerLaserMove;
            bool start;
            bool win;
            bool alive;
            std::vector<std::pair<int, int>> enemiesPos; // a gauche haut en bas, en haut gauche a droite, a droite bas en haut, en bas, droite a gauche
            std::vector<int> replaceObject;
            std::vector<int> laserEnemies;
            std::vector<bool> enemyLaserLaunched;
            std::vector<bool> firstEnemyLaserWall;
            std::vector<std::pair<int, int>> enemiesLaserPos;
            std::vector<Movement> enemiesMovement;
            std::vector<Movement> enemiesLaserMovement;
            std::pair<int, int> playerPos;
            bool playerLaserLaunched;
            int replaceObjectPlayerLaser;
            int gameSpeed;
            int playerSpeed;
            int playerBaseSpeed;
            int enemySpeed;
            int enemyLaserSpeed;
            int playerLaserGraphical;
            int playerLaserLife;
            void checkCollisionPlayer();
            void doMovement();
            void playerMovement();
            void checkCollisionEnemy(int enemy);
            void doEnemyMovement();
            void checkEnemiesMovement();
            void checkCollisionLaserEnemy(int enemy);
            void doEnemyLaserMovement();
            void moveEnemiesLaser();
            void checkCollisionPlayerLaser(std::pair<int, int> laserPos);
            void movePlayerLaser();
            void setLaserEnemySpawn(int enemy);
            void checkWin();
            std::pair<int, int>getLaserPosition();
            int getLaserEnemy(std::pair<int, int> laserPos);
            void resetEnemyLaserSprite(int enemy);
            void restart();
    };
}

#endif /* !NIBBLER_HPP_ */

/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** solarFox
*/

#include <utility>
#include "solarFox.hpp"

games::solarFox::solarFox()
{
    std::vector<std::vector<int>> map = this->createMap();
    this->move = Movement::RIGHT;
    this->oldMove = this->move;
    this->start = true;
    this->win = false;
    this->alive = true;
    this->playerLaserLaunched = false;
    this->_map.setMap(map);
    this->_startMap.setMap(map);
    this->playerPos = std::make_pair(7, 9);
    this->replaceObject = {utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX};
    this->enemiesPos = {std::make_pair(12, 0), std::make_pair(12, 14), std::make_pair(19, 7), std::make_pair(0, 7)};
    this->enemyLaserLaunched = {false, false, false, false};
    this->firstEnemyLaserWall = {false, false, false, false};
    this->laserEnemies = {utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL, utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL,
        utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL, utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL};
    this->enemiesMovement = {Movement::LEFT, Movement::RIGHT, Movement::UP, Movement::DOWN};
    this->enemiesLaserMovement = {Movement::DOWN, Movement::UP, Movement::LEFT, Movement::RIGHT};
    this->enemiesLaserPos = {std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0)};
    this->gameSpeed = 2;
    this->playerSpeed = 0;
    this->playerBaseSpeed = 0;
    this->enemySpeed = 0;
    this->enemyLaserSpeed = 0;
    this->playerLaserGraphical = 0;
    this->playerLaserLife = 3;
    this->_map.setSleep(200000);
    this->_startMap.setSleep(200000);
    srand (time(NULL));
}

games::solarFox::~solarFox()
{
}

std::vector<std::vector<int>> games::solarFox::createMap()
{
    std::vector<std::vector<int>> map;
    int wall = static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX);
    int blank = static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
    int coin = static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::COIN);

    std::vector<int> topBorderLine = {wall, blank, blank, blank, blank, blank, blank,
        blank, blank, blank, blank, blank,
        static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPDOWN),
        blank, blank, blank, blank, blank, blank, wall};
    std::vector<int> botBorderLine = {wall, blank, blank, blank, blank, blank, blank,
        blank, blank, blank, blank, blank,
        static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPUP),
        blank, blank, blank, blank, blank, blank, wall};
    std::vector<int> emptyLine = {blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
        blank, blank, blank, blank, blank, blank, blank, blank, blank, blank};
    std::vector<int> wallLine = {blank, blank, blank, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, blank, blank, blank};
    std::vector<int> enemyLine = {static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPRIGHT),
        blank, blank, wall, blank, blank, blank, blank, blank,
        blank, blank, blank, blank, blank, blank, blank, wall, blank, blank,
        static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPLEFT)};
    std::vector<int> normalLine = {blank, blank, blank, wall, blank, blank, blank, blank, blank,
        blank, blank, blank, blank, blank, blank, blank, wall, blank, blank, blank};
    std::vector<int> deadLine = {blank, blank, blank, wall, blank, blank, blank, static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::POWERDEAD),
        blank, blank, blank, blank, blank, blank, blank, blank, wall, blank, blank, blank};
    std::vector<int> coinLine = {blank, blank, blank, wall, blank, coin, blank, coin, blank,
        coin, blank, coin, blank, coin, blank, blank, wall, blank, blank, blank};
    std::vector<int> playerLine = {blank, blank, blank, wall, blank, blank, blank,
        static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPRIGHT),
        blank, blank, blank, blank, blank, blank, blank, blank, wall, blank, blank, blank};
    map.push_back(topBorderLine);
    map.push_back(emptyLine);
    map.push_back(wallLine);
    map.push_back(deadLine);
    map.push_back(coinLine);
    map.push_back(normalLine);
    map.push_back(coinLine);
    map.push_back(enemyLine);
    map.push_back(coinLine);
    map.push_back(playerLine);
    map.push_back(coinLine);
    map.push_back(deadLine);
    map.push_back(wallLine);
    map.push_back(emptyLine);
    map.push_back(botBorderLine);
    return map;
}

void games::solarFox::checkPlayerInput(graphicals::Input input)
{
    this->playerBaseSpeed = 0;
    switch (this->oldMove) {
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
    if (input == graphicals::SPACE && this->playerLaserLaunched == false) {
        this->playerLaserLaunched = true;
        this->playerLaserMove = this->move;
        this->replaceObjectPlayerLaser = this->_map.getAssetInMap(this->playerPos.first, this->playerPos.second);
        if (this->playerLaserMove == Movement::LEFT || this->playerLaserMove == Movement::RIGHT)
            this->playerLaserGraphical = utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERHORIZONTAL;
        else
            this->playerLaserGraphical = utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERVERTICAL;
        this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, this->playerLaserGraphical);
        this->movePlayerLaser();
    }
    if (input == graphicals::SPEED) {
        this->playerSpeed = 2;
        this->playerBaseSpeed = 1;
    }
}

void games::solarFox::checkCollisionPlayer()
{
    int asset = this->_map.getAssetInMap(this->playerPos.first, this->playerPos.second);

    if (asset == utilitaries::SOLAR_FOX_ASSETS_E::COIN) {
        this->_map.setScore(this->_map.getScore() + 10);
    } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::POWERDEAD) {
        this->alive = false;
    } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX) {
        this->alive = false;
    } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL) {
        this->alive = false;
    } else if (asset == utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL) {
        this->alive = false;
    }
}

void games::solarFox::doMovement()
{
    switch (this->move) {
        case Movement::UP:
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
            this->playerPos.second--;
            this->checkCollisionPlayer();
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPUP);
            break;
        case Movement::DOWN:
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
            this->playerPos.second++;
            this->checkCollisionPlayer();
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPDOWN);
            break;
        case Movement::LEFT:
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
            this->playerPos.first--;
            this->checkCollisionPlayer();
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPLEFT);
            break;
        case Movement::RIGHT:
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
            this->playerPos.first++;
            this->checkCollisionPlayer();
            this->_map.setAssetInMap(this->playerPos.first, this->playerPos.second, utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPRIGHT);
            break;
    }
}

void games::solarFox::playerMovement()
{
    this->playerSpeed++;
    if (this->gameSpeed <= this->playerSpeed) {
        this->oldMove = this->move;
        this->doMovement();
        this->playerSpeed = this->playerBaseSpeed;
    }
}

void games::solarFox::checkCollisionEnemy(int enemy)
{
    int asset = this->_map.getAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second);

    if (asset == utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX) {
        switch (enemy) {
            case 0 :
                if (this->enemiesMovement[enemy] == Movement::LEFT) {
                    this->enemiesPos[enemy].first++;
                    this->enemiesMovement[enemy] = Movement::RIGHT;
                } else {
                    this->enemiesPos[enemy].first--;
                    this->enemiesMovement[enemy] = Movement::LEFT;
                }
                break;
            case 1 :
                if (this->enemiesMovement[enemy] == Movement::LEFT) {
                    this->enemiesPos[enemy].first++;
                    this->enemiesMovement[enemy] = Movement::RIGHT;
                } else {
                    this->enemiesPos[enemy].first--;
                    this->enemiesMovement[enemy] = Movement::LEFT;
                }
                break;
            case 2 :
                if (this->enemiesMovement[enemy] == Movement::UP) {
                    this->enemiesPos[enemy].second++;
                    this->enemiesMovement[enemy] = Movement::DOWN;
                } else {
                    this->enemiesPos[enemy].second--;
                    this->enemiesMovement[enemy] = Movement::UP;
                }
                break;
            case 3 :
                if (this->enemiesMovement[enemy] == Movement::UP) {
                    this->enemiesPos[enemy].second++;
                    this->enemiesMovement[enemy] = Movement::DOWN;
                } else {
                    this->enemiesPos[enemy].second--;
                    this->enemiesMovement[enemy] = Movement::UP;
                }
                break;
        }
    }
}

void games::solarFox::doEnemyMovement()
{
    int asset = 0;
    for (int enemy = 0; enemy <= 3; enemy++) {
        asset = this->_map.getAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second);

        switch (this->enemiesMovement[enemy]) {
            case Movement::UP:
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
                this->enemiesPos[enemy].second--;
                this->checkCollisionEnemy(enemy);
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, asset);
                break;
            case Movement::DOWN:
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
                this->enemiesPos[enemy].second++;
                this->checkCollisionEnemy(enemy);
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, asset);
                break;
            case Movement::LEFT:
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
                this->enemiesPos[enemy].first--;
                this->checkCollisionEnemy(enemy);
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, asset);
                break;
            case Movement::RIGHT:
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX);
                this->enemiesPos[enemy].first++;
                this->checkCollisionEnemy(enemy);
                this->_map.setAssetInMap(this->enemiesPos[enemy].first, this->enemiesPos[enemy].second, asset);
                break;
        }
    }
}

void games::solarFox::checkEnemiesMovement()
{
    this->enemySpeed++;
    if (this->gameSpeed <= this->enemySpeed) {
        this->doEnemyMovement();
        this->enemySpeed = 0;
    }
}

void games::solarFox::checkCollisionLaserEnemy(int enemy)
{
    int asset = this->_map.getAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second);

    switch (asset) {
        case utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX :
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::COIN :
            if (enemy <= 1)
                this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::COINLASERVERTICAL;
            else
                this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::COINLASERHORIZONTAL;
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::COIN;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::POWERDEAD :
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::POWERDEAD;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX :
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX;
            if (this->firstEnemyLaserWall[enemy] == true) {
                this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
                this->enemyLaserLaunched[enemy] = false;
                this->firstEnemyLaserWall[enemy] = false;
            } else {
                if (enemy <= 1)
                    this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::WALLLASERVERTICAL;
                else
                    this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::WALLLASERHORIZONTAL;
                this->firstEnemyLaserWall[enemy] = true;
            }
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPUP :
            this->alive = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPDOWN :
            this->alive = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPLEFT :
            this->alive = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::SPACESHIPRIGHT :
            this->alive = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERHORIZONTAL :
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERHORIZONTAL;
            this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
            this->enemyLaserLaunched[enemy] = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERVERTICAL :
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERVERTICAL;
            this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
            this->enemyLaserLaunched[enemy] = false;
            break;
        default :
            this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX;
            break;
    }
}

void games::solarFox::setLaserEnemySpawn(int enemy)
{
    this->enemiesLaserPos[enemy] = this->enemiesPos[enemy];
    this->firstEnemyLaserWall[enemy] = false;
    this->replaceObject[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX;
    switch (enemy) {
        case 0 :
            this->enemiesLaserPos[enemy].second += 1;
            break;
        case 1 :
            this->enemiesLaserPos[enemy].second -= 1;
            break;
        case 2 :
            this->enemiesLaserPos[enemy].first -= 1;
            break;
        case 3 :
            this->enemiesLaserPos[enemy].first += 1;
            break;
    }
    this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->laserEnemies[enemy]);
}

void games::solarFox::resetEnemyLaserSprite(int enemy)
{
    switch (enemy) {
        case 0 :
            this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL;
            break;
        case 1 :
            this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL;
            break;
        case 2 :
            this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL;
            break;
        case 3 :
            this->laserEnemies[enemy] = utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL;
            break;
    }
}

void games::solarFox::doEnemyLaserMovement()
{
    for (int enemy = 0; enemy <= 3; enemy++) {
        this->resetEnemyLaserSprite(enemy);
        if (this->enemyLaserLaunched[enemy]) {
            switch (this->enemiesLaserMovement[enemy]) {
                case Movement::UP:
                    this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
                    this->enemiesLaserPos[enemy].second--;
                    this->checkCollisionLaserEnemy(enemy);
                    if (this->enemyLaserLaunched[enemy])
                        this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->laserEnemies[enemy]);
                    break;
                case Movement::DOWN:
                    this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
                    this->enemiesLaserPos[enemy].second++;
                    this->checkCollisionLaserEnemy(enemy);
                    if (this->enemyLaserLaunched[enemy])
                        this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->laserEnemies[enemy]);
                    break;
                case Movement::LEFT:
                    this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
                    this->enemiesLaserPos[enemy].first--;
                    this->checkCollisionLaserEnemy(enemy);
                    if (this->enemyLaserLaunched[enemy])
                        this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->laserEnemies[enemy]);
                    break;
                case Movement::RIGHT:
                    this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->replaceObject[enemy]);
                    this->enemiesLaserPos[enemy].first++;
                    this->checkCollisionLaserEnemy(enemy);
                    if (this->enemyLaserLaunched[enemy])
                        this->_map.setAssetInMap(this->enemiesLaserPos[enemy].first, this->enemiesLaserPos[enemy].second, this->laserEnemies[enemy]);
                    break;
            }
        } else {
            if (rand() % 2 == 0 && ((enemy == 0 && this->enemiesPos[enemy].first > 3 && this->enemiesPos[enemy].first < 16)
                || (enemy == 1 && this->enemiesPos[enemy].first > 3 && this->enemiesPos[enemy].first < 16)
                || (enemy == 2 && this->enemiesPos[enemy].second > 2 && this->enemiesPos[enemy].second < 12)
                || (enemy == 3 && this->enemiesPos[enemy].second > 2 && this->enemiesPos[enemy].second < 12))) {
                this->enemyLaserLaunched[enemy] = true;
                this->setLaserEnemySpawn(enemy);
            }
        }
    }
}

void games::solarFox::moveEnemiesLaser()
{
    this->enemyLaserSpeed++;
    if (this->gameSpeed <= this->enemyLaserSpeed) {
        this->doEnemyLaserMovement();
        this->enemyLaserSpeed = 0;
    }
}

int games::solarFox::getLaserEnemy(std::pair<int, int> laserPos)
{
    for (int enemy = 0; enemy <= 3; enemy++) {
        if (this->enemiesLaserPos[enemy] == laserPos)
            return enemy;
    }
    return -1;
}

void games::solarFox::checkCollisionPlayerLaser(std::pair<int, int> laserPos)
{
    int asset = this->_map.getAssetInMap(laserPos.first, laserPos.second);

    switch (asset) {
        case utilitaries::SOLAR_FOX_ASSETS_E::COIN :
            this->_map.setScore(this->_map.getScore() + 10);
            this->replaceObjectPlayerLaser = utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::POWERDEAD :
            this->replaceObjectPlayerLaser = utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::WALL_SOLARFOX :
            this->playerLaserLaunched = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERHORIZONTAL :
            this->enemyLaserLaunched[this->getLaserEnemy(laserPos)] = false;
            break;
        case utilitaries::SOLAR_FOX_ASSETS_E::ENEMYLASERVERTICAL :
            this->enemyLaserLaunched[this->getLaserEnemy(laserPos)] = false;
            break;
        default :
            this->replaceObjectPlayerLaser = utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX;
            break;
    }
}

std::pair<int, int> games::solarFox::getLaserPosition()
{
    int x = 0;
    int y = 0;

    for (std::vector<int> assetLine : this->_map.getMap()) {
        for (int asset : assetLine) {
            if (asset == static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERHORIZONTAL)
                || asset == static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERVERTICAL))
                return std::make_pair(x, y);
            x++;
        }
        y++;
        x = 0;
    }
    return std::make_pair(-1, -1);
}

void games::solarFox::movePlayerLaser()
{
    if (this->playerLaserLaunched && this->playerLaserLife > 0) {
        std::pair<int, int> laserPos = this->getLaserPosition();
        switch (this->playerLaserMove) {
            case Movement::UP:
                this->_map.setAssetInMap(laserPos.first, laserPos.second, this->replaceObjectPlayerLaser);
                laserPos.second--;
                this->checkCollisionPlayerLaser(laserPos);
                if (this->playerLaserLaunched)
                    this->_map.setAssetInMap(laserPos.first, laserPos.second, utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERVERTICAL);
                break;
            case Movement::DOWN:
                this->_map.setAssetInMap(laserPos.first, laserPos.second, this->replaceObjectPlayerLaser);
                laserPos.second++;
                this->checkCollisionPlayerLaser(laserPos);
                if (this->playerLaserLaunched)
                    this->_map.setAssetInMap(laserPos.first, laserPos.second, utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERVERTICAL);
                break;
            case Movement::LEFT:
                this->_map.setAssetInMap(laserPos.first, laserPos.second, this->replaceObjectPlayerLaser);
                laserPos.first--;
                this->checkCollisionPlayerLaser(laserPos);
                if (this->playerLaserLaunched)
                    this->_map.setAssetInMap(laserPos.first, laserPos.second, utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERHORIZONTAL);
                break;
            case Movement::RIGHT:
                this->_map.setAssetInMap(laserPos.first, laserPos.second, this->replaceObjectPlayerLaser);
                laserPos.first++;
                this->checkCollisionPlayerLaser(laserPos);
                if (this->playerLaserLaunched)
                    this->_map.setAssetInMap(laserPos.first, laserPos.second, utilitaries::SOLAR_FOX_ASSETS_E::PLAYERLASERHORIZONTAL);
                break;
        }
        this->playerLaserLife--;
    } else if (this->playerLaserLaunched) {
        std::pair<int, int> laserPos = this->getLaserPosition();
        this->_map.setAssetInMap(laserPos.first, laserPos.second, this->replaceObjectPlayerLaser);
        this->checkCollisionPlayerLaser(laserPos);
        this->playerLaserLife = 3;
        this->playerLaserLaunched = false;
    }
}

void games::solarFox::checkWin()
{
    for (std::vector<int> assetLine : this->_map.getMap()) {
        for (int asset : assetLine) {
            if (asset == static_cast<int>(utilitaries::SOLAR_FOX_ASSETS_E::COIN)) {
                this->win = false;
                return;
            }
        }
    }
    this->win = true;
    return;
}

void games::solarFox::restart()
{
    this->move = Movement::RIGHT;
    this->oldMove = this->move;
    this->start = true;
    this->win = false;
    this->alive = true;
    this->playerLaserLaunched = false;
    this->_map.setMap(this->_startMap.getMap());
    this->playerPos = std::make_pair(7, 9);
    this->replaceObject = {utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX, utilitaries::SOLAR_FOX_ASSETS_E::BLANK_SOLARFOX};
    this->enemiesPos = {std::make_pair(12, 0), std::make_pair(12, 14), std::make_pair(19, 7), std::make_pair(0, 7)};
    this->enemyLaserLaunched = {false, false, false, false};
    this->firstEnemyLaserWall = {false, false, false, false};
    this->enemiesMovement = {Movement::LEFT, Movement::RIGHT, Movement::UP, Movement::DOWN};
    this->enemiesLaserMovement = {Movement::DOWN, Movement::UP, Movement::LEFT, Movement::RIGHT};
    this->enemiesLaserPos = {std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0)};
    this->gameSpeed = 2;
    this->playerSpeed = 0;
    this->playerBaseSpeed = 0;
    this->enemySpeed = 0;
    this->enemyLaserSpeed = 0;
    this->playerLaserLife = 3;
    srand (time(NULL));
}

const utilitaries::GameMap &games::solarFox::nextCycle(graphicals::Input input)
{
    if (this->start == true) {
        this->start = false;
        return this->_map;
    }
    if (this->alive && !this->win) {
        this->checkPlayerInput(input);
        this->checkWin();
        this->movePlayerLaser();
        this->playerMovement();
        this->moveEnemiesLaser();
        this->checkEnemiesMovement();
    }
    if (this->win || !this->alive)
        this->restart();
    return this->_map;
}

extern "C" std::unique_ptr<games::IGameModule>loadLib() {
    return std::make_unique<games::solarFox>();
}

#pragma once
#include "State.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Util.h"

#include <iostream>
#include <vector>
#include <string>

#define SPRITE_SIZE 64

#define CELL_SIZE 64
#define BOMB_COUNT 16

class GameState : public we::State
{
public:
    GameState(we::App* app);

    void Init           ()                          override;
    void HandleInput    (sf::Event& e)              override;
    void Update         (float deltaTime)           override;
    void Draw           (sf::RenderWindow& window)  override;

    void Resume         ()                          override;

private:
    enum class CELL_STATE { CLOSED, OPENED, BOMB };

    struct sCell
    {
        sCell(sf::Vector2f pos)
        {
            state = CELL_STATE::CLOSED;

            sprite.setSize(sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE));
            sprite.setTexture(&ResourceManager::get().getTexture("closed_cell"));
            sprite.scale((float)CELL_SIZE / SPRITE_SIZE, (float)CELL_SIZE / SPRITE_SIZE);

            sprite.setPosition(pos);

            neighbour_count = 0;
            flagged         = false;
        }

        void ChangeTexture(std::string texName, sf::IntRect rect)
        {
            sprite.setTexture(&ResourceManager::get().getTexture(texName));
            sprite.setTextureRect(rect);
        }

        int     neighbour_count;
        bool    flagged;

        sf::RectangleShape  sprite;
        CELL_STATE          state;
    };

    std::vector<sCell>  m_board;
    sf::Vector2i        m_cellCount;

    int convertCoord    (int x, int y);
    int isBomb          (int x, int y);
};

#include "GameState.h"
#include "../Engine/App.h"
#include "GameEnd.h"

GameState::GameState(we::App* app)
    : we::State(app)
{}

void GameState::Init()
{
    // Setup cellCount
    m_cellCount.x = m_app->ScreenWidth () / CELL_SIZE;
    m_cellCount.y = m_app->ScreenHeight() / CELL_SIZE;

    // Create board array
    for (int y = 0; y < m_cellCount.y; y++)
    {
        for (int x = 0; x < m_cellCount.x; x++)
        {
            m_board.push_back(sCell(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE)));
        }
    }

    // Setup random bombs
    int placed_bombs = 0;
    while (placed_bombs != BOMB_COUNT)
    {
        int x = iRandom(0, m_cellCount.x - 1);
        int y = iRandom(0, m_cellCount.y - 1);

        if (m_board.at(convertCoord(x, y)).state == CELL_STATE::CLOSED)
        {
            m_board.at(convertCoord(x, y)).state = CELL_STATE::BOMB;
            //m_board.at(convertCoord(x, y)).ChangeTexture("bomb", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(CELL_SIZE, CELL_SIZE)));
            placed_bombs++;
        }
    }

    // Setup each cell by checking neighbours
    for (int y = 0; y < m_cellCount.y; y++)
    {
        for (int x = 0; x < m_cellCount.x; x++)
        {
            int Neighbours = 0;

            if (x != 0)
                Neighbours += isBomb(x - 1, y);
            if (y != 0)
                Neighbours += isBomb(x, y - 1);
            if (x != (m_cellCount.x) - 1)
                Neighbours += isBomb(x + 1, y);
            if (y != (m_cellCount.y) - 1)
                Neighbours += isBomb(x, y + 1);
            if (x != 0 && y != 0)
                Neighbours += isBomb(x - 1, y - 1);
            if (x != (m_cellCount.x) - 1 && y != (m_cellCount.y) - 1)
                Neighbours += isBomb(x + 1, y + 1);
            if (x != 0 && y != (m_cellCount.y) - 1)
                Neighbours += isBomb(x - 1, y + 1);
            if (x != (m_cellCount.x) - 1 && y != 0)
                Neighbours += isBomb(x + 1, y - 1);

            m_board.at(convertCoord(x, y)).neighbour_count = Neighbours;
        }
    }
}

void GameState::HandleInput(sf::Event& e)
{
    // Get mouse click left or right
    // Left open space
    // Right place flag
    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        int x = sf::Mouse::getPosition(m_app->getWindow()).x / CELL_SIZE;
        int y = sf::Mouse::getPosition(m_app->getWindow()).y / CELL_SIZE;

        if (m_board.at(convertCoord(x, y)).state == CELL_STATE::CLOSED)
        {
            int rectMultiplier = m_board.at(convertCoord(x, y)).neighbour_count;

            m_board.at(convertCoord(x, y)).state = CELL_STATE::OPENED;
            m_board.at(convertCoord(x, y)).ChangeTexture("cells", sf::IntRect(sf::Vector2i(rectMultiplier * SPRITE_SIZE, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
        }
        else if (m_board.at(convertCoord(x, y)).state == CELL_STATE::BOMB) // Check if bomb was clicked
        {
            // if the game has ended show all bombs
            for (auto &i : m_board)
            {
                if (i.state == CELL_STATE::BOMB)
                    i.ChangeTexture("bomb", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
            }

            // Clicked bomb has a red background
            m_board.at(convertCoord(x, y)).ChangeTexture("bomb_red", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));

            // Change state to GameEnd
            m_app->getStateMachine().AddState(std::make_unique<GameEnd>(m_app, false), false);
            m_app->getStateMachine().ProcessStateChanges();
        }
    }
    else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right)
    {
        int x = sf::Mouse::getPosition(m_app->getWindow()).x / CELL_SIZE;
        int y = sf::Mouse::getPosition(m_app->getWindow()).y / CELL_SIZE;

        if (m_board.at(convertCoord(x, y)).state != CELL_STATE::OPENED && !m_board.at(convertCoord(x, y)).flagged)
        {
            m_board.at(convertCoord(x, y)).flagged = true;
            m_board.at(convertCoord(x, y)).ChangeTexture("flag", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
        }
        else if (m_board.at(convertCoord(x, y)).flagged)
        {
            m_board.at(convertCoord(x, y)).flagged = false;
            m_board.at(convertCoord(x, y)).ChangeTexture("closed_cell", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
        }
    }
}

void GameState::Update(float deltaTime)
{
    // Check if all cells have been visited then run GameEnd state
    int Opened  = 0;
    int Flagged = 0;

    for (auto &cell : m_board)
    {
        if (cell.state == CELL_STATE::OPENED)
            Opened++;

        if (cell.flagged == true)
            Flagged++;
    }

    if (Opened == m_board.size() - BOMB_COUNT && Flagged == BOMB_COUNT)
    {
        // Change state to GameEnd
        m_app->getStateMachine().AddState(std::make_unique<GameEnd>(m_app, false), true);
        m_app->getStateMachine().ProcessStateChanges();
    }
}

void GameState::Draw(sf::RenderWindow & window)
{
    // Draw board
    for (auto &i : m_board)
    {
        window.draw(i.sprite);
    }
}

void GameState::Resume()
{
    // if this is called that means a new game should be created
    m_app->getStateMachine().AddState(std::make_unique<GameState>(m_app));
    m_app->getStateMachine().ProcessStateChanges();
}

// Helper methods
int GameState::convertCoord(int x, int y)
{
    return (y * m_cellCount.x) + x;
}

int GameState::isBomb(int x, int y)
{
    if (m_board.at((y * (m_app->ScreenWidth() / CELL_SIZE)) + x).state == CELL_STATE::BOMB)
    {
        return 1;
    }
    else return 0;
}



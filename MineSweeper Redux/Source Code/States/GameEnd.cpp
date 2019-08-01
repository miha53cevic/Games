#include "GameEnd.h"
#include "../Engine/App.h"

GameEnd::GameEnd(we::App* app, bool won)
    : we::State(app)
    , m_hasWon(won)
    , m_text(app)
{}

void GameEnd::Init()
{}

void GameEnd::HandleInput(sf::Event & e)
{
    // TODO check for user input to restart
    if (m_text.getText().getGlobalBounds().contains(sf::Mouse::getPosition(m_app->getWindow()).x, sf::Mouse::getPosition(m_app->getWindow()).y) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        // Pop both states and call a new GameState
        m_app->getStateMachine().RemoveState();
        m_app->getStateMachine().ProcessStateChanges();
    }
}

void GameEnd::Update(float deltaTime)
{}

void GameEnd::Draw(sf::RenderWindow &window)
{
    // Draw previous states because GameEnd state is just an overlay state
    for (auto &state : m_app->getStateMachine().GetStates())
    {
        // Don't draw the current state it is drawn later
        if (state != m_app->getStateMachine().GetActiveState())
        {
            state->Draw(window);
        }
    }

    // Draw text
    if (m_hasWon)   m_text.setString("You have won!" );
    else            m_text.setString("You have lost!");

    m_text.setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() / 2 - 128);
    m_text.setFillColour(sf::Color::White);
    m_text.Draw(window);

    m_text.setString("Restart");

    // If hovering change colour
    if (m_text.MouseHover())
    {
        m_text.setFillColour(sf::Color::Yellow);
    }


    m_text.Draw(window);
}

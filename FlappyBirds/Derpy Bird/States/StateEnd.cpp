#include "StateEnd.h"
#include "../Engine/App.h"
#include "../ResourceManager/ResourceManager.h"

StateEnd::StateEnd(we::App* app)
    : we::State(app)
    , m_textbox(app)
{}

void StateEnd::Init()
{
    // Init restartButton texture
    m_restartButton.setTexture(ResourceManager::get().getTexture("sprite_sheet"));
    m_restartButton.setTextureRect({ 0, 288, 256, 96 });
    m_restartButton.setOrigin({ 128, 48 });
    m_restartButton.setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() / 1.5f);
}

void StateEnd::HandleInput(sf::Event& e)
{
    // TODO Press SPACE to restart game
    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_app->getWindow());

        if (m_restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            m_app->getStateMachine().RemoveState();
            m_app->getStateMachine().ProcessStateChanges();
        }
    }
}

void StateEnd::Update(float deltaTime)
{}

void StateEnd::Draw(sf::RenderWindow &window)
{
    // Draw previous state
    for (auto& state : m_app->getStateMachine().GetStates())
    {
        if (state != m_app->getStateMachine().GetActiveState())
        {
            state->Draw(window);
        }
    }

    // Draw current state
    window.draw(m_restartButton);
}
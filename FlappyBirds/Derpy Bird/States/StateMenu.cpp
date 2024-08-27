#include "StateMenu.h"
#include "../Engine/App.h"

StateMenu::StateMenu(we::App* app)
    : we::State(app)
    , m_textbox(app)
{}

void StateMenu::Init()
{
    m_textbox.setCharachterSize(32);
    m_textbox.setString("Press SPACE to start");
    m_textbox.setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() / 2);
}

void StateMenu::HandleInput(sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Space)
    {
        m_app->getStateMachine().RemoveState();
        m_app->getStateMachine().ProcessStateChanges();
    }
}

void StateMenu::Update(float deltaTime)
{
    for (auto& state : m_app->getStateMachine().GetStates())
    {
        if (state != m_app->getStateMachine().GetActiveState())
        {
            state->Update(deltaTime);
        }
    }
}

void StateMenu::Draw(sf::RenderWindow& window)
{
    // This is an overlay state so draw the previous state as well
    for (auto& state : m_app->getStateMachine().GetStates())
    {
        if (state != m_app->getStateMachine().GetActiveState())
        {
            state->Draw(window);
        }
    }

    // Draw current state
    m_textbox.Draw(window);
}
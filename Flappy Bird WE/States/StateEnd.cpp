#include "StateEnd.h"
#include "../Engine/App.h"

StateEnd::StateEnd(we::App* app)
    : we::State(app)
    , m_textbox(app)
{}

void StateEnd::Init()
{}

void StateEnd::HandleInput(sf::Event& e)
{
    // TODO Press SPACE to restart game
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
}
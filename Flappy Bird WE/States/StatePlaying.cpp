#include "StatePlaying.h"
#include "../Engine/App.h"
#include "../defines.h"
#include "StateEnd.h"

StatePlaying::StatePlaying(we::App* app)
    : we::State(app)
    , m_textbox(app)
    , m_pipe(sf::Vector2i(app->ScreenWidth(), app->ScreenHeight()))
{}

void StatePlaying::Init()
{
    // Starting positions
    m_bird.SetPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() / 3);
    m_ground.setPosition(0, m_app->ScreenHeight());

    // Set blue sky background
    m_app->setClearColour(sf::Color(0, 255, 255));

    m_velocity.x = 0.0f;
    m_velocity.y = 0.0f;

    m_score      = 0;
}

void StatePlaying::HandleInput(sf::Event& e)
{
    // Jump if space is pressed
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Space)
    {
        // Only jump if the bird isn't above the screen
        if (m_bird.GetPosition().y > 0)
        {
            m_velocity.y = -JUMP_SPEED;
        }
    }
}

void StatePlaying::Update(float deltaTime)
{
    // Add gravity
    m_velocity.y += GRAVITY;

    // Move bird
    m_bird.Move(m_velocity.x * deltaTime, m_velocity.y * deltaTime);

    // Update ground
    m_ground.Update(deltaTime);

    // If the ground is about the end reset its position
    if (m_ground.getPosition().x + 640 <= m_app->ScreenWidth())
    {
        m_ground.setPosition(0, m_app->ScreenHeight());
    }

    // Update pipe
    m_pipe.Update(deltaTime);

    // Check if player has hit the floor
    if (m_bird.GetPosition().y + 16 > m_app->ScreenHeight() - GROUND_HEIGHT)
    {
        nextState();
    }

    // Check if a pipe and player have collided
    if (m_bird.isColliding(m_pipe.getLowerPipe().getGlobalBounds()) || m_bird.isColliding(m_pipe.getUpperPipe().getGlobalBounds()))
    {
        nextState();
    }

    // TODO ADD SCORE

    // Update scoreBoard
    m_textbox.setString(std::to_string(m_score));
    m_textbox.setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() / 8);
}

void StatePlaying::Draw(sf::RenderWindow& window)
{
    m_ground.   Draw(window);
    m_pipe.     Draw(window);
    m_textbox.  Draw(window);
    m_bird.     Draw(window);
}

void StatePlaying::nextState()
{
    m_app->getStateMachine().AddState(std::make_unique<StateEnd>(m_app), false);
    m_app->getStateMachine().ProcessStateChanges();
}
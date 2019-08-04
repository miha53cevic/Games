#pragma once
#include "State.h"
#include "../GUI/TextBox.h"
#include "../Entity/Bird.h"
#include "../Entity/Ground.h"
#include "../Entity/Pipe.h"

class StatePlaying : public we::State
{
public:
    StatePlaying(we::App* app);

    void Init           ()                          override;
    void HandleInput    (sf::Event& e)              override;
    void Update         (float deltaTime)           override;
    void Draw           (sf::RenderWindow& window)  override;

private:
    we::TextBox     m_textbox;
    Bird            m_bird;
    Ground          m_ground;
    Pipe            m_pipe;

    unsigned int    m_score;

    sf::Vector2f    m_velocity;

private:
    void nextState      ();
};
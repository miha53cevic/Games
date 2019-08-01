#pragma once
#include "State.h"
#include "../GUI/TextBox.h"

class GameEnd : public we::State
{
public:
    GameEnd(we::App* app, bool won);

    void Init           ()                          override;
    void HandleInput    (sf::Event& e)              override;
    void Update         (float deltaTime)           override;
    void Draw           (sf::RenderWindow& window)  override;

private:
    we::TextBox     m_text;
    bool            m_hasWon;
};

#pragma once
#include "State.h"
#include "../GUI/TextBox.h"

class StateEnd : public we::State
{
public:
    StateEnd(we::App* app);

    void Init           ()                          override;
    void HandleInput    (sf::Event& e)              override;
    void Update         (float deltaTime)           override;
    void Draw           (sf::RenderWindow& window)  override;

private:
    we::TextBox m_textbox;
};
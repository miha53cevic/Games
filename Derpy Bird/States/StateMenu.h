#pragma once
#include "State.h"
#include "../GUI/TextBox.h"

class StateMenu : public we::State
{
public:
    StateMenu(we::App* app);

    void Init           ()                          override;
    void HandleInput    (sf::Event& e)              override;
    void Update         (float deltaTime)           override;
    void Draw           (sf::RenderWindow& window)  override;

private:
    we::TextBox m_textbox;
};
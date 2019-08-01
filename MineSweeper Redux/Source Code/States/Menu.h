#pragma once
#include "State.h"
#include "../GUI/TextBox.h"

class Menu : public we::State
{
public:
    Menu(we::App* app);

    void Init               ()                          override;
    void HandleInput        (sf::Event& e)              override;
    void Update             (float deltaTime)           override;
    void Draw               (sf::RenderWindow& window)  override;

private:
    std::unique_ptr<we::TextBox> m_text[4];
};

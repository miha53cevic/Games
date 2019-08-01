#include "Menu.h"
#include "../Engine/App.h"
#include "GameState.h"

Menu::Menu(we::App* app)
    : we::State(app)
{
    // Initialize the text box pointers
    for (int i = 0; i < 4; i++)
        m_text[i] = std::make_unique<we::TextBox>(app);
}

void Menu::Init()
{
    m_text[0]->setString("MineSweeper Redux");
    m_text[0]->setCharachterSize(96);
    m_text[0]->setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() * 0.2f);

    m_text[1]->setString("START");
    m_text[1]->setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() * 0.5f);

    m_text[2]->setString("EXIT");
    m_text[2]->setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() * 0.5f + 96);

    m_text[3]->setString("miha53cevic");
    m_text[3]->setCharachterSize(32);
    m_text[3]->setPosition(m_app->ScreenWidth() / 2, m_app->ScreenHeight() * 0.9f);
}

void Menu::HandleInput(sf::Event & e)
{
    if (m_text[1]->MouseHover() && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        m_app->getStateMachine().AddState(std::make_unique<GameState>(m_app));
        m_app->getStateMachine().ProcessStateChanges();
    }
    else if (m_text[2]->MouseHover() && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        exit(0);
    }
}

void Menu::Update(float deltaTime)
{
    // Mouse hover change colour to yellow
    for (int i = 1; i < 3; i++)
    {
        if (m_text[i]->MouseHover())
            m_text[i]->setFillColour(sf::Color::Yellow);
        else m_text[i]->setFillColour(sf::Color::White);
    }
}

void Menu::Draw(sf::RenderWindow & window)
{
    for (int i = 0; i < 4; i++)
    {
        m_text[i]->Draw(window);
    }
}

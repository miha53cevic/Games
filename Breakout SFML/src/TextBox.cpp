#include "TextBox.h"

TextBox::TextBox(float x, float y)
{
    if(!m_font.loadFromFile("consola.ttf"))
    {
        // Error
    }
    else
    {
        m_text.setFont(m_font);
        m_text.setCharacterSize(64);
        m_text.setFillColor(sf::Color::White);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(5);

        m_text.setPosition(x, y);
    }
}

void TextBox::setString(std::string l_string)
{
    m_text.setString(l_string);
}

void TextBox::Draw(sf::RenderWindow *window)
{
    window->draw(m_text);
}


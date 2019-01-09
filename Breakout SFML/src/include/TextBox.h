#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class TextBox
{
    public:
        TextBox(float x, float y);
        ~TextBox() = default;

        void setString(std::string l_string);
        void Draw(sf::RenderWindow *window);

    private:
        sf::Font m_font;
        sf::Text m_text;
};

#endif // TEXTBOX_H

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>

class Window
{
public:
    Window(sf::Vector2u l_size, std::string l_name);
    ~Window();

    void Update();

    void BeginDraw(sf::Color c = sf::Color::Black);
    void EndDraw();

    bool isDone();

    sf::Vector2u getSize();

    sf::RenderWindow* getRenderWindow();

private:
    sf::RenderWindow m_window;

    bool m_bDone;

    void Destroy();
    void Setup(sf::Vector2u l_size, std::string l_name);
};

#endif // WINDOW_H

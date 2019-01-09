#include "Window.h"

Window::Window(sf::Vector2u l_size, std::string l_name)
{
    Setup(l_size, l_name);
}

Window::~Window()
{
    Destroy();
}

void Window::Update()
{
    sf::Event e;

    while(m_window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            m_bDone = true;
        }
    }
}

void Window::BeginDraw(sf::Color c)
{
    m_window.clear(c);
}

void Window::EndDraw()
{
    m_window.display();
}

sf::RenderWindow* Window::getRenderWindow()
{
    return &m_window;
}

sf::Vector2u Window::getSize()
{
    return m_window.getSize();
}

void Window::Setup(sf::Vector2u l_size, std::string l_name)
{
    m_window.create(sf::VideoMode(l_size.x, l_size.y), l_name);
    m_window.setVerticalSyncEnabled(true);

    m_bDone = false;
}

void Window::Destroy()
{
    m_window.close();
}

bool Window::isDone()
{
    return m_bDone;
}


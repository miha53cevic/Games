#include "Window.h"

Window::Window() { Setup(sf::Vector2u(640, 480), "Default Window"); }
Window::Window(sf::Vector2u l_size, std::string l_title) { Setup(l_size, l_title); }
Window::~Window() { Destroy(); }

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_done = true;
	}
}

void Window::BeginDraw(sf::Color l_color) { m_window.clear(l_color); }
void Window::Draw(sf::Drawable& l_drawable) { m_window.draw(l_drawable); }
void Window::EndDraw() { m_window.display(); }

bool Window::isDone() { return m_done; }

void Window::Destroy() { m_window.close(); }

sf::Vector2u Window::getWindowSize() { return m_size; }
sf::RenderWindow* Window::getRenderWindow() { return &m_window; }

void Window::Setup(sf::Vector2u l_size, std::string l_title)
{
	m_window.create(sf::VideoMode(l_size.x, l_size.y), l_title);
	m_size = l_size;

	m_done = false;
	m_window.setVerticalSyncEnabled(true);
}

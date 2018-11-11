#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
public:
	Window();
	Window(sf::Vector2u l_size, std::string l_title);
	~Window();

	bool isDone();

	void BeginDraw(sf::Color l_color);
	void Draw(sf::Drawable& l_drawable);
	void EndDraw();

	void Update();

	sf::Vector2u getWindowSize();

	void Destroy();

	sf::RenderWindow* getRenderWindow();

private:
	sf::RenderWindow m_window;

	bool m_done;
	sf::Vector2u m_size;

	void Setup(sf::Vector2u l_size, std::string l_title);
};


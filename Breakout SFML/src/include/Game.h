#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Window.h"
#include "World.h"
#include "Player.h"

class Game
{
   public:
       Game(sf::Vector2u l_size, std::string l_name);
       ~Game() = default;

       void HandleInput();
       void Update();
       void Render();

       void getElapsedTime();

       Window* getWindow();

   private:
       Window   m_window;

       World    m_world;
       Player   m_player;

       sf::Time m_elapsed;
       sf::Clock m_clock;

};

#endif // GAME_H

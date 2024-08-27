//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 22.5.2019.
//

#include <vector>

#include "mihaSimpleSFML.h"
#include "../Server/UdpHandler.hpp"

class Client : public mihaSimpleSFML
{
public:
    Client(sf::IpAddress adress, unsigned short int port)
    {
        handler.setBlocking(false);

        handler.try_connect(5001);
        handler.ConnectionRequest(adress, port);

        if (handler.WaitForConnection(15))  connected = true;
        else                                connected = false;
    }

private:
    UdpHandler handler;

    bool connected;

    sf::CircleShape     ball;
    sf::RectangleShape  player;

    sf::Font font;
    sf::Text text;

    bool OnUserCreate() override
    {
        // Setup font
        if (!font.loadFromFile("Client/fonts/arial.ttf"))
    	{
	    	// error...
	    }

        // Setup text
	    sf::Text text;
	    text.setFont(font);
	    text.setCharacterSize(64);
        text.setFillColor(sf::Color::Black);
	    text.setOutlineColor(sf::Color::White);
	    text.setOutlineThickness(5);
	
	    text.setPosition(ScreenWidth() / 2, ScreenHeight() / 2);
        text.setString("0");

        // Setup game
        ball.setFillColor(sf::Color::Yellow);
        ball.setRadius(10.0f);
        ball.setOrigin(ball.getRadius(), ball.getRadius());
        ball.setPosition(ScreenWidth() / 2, ScreenHeight() / 2);
 
        player.setFillColor(sf::Color::White);
        player.setSize(sf::Vector2f(20, 100));

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        // If a connection has been established
        if (connected)
        {
            // Get ballPos from server
            sf::Packet data;
            handler.Receive(data);  

            float x, y, score;
            if (data >> x)
            {
                if (data >> y)
                {
                    ball.setPosition(x, y);

                    if (data >> score)
                    {
                        text.setString(std::to_string(score));
                    }
                }
            }

            // Send player pos to server
            data.clear();
            data << player.getPosition().x  << player.getPosition().y;
            handler.Send(data, *handler.getIPAdress(), *handler.getPort());
        }

        // Controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.move(0, -100.0f * elapsed.asSeconds());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.move(0, 100.0f * elapsed.asSeconds());
        }

        // Drawing routines
        Draw(ball);
        Draw(player);
        Draw(text);


        return true;
    }
};
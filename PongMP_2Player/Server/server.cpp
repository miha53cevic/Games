//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 22.5.2019.
//

#include "server.hpp"
#include <SFML/Graphics.hpp>

Server::PongServer::PongServer(unsigned short int port)
{
    // Using inline if with cout you must enclose expression in ()
    std::cout << (m_handler.try_connect(port) ? "Server started!\n" : "Failed to start server!\n");

    // Blocking false so it doesn't freeze the program until it receives an answer
    m_handler.setBlocking(false);

    m_running = true;
    m_Connected = 0;

    // Setup game starting values
    m_ScreenSize.x = 640;
    m_ScreenSize.y = 480;

    m_ballPos.x = m_ScreenSize.x / 2;
    m_ballPos.y = m_ScreenSize.y / 2;

    m_ballVelocity.x = cosf(M_PI / 4);
    m_ballVelocity.y = sinf(M_PI / 4);

    m_Score = 5;
}

void Server::PongServer::UpdateGame(float Speed)
{
    // Delta time
    GetElapsedTime();

    m_ballPos.x += m_ballVelocity.x * m_elapsed.asSeconds() * Speed;
    m_ballPos.y += m_ballVelocity.y * m_elapsed.asSeconds() * Speed;

    // Bounce ball off boundry
    // the ball can go outside the left and right boundry
    // if it  happens the player losses a point
    if (m_ballPos.y < 0 || m_ballPos.y >= m_ScreenSize.y)
    {
        m_ballVelocity.y *= -1.0f;
    }

    // Player hitting ball
    sf::IntRect ball;
    sf::IntRect player1;
    sf::IntRect player2;

    ball.width  = 20;
    ball.height = 20;
    ball.top    = m_ballPos.y - 10;
    ball.left   = m_ballPos.x - 10;

    player1.width   = 20;
    player1.height  = 100;
    player1.top     = m_players[0].m_playerPos.y;
    player1.left    = m_players[0].m_playerPos.x;

    player2.width   = 20;
    player2.height  = 100;
    player2.top     = m_players[1].m_playerPos.y;
    player2.left    = m_players[1].m_playerPos.x;

    if (player1.intersects(ball) || player2.intersects(ball))
    {
        m_ballVelocity.x *= -1.0f;    
    }

    // Has the ball went outside the left boundry
    if (m_ballPos.x < 0)
    {
        // Reset ball position to center of the screen
        m_ballPos.x = m_ScreenSize.x / 2;
        m_ballPos.y = m_ScreenSize.y / 2;

        m_Score--;
    }
}

void Server::PongServer::ReceiveData()
{
    // Receive data from both clients
    sf::Packet data;
    m_handler.Receive(data);

    if (*m_handler.getIPAdress() == m_players[0].m_adress && *m_handler.getPort() == m_players[0].m_port)
    {
        float x, y;
        if (data >> x)
        {
            if (data >> y)
            {
                m_players[0].m_playerPos.x = x;
                m_players[0].m_playerPos.y = y;
            }
        }
    }
    else if (*m_handler.getIPAdress() == m_players[1].m_adress && *m_handler.getPort() == m_players[1].m_port)
    {
        float x, y;
        if (data >> x)
        {
            if (data >> y)
            {
                m_players[1].m_playerPos.x = x;
                m_players[1].m_playerPos.y = y;
            }
        }
    }

    // Flip second player X coordinates so he is on the right side
    m_players[1].m_playerPos.x = m_ScreenSize.x - 20;   // ScreenSize - PaddleWidth  
}

void Server::PongServer::SendData()
{
    // Send ball data and enemy position data
    for (int i = 0; i < 2; i++)
    {
        sf::Packet data;

        if (i == 0)
        {
            data << m_ballPos.x << m_ballPos.y << m_Score;
            data << m_players[1].m_playerPos.x << m_players[1].m_playerPos.y;
        }
        if (i == 1)
        {
            // Flip second player ballX position
            data << m_ScreenSize.x - m_ballPos.x << m_ballPos.y << m_Score;
            data << m_ScreenSize.x - 20 << m_players[0].m_playerPos.y;
        } 

        m_handler.Send(data, m_players[i].m_adress, m_players[i].m_port);
    }
}

bool Server::PongServer::WaitForPlayers(int timeout)
{
    if (m_Connected != 2)
    {
        if (m_handler.WaitForConnection(timeout))
        {
            m_players[m_Connected].m_adress  = *m_handler.getIPAdress();
            m_players[m_Connected].m_port    = *m_handler.getPort();

            std::cout << "Player "  <<           m_Connected            << " has joined!\n";
            std::cout << "Adress: " << m_players[m_Connected].m_adress  << "\n";
            std::cout << "Port: "   << m_players[m_Connected].m_port    << "\n";

            m_Connected++;

            return true;
        }
    }
    else std::cout << "2 players are already connected!\n";

    return false;
}

void Server::PongServer::GetElapsedTime()
{
    m_elapsed = m_clock.restart();
}
//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 22.5.2019.
//

#include "server.hpp"

Server::PongServer::PongServer(unsigned short int port)
{
    // Using inline if with cout you must enclose expression in ()
    std::cout << (m_handler.try_connect(port) ? "Server started!\n" : "Failed to start server!\n");

    // Blocking false so it doesn't freeze the program until it receives an answer
    m_handler.setBlocking(false);

    m_running = true;

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
    // the ball can go outside the left boundry
    // if it  happens the player losses a point
    if (m_ballPos.x >= m_ScreenSize.x)
    {
        m_ballVelocity.x *= -1.0f;
    }
    if (m_ballPos.y < 0 || m_ballPos.y >= m_ScreenSize.y)
    {
        m_ballVelocity.y *= -1.0f;
    }

    // Player hitting ball
    if (m_ballPos.x <= 20 && m_ballPos.y >= m_players.m_playerPos.y && m_ballPos.y <= m_players.m_playerPos.y + 100.0f)
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
    sf::Packet data;
    m_handler.Receive(data);

    float x, y;
    if (data >> x)
    {
        if (data >> y)
        {
            m_players.m_playerPos.x = x;
            m_players.m_playerPos.y = y;
        }
    }
}

void Server::PongServer::SendData()
{
    sf::Packet data;
    data << m_ballPos.x << m_ballPos.y << m_Score;

    m_handler.Send(data, m_players.m_adress, m_players.m_port);
}

bool Server::PongServer::WaitForPlayers(int timeout)
{
    if (m_handler.WaitForConnection(timeout))
    {
        m_players.m_adress  = *m_handler.getIPAdress();
        m_players.m_port    = *m_handler.getPort();

        std::cout << "Adress: " << m_players.m_adress << "\n";
        std::cout << "Port: " << m_players.m_port << "\n";

        return true;
    }

    return false;
}

void Server::PongServer::GetElapsedTime()
{
    m_elapsed = m_clock.restart();
}
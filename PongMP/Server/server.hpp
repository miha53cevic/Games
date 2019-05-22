//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 22.5.2019.
//

#pragma once

#include "UdpHandler.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

struct Player
{
    sf::Vector2f        m_playerPos;
    sf::IpAddress       m_adress;

    unsigned short int  m_port;
};

namespace Server
{
    class PongServer
    {
    public:
        PongServer(unsigned short int port = 5003);

        void ReceiveData();
        void SendData();
        void UpdateGame(float Speed = 100.0f);
        void GetElapsedTime();

        bool WaitForPlayers(int timeout = 5);

        bool isRunning() { return m_running; }

        UdpHandler* getHandler() { return &m_handler; }

    private:
        UdpHandler m_handler;

        sf::Vector2f m_ballPos;
        sf::Vector2f m_ballVelocity;
        sf::Vector2f m_ScreenSize;

        Player  m_players;

        int     m_Score;

        sf::Clock   m_clock;
        sf::Time    m_elapsed;

        bool        m_running;
    };
}
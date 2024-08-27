//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 22.5.2019.
//

#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

class UdpHandler
{
public:
    UdpHandler() {}
    ~UdpHandler() 
    {
        m_socket.unbind();
    }

    // Tries to bind port
    bool try_connect(unsigned short int port)
    {
        if (m_socket.bind(port) != sf::Socket::Done)
        {
            // Error
            std::cout << "Could not bind to port " << port << "\n";

            return false;
        }
        else
        {
            m_port = port;

            return true;
        }
    }

    // Send packet to specific Adress and Port
    void Send(sf::Packet data, sf::IpAddress adress, unsigned short int port)
    {
        m_socket.send(data, adress, port);

        //m_adress    = adress;
        //m_port      = port;        
    }

    // If a packet is received its IP adress and port are saved in m_adress and m_port
    void Receive(sf::Packet& data)
    {
        m_socket.receive(data, m_adress, m_port);
    }

    // Sends a request which is found by WaitForConnection()
    void ConnectionRequest(sf::IpAddress adress, unsigned short int port)
    {
        sf::Packet data;
        data << 200;

        Send(data, adress, port);
    }

    // timeout is in SECONDS
    bool WaitForConnection(unsigned int timeout = 5)
    {
        sf::Clock   clock;
        sf::Time    elapsed;

        while (elapsed.asSeconds() <= timeout)
        {
            sf::Packet data;

            Receive(data);
            int code;
            data >> code;
            if (code == 200)
            {
                std::cout << "Established connection!\n";
                return true;
            }

            elapsed += clock.restart();
        }

        std::cout << "No connection was established after waiting " << timeout << " seconds!\n";

        return false;
    }

    std::vector<float> PacketToVector(sf::Packet data)
    {
        float value;
        std::vector<float> vecData;

        while (!data.endOfPacket())
        {
            if (data >> value)
            {
                vecData.push_back(value);
            }
            else break;
        }

        return vecData;
    }

    // Does the program freeze until an answer is received
    void setBlocking(bool setting)  { m_socket.setBlocking(setting); }

    sf::UdpSocket* getSocket()      { return &m_socket; }
    sf::IpAddress* getIPAdress()    { return &m_adress; }
    unsigned short int* getPort()   { return &m_port;   }

private:
    sf::UdpSocket m_socket;
    sf::IpAddress m_adress;

    unsigned short int m_port;
};
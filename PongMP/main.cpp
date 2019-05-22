//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 22.5.2019.
//
// Compile command: g++ -std=c++17 -o app Server/server.cpp main.cpp $(pkg-config --libs --cflags sfml-system sfml-network sfml-graphics)
//

#include <iostream>

#include "Server/server.hpp"
#include "Client/client.hpp"

// Client runs on 5001 by default
// Server runs on 5003 by default

int main()
{
    int choice;

    std::cout << "Start:\n\t1 - Client\n\t2 - Server\nAnswer: ";
    std::cin >> choice;

    if (choice == 1)
    {
        sf::IpAddress adress;
        std::cout << "\n\nServer ip: ";
        std::cin >> adress;

        Client app(adress, 5003);
        app.Construct(640, 480, L"Client");
        app.Start();
    }
    else if (choice == 2)
    {
        Server::PongServer server;
        if (server.WaitForPlayers(30))
        {
            // If a client connects send back a response to the client
            server.getHandler()->ConnectionRequest(*server.getHandler()->getIPAdress(), *server.getHandler()->getPort());
        }

        // Otherwise the starting time in gameUpdate is higher because of the wait
        server.GetElapsedTime();

        while (server.isRunning())
        {
            server.ReceiveData();
            server.SendData();
            server.UpdateGame(150.0f);
        }
    }
    else
    {
        std::cout << choice << " is not a valid answer, try again!\n";
        main();
    }

    return 0;
}
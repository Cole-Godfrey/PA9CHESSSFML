


#pragma once
#include "Game.hpp"
#include "SFML/Network.hpp"

using namespace sf;

void runMainMenu();
void showRulesWindow();
void playGameOnSameDesktop();
bool send(TcpSocket& sock, int sX, int sY, int dX, int dY);
bool receive(TcpSocket& sock, int& sX, int& sY, int& dX, int& dY);
void playNetworkHost();
void playNetworkJoin(IpAddress serverIp);
void network(TcpSocket& sock, bool ismyturn);

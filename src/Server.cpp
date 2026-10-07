#include "../headers/Server.hpp"

/*
* Constructeurs & Destructeur
*/

Server::Server(std::string name, int version): name(name), version(version){}

Server::Server(const Server& server) {

}

Server::~Server() {

}

/*
* Geters & Seters
*/

void Server::setName(std::string name) {
    this->name = name;
}

std::string Server::getName() {
    return this->name;
}

void Server::setIp(std::string ip) {
    this->ip = ip;
}

std::string Server::getIp() {
    return this->ip;
}

void Server::setVersions(int version) {
    this->version = version;
}

int Server::getVersion() {
    return this->version;
}

void Server::setPort(int port) {
    this->port = port;
}

int Server::getPort() {
    return this->port;
}

/*
* Méthodes
*/
void Server::consoleWriter() {

}

void Server::fileWriter() {

}
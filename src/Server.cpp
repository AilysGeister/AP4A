#include "Server.hpp"

// Constructeur par défaut:
Server::Server() : name("Server_Default"), ip(Ipv4()), version(0), port(8080) {}

// Constructeur paramétré (avec liste d'initialisation):
Server::Server(const std::string &name, const Ipv4 &ip, int port, int version)
    : name(name), ip(ip), port(port), version(version) {}

// Constructeur de recopie:
Server::Server(const Server &other)
    : name(other.name), ip(other.ip), port(other.port), version(other.version) {
}

// Opérateur d'affectation:
Server &Server::operator=(const Server &other) {
  if (this != &other) {
    this->name = other.name;
    this->ip = other.ip;
    this->version = other.version;
    this->port = other.port;
  }
  return *this;
}

// Destructeur:
Server::~Server() {}

// Setters & Getters:
void Server::setName(const std::string &name) { this->name = name; }
std::string Server::getName() const { return this->name; }

void Server::setIp(const Ipv4 &ip) { this->ip = ip; }
Ipv4 Server::getIp() const { return this->ip; }

void Server::setVersion(int version) { this->version = version; }
int Server::getVersion() const { return this->version; }

void Server::setPort(int port) { this->port = port; }
int Server::getPort() const { return this->port; }

// Methodes:
void Server::consoleWrite(const std::string &data) const {
  std::cout << "[" << name << "] " << data << std::endl;
}

void Server::fileWrite(const std::string &filename,
                       const std::string &data) const {
  std::ofstream file(filename, std::ios::app);
  if (file.is_open()) {
    file << data << "\n";
  } else {
    std::cerr << "[ERREUR] Impossible d'ouvrir le fichier : " << filename
              << std::endl;
  }
}

// Surcharge <<
std::ostream &operator<<(std::ostream &os, const Server &server) {
  os << "Server[Name: " << server.name << ", IP: " << server.ip
     << ", Port: " << server.port << ", Ver: " << server.version << "]";
  return os;
}
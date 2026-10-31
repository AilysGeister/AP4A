#ifndef SERVER_HPP
#define SERVER_HPP

#include "Ip.hpp"
#include <iostream>
#include <string>

class Server {
private:
  std::string name;
  Ipv4 ip;
  int port;
  int version;

public:
  // Forme cannonique:
  Server();
  Server(const std::string &name, const Ipv4 &ip, int port, int version);
  Server(const Server &other);
  Server &operator=(const Server &other);
  ~Server();

  // Setters & Getters:
  void setName(const std::string &name);
  std::string getName() const;

  void setIp(const Ipv4 &ip);
  Ipv4 getIp() const;

  void setVersion(int version);
  int getVersion() const;

  void setPort(int port);
  int getPort() const;

  // Log:
  void consoleWrite(const std::string &data) const;
  void fileWrite(const std::string &filename, const std::string &data) const;

  // Surcharge<<:
  friend std::ostream &operator<<(std::ostream &os, const Server &server);
};

#endif
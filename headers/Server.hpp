#ifndef SERVER_HPP
#define SERVER_HPP

#include <fstream>
#include <iostream>
#include <string>

class Server {
private:
  std::string name;
  std::string ip;
  int version;
  int port;

public:
  // Forme cannonique
  Server();
  Server(const std::string &name, int version);
  Server(const Server &other);
  Server &operator=(const Server &other);
  ~Server();

  // Setters & Geters
  void setName(const std::string &name);
  std::string getName() const;

  void setIp(const std::string &ip);
  std::string getIp() const;

  void setVersion(int version);
  int getVersion() const;

  void setPort(int port);
  int getPort() const;

  // Log
  void consoleWrite(const std::string &data) const;
  void fileWrite(const std::string &filename, const std::string &data) const;

  // Surcharge <<
  friend std::ostream &operator<<(std::ostream &os, const Server &server);
};

#endif

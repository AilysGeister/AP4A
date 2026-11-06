#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include "Ip.hpp"
#include "Room.hpp"
#include "Scheduler.hpp"
#include "Sensor.hpp"
#include "Server.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ConfigLoader {
private:
  static Ipv4 parseIp(const std::string &ipStr) {
    int ipVal[4] = {0, 0, 0, 0};
    char dot;
    std::stringstream ipStream(ipStr);
    ipStream >> ipVal[0] >> dot >> ipVal[1] >> dot >> ipVal[2] >> dot >>
        ipVal[3];
    return Ipv4(ipVal, 24);
  }

public:
  static std::vector<Room *> loadRooms(const std::string &filepath) {
    std::vector<Room *> rooms;
    std::ifstream file(filepath);
    if (!file.is_open()) {
      std::cerr << "[ConfigLoader] Impossible d'ouvrir : " << filepath
                << std::endl;
      return rooms;
    }

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty() || line[0] == '#')
        continue;
      std::stringstream ss(line);
      std::string segment;

      // CSV separe par des virgules:
      std::getline(ss, segment, ','); // ID (ignoré car généré auto)
      std::string name;
      std::getline(ss, name, ',');

      float temp, humidity;
      int pressure, particles;
      char comma;
      ss >> temp >> comma >> humidity >> comma >> pressure >> comma >>
          particles;

      Room *room = new Room(name);
      room->setTemperature(temp);
      room->setHumidity(humidity);
      room->setPressure(pressure);
      room->setParticles(particles);
      rooms.push_back(room);
    }
    file.close();
    std::cout << "[ConfigLoader] " << rooms.size() << " salle(s) chargée(s)."
              << std::endl;
    return rooms;
  }

  static std::vector<Server *> loadServers(const std::string &filepath) {
    std::vector<Server *> servers;
    std::ifstream file(filepath);
    if (!file.is_open()) {
      std::cerr << "[ConfigLoader] Impossible d'ouvrir : " << filepath
                << std::endl;
      return servers;
    }

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty() || line[0] == '#')
        continue;
      std::stringstream ss(line);
      std::string name, ipStr;
      int port, version;
      char comma;

      std::getline(ss, name, ',');
      std::getline(ss, ipStr, ',');
      ss >> port >> comma >> version;

      Server *server = new Server(name, parseIp(ipStr), port, version);
      servers.push_back(server);
    }
    file.close();
    std::cout << "[ConfigLoader] " << servers.size() << " serveur(s) chargé(s)."
              << std::endl;
    return servers;
  }

  static void loadSensors(const std::string &filepath,
                          const std::vector<Server *> &servers,
                          const std::vector<Room *> &rooms,
                          Scheduler &scheduler) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
      std::cerr << "[ConfigLoader] Impossible d'ouvrir : " << filepath
                << std::endl;
      return;
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
      if (line.empty() || line[0] == '#')
        continue;
      std::stringstream ss(line);
      std::string type, ipStr, serverIpStr;
      float accuracy;
      int roomId;
      char comma;

      std::getline(ss, type, ',');
      std::getline(ss, ipStr, ',');
      ss >> accuracy >> comma;
      std::getline(ss, serverIpStr, ',');
      ss >> roomId;

      Ipv4 sensorIp = parseIp(ipStr);
      Ipv4 targetServerIp = parseIp(serverIpStr);

      // Recherche du serveur correspondant par IP:
      Server *targetServer = nullptr;
      for (auto *s : servers) {
        if (s->getIp() == targetServerIp) {
          targetServer = s;
          break;
        }
      }

      // Recherche de la room correspondante par ID index:
      Room *targetRoom = nullptr;
      if (roomId >= 0 && static_cast<size_t>(roomId) < rooms.size()) {
        targetRoom = rooms[roomId];
      }

      // Instanciation du bon type de capteur:
      ISensor *newSensor = nullptr;
      if (type == "Thermometer") {
        newSensor = new Thermometer(sensorIp, accuracy, targetServer);
      } else if (type == "HumiditySensor") {
        newSensor = new HumiditySensor(sensorIp, accuracy, targetServer);
      } else if (type == "PressureSensor") {
        newSensor = new PressureSensor(sensorIp, accuracy, targetServer);
      } else if (type == "ParticleSensor") {
        newSensor = new ParticleSensor(sensorIp, accuracy, targetServer);
      }

      if (newSensor) {
        newSensor->setRoom(targetRoom);
        scheduler.addSensor(newSensor);
        count++;
      }
    }
    file.close();
    std::cout << "[ConfigLoader] " << count << " capteur(s) chargé(s) et liés."
              << std::endl;
  }
};

#endif // CONFIG_LOADER_HPP
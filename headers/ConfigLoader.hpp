#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

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
public:
  static std::vector<Room *> loadRooms(const std::string &filepath) {
    std::vector<Room *> rooms;
    std::ifstream file(filepath);
    if (!file.is_open()) {
      std::cerr << "[ConfigLoader] Unable to open file : " << filepath << std::endl;
      return rooms;
    }

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty() || line[0] == '#')
        continue; // Ignore les commentaires
      std::stringstream ss(line);
      std::string name;
      float temp, humidity;
      int pressure, particles;

      if (ss >> name >> temp >> humidity >> pressure >> particles) {
        Room *room = new Room(name);
        room->setTemperature(temp);
        room->setHumidity(humidity);
        room->setPressure(pressure);
        room->setParticles(particles);
        rooms.push_back(room);
      }
    }
    file.close();
    std::cout << "[ConfigLoader] " << rooms.size() << " rooms loaded."
              << std::endl;
    return rooms;
  }

  static void loadSensors(const std::string &filepath, Server *server,
                          const std::vector<Room *> &rooms,
                          Scheduler &scheduler) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
      std::cerr << "[ConfigLoader] Unable to open file : " << filepath << std::endl;
      return;
    }

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty() || line[0] == '#')
        continue;
      std::stringstream ss(line);
      std::string type, ipStr;
      float accuracy;
      int roomIndex;

      if (ss >> type >> ipStr >> accuracy >> roomIndex) {
        int ipVal[4] = {0, 0, 0, 0};
        char dot;
        std::stringstream ipStream(ipStr);
        ipStream >> ipVal[0] >> dot >> ipVal[1] >> dot >> ipVal[2] >> dot >>
            ipVal[3];
        Ipv4 ip(ipVal, 24);

        Room *targetRoom = (roomIndex >= 0 && roomIndex < rooms.size())
                               ? rooms[roomIndex]
                               : nullptr;

        ISensor *newSensor = nullptr;
        if (type == "Thermometer") {
          newSensor = new Thermometer(ip, accuracy, server);
        } else if (type == "HumiditySensor") {
          newSensor = new HumiditySensor(ip, accuracy, server);
        } else if (type == "PressureSensor") {
          newSensor = new PressureSensor(ip, accuracy, server);
        } else if (type == "ParticleSensor") {
          newSensor = new ParticleSensor(ip, accuracy, server);
        }

        if (newSensor) {
          // newSensor->setRoom(targetRoom);
          scheduler.addSensor(newSensor);
        }
      }
    }
    file.close();
    std::cout << "[ConfigLoader] Done." << std::endl;
  }
};

#endif // CONFIG_LOADER_HPP
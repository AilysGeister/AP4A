#include "ConfigLoader.hpp"
#include "Room.hpp"
#include "Scheduler.hpp"
#include "Server.hpp"
#include <iostream>
#include <vector>

int main() {
  Server server("CentralServer", Ipv4(), 8080, 1);
  std::cout << server << std::endl;

  Scheduler scheduler(1);

  std::vector<Room *> rooms = ConfigLoader::loadRooms("config/rooms.txt");

  ConfigLoader::loadSensors("config/sensors.txt", &server, rooms, scheduler);

  scheduler.simulation(5);

  for (auto *room : rooms) {
    delete room;
  }
  rooms.clear();

  return 0;
}
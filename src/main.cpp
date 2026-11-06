#include <iostream>
#include <vector>
#include "Server.hpp"
#include "Scheduler.hpp"
#include "Room.hpp"
#include "ConfigLoader.hpp"

int main() {
    std::cout << "=== LANCEMENT DU SIMULATEUR IOT ===" << std::endl;

    Scheduler scheduler(1);

    std::vector<Room*> rooms = ConfigLoader::loadRooms("config/rooms.csv");

    std::vector<Server*> servers = ConfigLoader::loadServers("config/servers.csv");

    ConfigLoader::loadSensors("config/sensors.csv", servers, rooms, scheduler);

    scheduler.simulation(5);

    for (auto* room : rooms) delete room;
    for (auto* server : servers) delete server;
    rooms.clear();
    servers.clear();

    std::cout << "=== FIN DU PROGRAMME ===" << std::endl;
    return 0;
}
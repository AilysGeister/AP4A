#include <iostream>
#include <fstream>
#include "Server.hpp"
#include "Sensor.hpp"
#include "Scheduler.hpp"

int main() {
    Server server("CentralServer", Ipv4(), 8080, 1);
    Sensor tempSensor("Temperature", &server);
    Sensor humiditySensor("Humidity", &server);

    Scheduler scheduler(1);
    scheduler.addSensor(&tempSensor);
    scheduler.addSensor(&humiditySensor);

    std::cout << "=== TEST AFFICHAGE CONSOLE ===" << std::endl;
    std::cout << server << std::endl;
    std::cout << tempSensor << std::endl;
    std::cout << humiditySensor << std::endl;
    std::cout << scheduler << std::endl;


    std::cout << "\n=== TEST REDIRECTION VERS FICHIER LOG ===" << std::endl;
    std::ofstream logFile("data/system_status.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "--- STATUT SYSTÈME ---" << std::endl;
        logFile << server << std::endl;
        logFile << tempSensor << std::endl;
        logFile << humiditySensor << std::endl;
        logFile << scheduler << std::endl;
        logFile.close();
        std::cout << "-> Les états des objets ont été sauvegardés dans 'system_status.log'." << std::endl;
    }

    scheduler.simulation(3);

    return 0;
}
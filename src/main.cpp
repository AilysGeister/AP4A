#include <iostream>
#include <fstream>
#include "Server.hpp"

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "        TEST DE LA CLASSE SERVER          " << std::endl;
    std::cout << "==========================================" << std::endl << std::endl;

    // 1. Test du constructeur par défaut
    std::cout << "[1] Création du serveur par défaut..." << std::endl;
    Server s1;
    std::cout << "    s1 -> " << s1 << std::endl << std::endl;

    // 2. Test du constructeur paramétré et des Setters/Getters
    std::cout << "[2] Création d'un serveur paramétré et modification des propriétés..." << std::endl;
    Server s2("MainServer", 2);
    s2.setIp("192.168.1.100");
    s2.setPort(8080);
    std::cout << "    s2 -> " << s2 << std::endl << std::endl;

    // 3. Test de la forme de Coplien (Recopie et Affectation)
    std::cout << "[3] Test de la recopie et de l'affectation..." << std::endl;
    Server s3(s2);                   // Constructeur de recopie
    Server s4 = s1;                  // Opérateur d'affectation
    std::cout << "    s3 (copie de s2) -> " << s3 << std::endl;
    std::cout << "    s4 (affecté par s1) -> " << s4 << std::endl << std::endl;

    // 4. Test des méthodes de log (consoleWrite & fileWrite)
    std::cout << "[4] Test de consoleWrite() et fileWrite()..." << std::endl;
    std::string sampleLog1 = "2026-10-07 14:00:00 | TempSensor_01 | 22.5 C";
    std::string sampleLog2 = "2026-10-07 14:00:05 | HumiditySensor_01 | 45 %";

    // Affichage console
    s2.consoleWrite(sampleLog1);
    s2.consoleWrite(sampleLog2);

    // Écriture dans un fichier log (au format texte / CSV)
    s2.fileWrite("data/temperature_logs.csv", sampleLog1);
    s2.fileWrite("data/humidity_logs.csv", sampleLog2);
    std::cout << "    --> Les logs ont été écrits dans 'temperature_logs.csv' et 'humidity_logs.csv'." << std::endl << std::endl;

    // 5. Test de la redirection d'un flux vers un fichier avec std::ofstream
    std::cout << "[5] Test d'écriture du serveur via std::ofstream..." << std::endl;
    std::ofstream serverLogFile("data/server_info.txt", std::ios::app);
    if (serverLogFile.is_open()) {
        serverLogFile << s2 << std::endl;
        serverLogFile.close();
        std::cout << "    --> Informations du serveur écrites dans 'server_info.txt'." << std::endl;
    } else {
        std::cerr << "    [ERREUR] Impossible d'ouvrir server_info.txt" << std::endl;
    }

    std::cout << std::endl << "==========================================" << std::endl;
    std::cout << "        FIN DES TESTS DU SERVEUR          " << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}
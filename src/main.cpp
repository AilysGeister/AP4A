#include <iostream>
#include "../headers/Server.hpp"

int main() {
    /*
    Server* server = new server("nom", "verison");
    
    serveur->show();

    Scheduler scheduler(server);

    Sensor* sensori = new
    */
    //Tests:
    Server s1("ui", 1);
    Server s2(s1);
    std::cout << "Name: " << s2.getName() << "\nVersion: " << s2.getVersion() << std::endl;
    return 0;
}

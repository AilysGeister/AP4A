#include "Ip.hpp"
#include <map>

#include "Scheduler.hpp"
#include "Sensor.hpp"
#include "Server.hpp"

// Constructeur:
Ipv4::Ipv4() : value{192, 168, 0, 1}, subnetMask(24) {}

Ipv4::Ipv4(const Ipv4 &ipv4) {
  for (int i = 0; i < 4; i++) {
    this->value[i] = value[i];
  }
  this->subnetMask = ipv4.subnetMask;
}

Ipv4::Ipv4(int value[4], int subnetMask) {
  // Un octet ne peux définir un entier supérieur à 255:
  for (int i = 0; i < 4; i++) {
    this->value[i] = (value[i] <= 255) ? value[i] : 255;
  }
  this->subnetMask = (subnetMask < 32) ? subnetMask : 24;
}

// Destructeur:
Ipv4::~Ipv4() {}

// Sruchage d'opérateurs:
Ipv4 Ipv4::operator+(const Ipv4 &ipv4) {
  for (int i = 0; i < 4; i++) {
    int sum = this->value[i] + ipv4.value[i];
    this->value[i] = (sum <= 255) ? sum : 255;
  }
  return *this;
}

bool Ipv4::operator==(const Ipv4 &ipv4) {
  for (int i = 0; i < 4; i++) {
    if (this->value[i] != ipv4.value[i]) {
      return false;
    }
  }
  return this->subnetMask == ipv4.subnetMask;
}

bool Ipv4::operator<(const Ipv4 &ipv4) const {
  for (int i = 0; i < 4; ++i) {
    if (this->value[i] != ipv4.value[i]) {
      return this->value[i] < ipv4.value[i];
    }
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const Ipv4 &ipv4) {
  os << ipv4.value[0] << '.' << ipv4.value[1] << '.' << ipv4.value[2] << '.'
     << ipv4.value[3] << '/' << ipv4.subnetMask;
  return os;
}

// Getters & Setters:
void Ipv4::setValue(int value[4]) {
  for (int i = 0; i < 4; i++) {
    this->value[i] = (value[i] < 255) ? value[i] : 255;
  }
}

int *Ipv4::getValue() { return this->value; }

void Ipv4::setSubnetMask(int subnetMask) { this->subnetMask = subnetMask; }

int Ipv4::getSubnetMask() { return this->subnetMask; }

// Méthodes:
void Ipv4::autoAssign(Scheduler *scheduler) {
  // Initialisation:
  std::map<Ipv4, Ipv4>
      ipServers; // Declaration d'un tableau [ip serveur][ip dernier appareil],
                 // pour garder en mémoire les différents serveurs.
  std::vector<Sensor *> sensors;

  // Parcour de tout les sensors:
  for (auto &sensor : sensors) {
    for (auto &entry : ipServers) {
      // Sécurité des champs nulls:
      if (!sensor || !sensor->getServer()) {
        continue;
      }

      Ipv4 serverIp = sensor->getServer()->getIp();

      // Recherche si le serveur est déjà enregistré:
      if (ipServers.find(serverIp) != ipServers.end()) {
        // Incrémentation de l'ip du dernier sensor connu:
        int *lastVal = ipServers[serverIp].getValue();
        int nextVal[4] = {lastVal[0], lastVal[1], lastVal[2], lastVal[3] + 1};
        Ipv4 nextIp(nextVal, serverIp.getSubnetMask());
        ipServers[serverIp] = nextIp;
        sensor->setIp(nextIp);
      } else {
        // Cas d'un serveur inconnu:
        int *sVal = serverIp.getValue();
        int firstVal[4] = {sVal[0], sVal[1], sVal[2], sVal[3] + 1};
        Ipv4 firstIp(firstVal, serverIp.getSubnetMask());
        ipServers[serverIp] = firstIp;
        sensor->setIp(firstIp);
      }
    }
  }

  // Mise à jour du Scheduler:
  scheduler->setSensors(sensors);
}
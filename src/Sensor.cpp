#include "Sensor.hpp"
#include "Server.hpp"
#include <cstdlib> // rand()

// ID uniques
int Sensor::nextId = 1;

// Constructeur par défaut
Sensor::Sensor() : id(nextId++), type("Generic"), value(0.0), server(nullptr) {}

// Constructeur paramétré
Sensor::Sensor(const std::string &type, Server *server)
    : id(nextId++), type(type), value(0.0), server(server) {}

// Constructeur de recopie
Sensor::Sensor(const Sensor &other)
    : id(nextId++), type(other.type), value(other.value), server(other.server) {
}

// Opérateur d'affectation
Sensor &Sensor::operator=(const Sensor &other) {
  if (this != &other) {
    this->type = other.type;
    this->value = other.value;
    this->server = other.server;
    // On ne copie pas l'id pour garder l'unicité
  }
  return *this;
}

// Destructeur
Sensor::~Sensor() {}

// Getters & Setters
int Sensor::getId() const { return this->id; }
std::string Sensor::getType() const { return this->type; }

double Sensor::getValue() const { return this->value; }
void Sensor::setServer(Server *server) { this->server = server; }

Server *Sensor::getServer() const { return this->server; }

// Simulation d'une mesure de données aléatoires
void Sensor::execute() {
  this->value = (rand() % 1000) / 10.0; // entre 0.0 et 99.9

  std::string logMsg = "Sensor ID=" + std::to_string(id) + 
                       "\t| Type=" + type +
                       "  \t| Value=" + std::to_string(value);

  if (server) {
    server->consoleWrite(logMsg);
    server->fileWrite("data/" + type + "_logs.csv", logMsg);
  }
}

void Sensor::update() { this->execute(); }

// Surcharge <<
std::ostream &operator<<(std::ostream &os, const Sensor &sensor) {
  os << "Sensor[ID: " << sensor.id << ", Type: " << sensor.type
     << ", Value: " << sensor.value << "]";
  return os;
}
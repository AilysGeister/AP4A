#include "Sensor.hpp"
#include "Server.hpp"
#include <cstdlib> // rand()

/*======================================================================================================================
 Class: Sensor
 =====================================================================================================================*/

// ID uniques:
template <typename T> int Sensor<T>::nextId = 1;

// Constructeur par défaut:
template <typename T>
Sensor<T>::Sensor()
    : id(nextId++), server(nullptr), room(nullptr), measurement(0, "none") {}

// Constructeur paramétré:
template <typename T>
Sensor<T>::Sensor(const Ipv4 &ipv4, float accuracy, Server *server, Room *room)
    : id(nextId++), ip(ipv4), accuracy(accuracy), server(server), room(room) {}

// Constructeur de recopie
template <typename T>
Sensor<T>::Sensor(const Sensor &other)
    : id(nextId++), ip(other.ip), accuracy(other.accuracy),
      measurement(other.measurement), server(other.server), room(other.room) {}

// Opérateur d'affectation
template <typename T> Sensor<T> &Sensor<T>::operator=(const Sensor<T> &other) {
  if (this != &other) {
    this->accuracy = other.accuracy;
    this->measurement = other.measurement;
    this->server = other.server;
    this->room = other.room;
    // On ne copie pas l'id pour garder l'unicité
  }
  return *this;
}

// Destructeur:
template <typename T> Sensor<T>::~Sensor() {
  // if (server)
  //   delete server;
  // if (room)
  //   delete room;
  // bah non enfaite
}

// Getters & Setters:
template <typename T> int Sensor<T>::getId() const { return this->id; }

template <typename T> void Sensor<T>::setIp(const Ipv4 &ip) { this->ip = ip; }

template <typename T> Ipv4 Sensor<T>::getIp() const { return this->ip; }

template <typename T> void Sensor<T>::setServer(Server *server) {
  this->server = server;
}

template <typename T> Server *Sensor<T>::getServer() const {
  return this->server;
}

template <typename T> void Sensor<T>::update() {
  this->execute();
  std::string logMsg = "Sensor ID=" + std::to_string(id) +
                       " | IP=" + ip.toString() + "\t| Type=" + getType() +
                       "\t| Value=" + std::to_string(measurement.getValue()) +
                       " " + measurement.getUnit();
  if (server) {
    server->consoleWrite(logMsg);
    server->fileWrite("data/" + getType() + ".csv", logMsg);
  }
}

// Surcharge <<
template <typename T>
std::ostream &operator<<(std::ostream &os, const Sensor<T> &sensor) {
  os << "Sensor[ID: " << sensor.id << ", Type: non définie";
  return os;
}

// Méthodes:


/*======================================================================================================================
 Class: Thermometer
 =====================================================================================================================*/

Thermometer::Thermometer() : Sensor<float>() { measurement.setUnit("°C"); }
Thermometer::Thermometer(Ipv4 ipv4, float accuracy, Server *server)
    : Sensor<float>(ipv4, accuracy, server) {
  measurement.setUnit("°C");
}
Thermometer::Thermometer(const Thermometer &other) : Sensor<float>(other) {}

Data<float> Thermometer::getValue() const { return measurement; }

void Thermometer::execute() {
  float temp = this->room ? this->room->getTemperature() : 20.0f;
  float maxGap = temp * (1.0f - accuracy);
  measurement.setValue(randomInRange(temp - maxGap, temp + maxGap));
}

/*======================================================================================================================
 Class: HumiditySensor
 =====================================================================================================================*/

HumiditySensor::HumiditySensor() : Sensor<float>() { measurement.setUnit("%"); }
HumiditySensor::HumiditySensor(Ipv4 ipv4, float accuracy, Server *server)
    : Sensor<float>(ipv4, accuracy, server) {
  measurement.setUnit("%");
}
HumiditySensor::HumiditySensor(const HumiditySensor &other)
    : Sensor<float>(other) {} // ou adapter selon le type exact

Data<float> HumiditySensor::getValue() const { return measurement; }

void HumiditySensor::execute() {
  float humidity = this->room ? this->room->getHumidity() : 50.0f;
  float maxGap = humidity * (1.0f - accuracy);
  float measurementValue = randomInRange(humidity - maxGap, humidity + maxGap);
  if (measurementValue < 0.0f)
    measurementValue = 0.0f;
  if (measurementValue > 100.0f)
    measurementValue = 100.0f;
  measurement.setValue(measurementValue);
}

/*======================================================================================================================
  Class: PressureSensor
  =====================================================================================================================*/
PressureSensor::PressureSensor() : Sensor<int>() { measurement.setUnit("hPa"); }
PressureSensor::PressureSensor(Ipv4 ipv4, float accuracy, Server *server)
    : Sensor<int>(ipv4, accuracy, server) {
  measurement.setUnit("hPa");
}
PressureSensor::PressureSensor(const PressureSensor &other)
    : Sensor<int>(other) {}

Data<int> PressureSensor::getValue() const { return measurement; }

void PressureSensor::execute() {
  int pressure = this->room ? this->room->getPressure() : 1013;
  float maxGap = pressure * (1.0f - accuracy);
  measurement.setValue(
      static_cast<int>(randomInRange(pressure - maxGap, pressure + maxGap)));
}

/*======================================================================================================================
  Class: ParticleSensor
  =====================================================================================================================*/
ParticleSensor::ParticleSensor() : Sensor<int>() {
  measurement.setUnit("ug/m3");
}
ParticleSensor::ParticleSensor(Ipv4 ipv4, float accuracy, Server *server)
    : Sensor<int>(ipv4, accuracy, server) {
  measurement.setUnit("ug/m3");
}
ParticleSensor::ParticleSensor(const ParticleSensor &other)
    : Sensor<int>(other) {}

Data<int> ParticleSensor::getValue() const { return measurement; }

void ParticleSensor::execute() {
  int particles = this->room ? this->room->getParticles() : 15;
  float maxGap = particles * (1.0f - accuracy);
  measurement.setValue(
      static_cast<int>(randomInRange(particles - maxGap, particles + maxGap)));
}
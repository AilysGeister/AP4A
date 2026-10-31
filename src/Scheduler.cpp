#include "Scheduler.hpp"

// Constructeurs:
Scheduler::Scheduler() : timeStep(1) {}

Scheduler::Scheduler(int timeStep) : timeStep(timeStep) {}

Scheduler::Scheduler(const Scheduler &other)
    : sensors(other.sensors), timeStep(other.timeStep) {}

// Destructeur:
Scheduler::~Scheduler() {
  if (sensors.data()) {
    for (Sensor *sensor : sensors) {
      delete sensor;
    }
  }
}

// Opérateurs:
Scheduler &Scheduler::operator=(const Scheduler &other) {
  if (this != &other) {
    this->sensors = other.sensors;
    this->timeStep = other.timeStep;
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Scheduler &scheduler) {
  os << "Scheduler[Capteurs: " << scheduler.sensors.size()
     << ", Tick: " << scheduler.timeStep << "s]";
  return os;
}

// Getters & Setters:
void Scheduler::addSensor(Sensor *sensor) {
  if (sensor) {
    sensors.push_back(sensor);
  }
}

void Scheduler::removeSensor(Sensor *sensor) {
  if (sensor) {
    for (auto it = sensors.begin(); it != sensors.end(); ++it) {
      if (*it == sensor) {
        sensors.erase(it);
      }
    }
  }
}

void Scheduler::removeAllSensors() {
  for (auto it = sensors.begin(); it != sensors.end(); ++it) {
    delete *it;
  }
}

void Scheduler::setSensors(std::vector<Sensor *> sensors) {
  this->sensors = sensors;
}

std::vector<Sensor *> Scheduler::getSensors() { return this->sensors; }

Sensor *Scheduler::getSensor(int index) {
  if (index < sensors.size()) {
    return sensors[index];
  }
}

// Exécution séquentielle de la simulation
void Scheduler::simulation(int steps) {
  std::cout << "\n=== Démarrage de la simulation (" << steps
            << " étapes) ===" << std::endl;
  for (int step = 1; step <= steps; ++step) {
    std::cout << "--- Étape " << step << " ---" << std::endl;
    for (Sensor *sensor : sensors) {
      if (sensor) {
        sensor->update();
      }
    }
  }
}
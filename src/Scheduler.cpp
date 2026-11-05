#include "Scheduler.hpp"

// Constructeurs:
Scheduler::Scheduler() : timeStep(1) {}

Scheduler::Scheduler(int timeStep) : timeStep(timeStep) {}

Scheduler::Scheduler(const Scheduler &other)
    : sensors(other.sensors), timeStep(other.timeStep) {}

// Destructeur:
Scheduler::~Scheduler() { removeAllSensors(); }

// Opérateurs:
Scheduler &Scheduler::operator=(const Scheduler &other) {
  if (this != &other) {
    timeStep = other.timeStep;
    sensors = other.sensors;
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Scheduler &scheduler) {
  os << "Scheduler[Capteurs: " << scheduler.sensors.size()
     << ", Tick: " << scheduler.timeStep << "s]";
  return os;
}

// Getters & Setters:
void Scheduler::addSensor(ISensor *sensor) { sensors.push_back(sensor); }

void Scheduler::removeSensor(ISensor *sensor) {
  for (auto it = sensors.begin(); it != sensors.end(); ++it) {
    if (*it == sensor) {
      sensors.erase(it);
      break;
    }
  }
}

void Scheduler::removeAllSensors() {
  for (auto *sensor : sensors) {
    delete sensor;
  }
  sensors.clear();
}

void Scheduler::setSensors(std::vector<ISensor *> sensors) {
  this->sensors = sensors;
}

std::vector<ISensor *> Scheduler::getSensors() const { return this->sensors; }

ISensor *Scheduler::getSensor(int index) const {
  if (index >= 0 && index < sensors.size()) {
    return sensors[index];
  }
  return nullptr;
}

// Exécution séquentielle de la simulation
void Scheduler::simulation(int steps) {
  std::cout << "\n=== Démarrage de la simulation (" << steps
            << " étapes) ===" << std::endl;
  for (int step = 1; step <= steps; ++step) {
    std::cout << "--- Étape " << step << " ---" << std::endl;
    for (auto *sensor : sensors) {
      sensor->update();
    }
  }
}
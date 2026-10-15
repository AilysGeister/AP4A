#include "Scheduler.hpp"

// Constructeur par défaut
Scheduler::Scheduler() : timeStep(1) {}

// Constructeur paramétré
Scheduler::Scheduler(int timeStep) : timeStep(timeStep) {}

// Constructeur de recopie
Scheduler::Scheduler(const Scheduler &other)
    : sensors(other.sensors), timeStep(other.timeStep) {}

// Opérateur d'affectation
Scheduler &Scheduler::operator=(const Scheduler &other) {
  if (this != &other) {
    this->sensors = other.sensors;
    this->timeStep = other.timeStep;
  }
  return *this;
}

// Destructeur
Scheduler::~Scheduler() {}

void Scheduler::addSensor(Sensor *sensor) {
  if (sensor) {
    sensors.push_back(sensor);
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

// Surcharge <<
std::ostream &operator<<(std::ostream &os, const Scheduler &scheduler) {
  os << "Scheduler[Capteurs: " << scheduler.sensors.size()
     << ", Tick: " << scheduler.timeStep << "s]";
  return os;
}
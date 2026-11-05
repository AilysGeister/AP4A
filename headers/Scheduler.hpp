#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "Sensor.hpp"
#include <iostream>
#include <vector>

class Scheduler {
private:
  std::vector<ISensor *> sensors; // Liste des capteurs enregistrés
  int timeStep;                   // Intervalle ou pas de temps de simulation

public:
  // Constructeurs:
  Scheduler();
  Scheduler(int timeStep);
  Scheduler(const Scheduler &other);

  // Destructeur:
  ~Scheduler();

  // Opérateurs:
  Scheduler &operator=(const Scheduler &other);
  friend std::ostream &operator<<(std::ostream &os, const Scheduler &scheduler);

  // Getters & Setters:
  void addSensor(ISensor *sensor);
  void removeSensor(ISensor *sensor);
  void removeAllSensors();
  void setSensors(std::vector<ISensor *> sensors);
  std::vector<ISensor *> getSensors() const;
  ISensor *getSensor(int index) const;

  // Méthodes:
  void simulation(int steps);
};

#endif // SCHEDULER_HPP
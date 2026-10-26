#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "Sensor.hpp"
#include <iostream>
#include <vector>

class Scheduler {
private:
  std::vector<Sensor *> sensors; // Liste des capteurs enregistrés
  int timeStep;                  // Intervalle ou pas de temps de simulation

public:
  // Forme canonique
  Scheduler();
  Scheduler(int timeStep);
  Scheduler(const Scheduler &other);
  Scheduler &operator=(const Scheduler &other);
  ~Scheduler();

  // Gestion des capteurs
  void addSensor(Sensor *sensor);

  // Séquencement de la simulation
  void simulation(int steps);

  // Opérateurde sortie
  friend std::ostream &operator<<(std::ostream &os, const Scheduler &scheduler);
};

#endif // SCHEDULER_HPP
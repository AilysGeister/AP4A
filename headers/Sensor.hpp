#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <fstream>
#include <iostream>
#include <string>

// eviter les inclusions croisees
class Server;

class Sensor {
private:
  static int
      nextId; // Compteur statique pour attribuer un ID unique à chaque instance
  int id;     // Identifiant unique
  std::string type; // Type de capteur (ex: "Temperature", "Humidity")
  double value;     // Valeur mesurée
  Server *server;   // Pointeur vers le serveur associé

public:
  // Forme canonique
  Sensor();
  Sensor(const std::string &type, Server *server = nullptr);
  Sensor(const Sensor &other);
  Sensor &operator=(const Sensor &other);
  ~Sensor();

  // Getters & Setters
  int getId() const;
  std::string getType() const;
  double getValue() const;
  void setServer(Server *server);
  Server *getServer() const;

  // Methodesde simulation
  void execute(); // Génère une nouvelle donnée mesurée et l'envoie au serveur
  void update(); // Appelé par le Scheduler pour mettre à jour le comportement

  // Friend de sortie
  friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);
};

#endif // SENSOR_HPP
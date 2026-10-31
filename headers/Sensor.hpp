#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <fstream>
#include <iostream>
#include <string>

#include "Ip.hpp"

// Éviter les inclusions croisées:
class Server;

class Sensor {
private:
  Ipv4 ip;
  std::string type; // Type de capteur (ex: "Temperature", "Humidity")
  double value;     // Valeur mesurée
  Server *server;   // Pointeur vers le serveur associé
  static int
      nextId; // Compteur statique pour attribuer un ID unique à chaque instance
  int id;     // Identifiant unique

public:
  // Forme canonique:
  Sensor();
  Sensor(const std::string &type, Server *server = nullptr);
  Sensor(const Sensor &other);
  Sensor &operator=(const Sensor &other);
  ~Sensor();

  // Getters & Setters:
  void setIp(const Ipv4 &ip);
  Ipv4 getIp() const;
  std::string getType() const;
  double getValue() const;
  void setServer(Server *server);
  Server *getServer() const;

  // Methodesde simulation:
  /**
   * Génère une nouvelle donnée mesurée et l'envoie au serveur.
   */
  void execute();

  /**
   * Appelé par le Scheduler pour mettre à jour le comportement.
   */
  void update();

  // Friend de sortie:
  friend std::ostream &operator<<(std::ostream &os, const Sensor &sensor);
};

#endif // SENSOR_HPP
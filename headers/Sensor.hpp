#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <fstream>
#include <iostream>
#include <string>

#include "Data.hpp"
#include "Ip.hpp"
#include "Room.hpp"

// Évite les inclusions croisées:
class Server;

/**
 * Interface permettant au scheduler de manipuler les sensors, sans compléter le
 * template.
 */
class ISensor {
public:
  virtual ~ISensor() = default;
  virtual void update() = 0;
  virtual void execute() = 0;
  virtual int getId() const = 0;
  virtual Ipv4 getIp() const = 0;
  virtual void setIp(const Ipv4 &ip) = 0;
  virtual Server *getServer() const = 0;
  virtual void setServer(Server *server) = 0;
  virtual std::string getType() const = 0;
};

/**
 * Classe mère des sensors.
 * @tparam T Type de retour de la mesure
 */
template <typename T> class Sensor : public ISensor {
protected:
  Ipv4 ip;
  Server *server; // Pointeur vers le serveur associé
  Room *room;
  Data<T> measurement;
  static int
      nextId; // Compteur statique pour attribuer un ID unique à chaque instance
  int id;     // Identifiant unique
  float accuracy; // Simule un taux de confiance dans la mesure.

public:
  // Forme canonique:
  Sensor();
  Sensor(const Ipv4 &ipv4, float accuracy, Server *server = nullptr,
         Room *room = nullptr);
  Sensor(const Sensor &other);
  Sensor &operator=(const Sensor &other);
  virtual ~Sensor();

  // Getters & Setters:
  int getId() const override;
  void setIp(const Ipv4 &ip) override;
  Ipv4 getIp() const override;
  void setServer(Server *server) override;
  Server *getServer() const override;
  virtual Data<T> getValue() const = 0;

  float randomInRange(float min, float max) {
    return min + static_cast<float>(rand()) /
                     (static_cast<float>(RAND_MAX / (max - min)));
  }

  // Methodes de simulation:

  virtual void execute() = 0;

  void update() override;

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Sensor<U> &sensor);
};

class Thermometer : public Sensor<float> {
public:
  // Constructeurs:
  Thermometer();
  Thermometer(Ipv4 ipv4, float accuracy, Server *server = nullptr);
  Thermometer(const Thermometer &other);

  // Destructeur:
  ~Thermometer() override = default;

  // Méthodes:
  std::string getType() const override { return "Temperatures"; }
  Data<float> getValue() const override;
  void execute() override;
};

class HumiditySensor : public Sensor<float> {
public:
  // Constructeurs:
  HumiditySensor();
  HumiditySensor(Ipv4 ipv4, float accuracy, Server *server = nullptr);
  HumiditySensor(const HumiditySensor &other);

  // Destructeur:
  ~HumiditySensor() override = default;

  // Méthodes:
  std::string getType() const override { return "Humidite"; }
  Data<float> getValue() const override;
  void execute() override;
};

class PressureSensor : public Sensor<int> {
public:
  // Constructeurs:
  PressureSensor();
  PressureSensor(Ipv4 ipv4, float accuracy, Server *server = nullptr);
  PressureSensor(const PressureSensor &other);

  // Destructeur:
  ~PressureSensor() override = default;

  // Méthodes:
  std::string getType() const override { return "Pression"; }
  Data<int> getValue() const override;
  void execute() override;
};

class ParticleSensor : public Sensor<int> {
public:
  // Constructeurs:
  ParticleSensor();
  ParticleSensor(Ipv4 ipv4, float accuracy, Server *server = nullptr);
  ParticleSensor(const ParticleSensor &other);

  // Destructeur:
  ~ParticleSensor() override = default;

  // Méthodes:
  std::string getType() const override { return "Particules"; }
  Data<int> getValue() const override;
  void execute() override;
};

#endif // SENSOR_HPP
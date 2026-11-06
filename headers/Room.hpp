#ifndef SIMULATOR_ROOM_HPP
#define SIMULATOR_ROOM_HPP
#include <string>
#include <utility>

class Room {
private:
  float temperature, humidity;
  int pressure, particles;
  int id;
  static int nextId;
  std::string name;

public:
  // Constructeurs:
  Room()
      : temperature(20), humidity(50.0), pressure(1013), particles(15),
        id(++nextId), name("Salle " + std::to_string(id)) {}

  Room(std::string name)
      : temperature(20), humidity(50.0), pressure(1013), particles(15),
        id(++nextId), name(std::move(name)) {}

  Room(const Room &other)
      : temperature(other.temperature), humidity(other.humidity),
        pressure(other.pressure), particles(other.particles), id(++nextId),
        name(other.name) {}

  // Destructeur:
  ~Room() = default;

  // Getters & Setters:
  int getId() const { return id; }
  void setName(const std::string &name) { this->name = name; }
  std::string getName() { return name; }
  void setTemperature(float temperature) { this->temperature = temperature; }
  float getTemperature() const { return temperature; }
  void setHumidity(float humidity) { this->humidity = humidity; }
  float getHumidity() const { return humidity; }
  void setPressure(int pressure) { this->pressure = pressure; }
  int getPressure() const { return pressure; }
  void setParticles(int particles) { this->particles = particles; }
  int getParticles() const { return particles; }

  // Opérateurs:
  Room &operator=(const Room &other) {
    if (this != &other) {
      temperature = other.temperature;
      humidity = other.humidity;
      pressure = other.pressure;
      particles = other.particles;
      name = other.name;
    }
    return *this;
  }
};

#endif // SIMULATOR_ROOM_HPP
#ifndef SIMULATOR_ROOM_HPP
#define SIMULATOR_ROOM_HPP
#include <string>

class Room {
private:
  float temperature, humidity;
  int id, pressure, particles;
  static int nextId;
  std::string name;

public:
  // Constructeurs:
  Room()
      : id(++nextId), temperature(20), humidity(50.0), pressure(1013),
        particles(15), name("Salle " + std::to_string(id)) {}

  Room(std::string name)
      : id(++nextId), temperature(20), humidity(50.0), pressure(1013),
        particles(15), name(name) {}

  Room(const Room &other)
      : id(++nextId), temperature(other.temperature), humidity(other.humidity),
        particles(other.particles), name(other.name) {}

  // Destructeur:
  ~Room() = default;

  // Getters & Setters:
  int getId() { return id; }
  void setName(std::string name) { this->name = name; }
  std::string getName() { return name; }
  void setTemperature(float temperature) { this->temperature = temperature; }
  float getTemperature() { return temperature; }
  void setHumidity(float humidity) { this->humidity = humidity; }
  float getHumidity() { return humidity; }
  void setPressure(float pressure) { this->pressure = pressure; }
  int getPressure() { return pressure; }
  void setParticles(int particles) { this->particles = particles; }
  int getParticles() { return particles; }

  // Opérateurs:
  Room &operator=(const Room &other) {
    id = ++nextId;
    temperature = other.temperature;
    humidity = other.humidity;
    pressure = other.pressure;
    particles = other.particles;
    name = other.name;
  }
};

#endif // SIMULATOR_ROOM_HPP

#ifndef SIMULATOR_DATA_HPP
#define SIMULATOR_DATA_HPP

#include <string>

template <typename T> class Data {
private:
  T value;
  std::string unit;

public:
  // Constructeurs:
  Data() : value(T()), unit("none") {}
  Data(T value, const std::string &unit) : value(value), unit(unit) {}
  Data(const Data &other) : value(other.value), unit(other.unit) {}

  // Destructeur
  ~Data() = default;

  // Getters & Setters:
  void setValue(T value) { this->value = value; }

  void setUnit(const std::string &unit) { this->unit = unit; }
  T getValue() const { return this->value; }

  std::string getUnit() const { return this->unit; }

  // Opérateurs:
  Data &operator=(const Data &other) {
    this->value = other.value;
    this->unit = other.unit;
  }
};

#endif // SIMULATOR_DATA_HPP
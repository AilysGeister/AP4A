#ifndef SIMULATOR_IP_HPP
#define SIMULATOR_IP_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Scheduler;
class Server;
class ISensor;

class Ipv4 {
private:
  int value[4] = {0};
  int subnetMask = 0;

public:
  // Constructeur:
  Ipv4() {
    value[0] = 192;
    value[1] = 168;
    value[2] = 0;
    value[3] = 1;
    subnetMask = 24;
  }

  Ipv4(int val[4], int subnetMask) {
    for (int i = 0; i < 4; i++) {
      this->value[i] = (val[i] <= 255) ? val[i] : 255;
    }
    this->subnetMask = (subnetMask <= 32) ? subnetMask : 24;
  }

  Ipv4(const Ipv4 &ipv4) {
    for (int i = 0; i < 4; i++) {
      this->value[i] = ipv4.value[i]; // Correction de la copie
    }
    this->subnetMask = ipv4.subnetMask;
  }

  // Destructeur:
  ~Ipv4() = default;

  // Opérateurs:
  bool operator==(const Ipv4 &ipv4) const {
    for (int i = 0; i < 4; i++) {
      if (this->value[i] != ipv4.value[i]) {
        return false;
      }
    }
    return this->subnetMask == ipv4.subnetMask;
  }

  Ipv4 operator+(const Ipv4 &ipv4) {
    int newVal[4];
    for (int i = 0; i < 4; i++) {
      int sum = this->value[i] + ipv4.value[i];
      newVal[i] = (sum <= 255) ? sum : 255;
    }
    return Ipv4(newVal, this->subnetMask);
  }

  bool operator<(const Ipv4 &ipv4) const {
    for (int i = 0; i < 4; ++i) {
      if (this->value[i] != ipv4.value[i]) {
        return this->value[i] < ipv4.value[i];
      }
    }
    return false;
  }

  Ipv4 &operator=(const Ipv4 &ipv4) {
    for (int i = 0; i < 4; i++) {
      this->value[i] = ipv4.value[i];
    }
    this->subnetMask = ipv4.subnetMask;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Ipv4 &ipv4) {
    os << ipv4.value[0] << '.' << ipv4.value[1] << '.' << ipv4.value[2] << '.'
       << ipv4.value[3] << '/' << ipv4.subnetMask;
    return os;
  }

  // Getters & Setters:
  void setValue(int val[4]) {
    for (int i = 0; i < 4; i++) {
      this->value[i] = (val[i] <= 255) ? val[i] : 255;
    }
  }

  const int *getValue() const { return this->value; }

  void setSubnetMask(int subnetMask) {
    this->subnetMask = (subnetMask <= 32) ? subnetMask : 24;
  }

  int getSubnetMask() const { return this->subnetMask; }

  // Méthodes:
  inline void autoAssign(Scheduler *scheduler);

  std::string toString() const {
    return std::to_string(this->value[0]) + "." +
           std::to_string(this->value[1]) + "." +
           std::to_string(this->value[2]) + "." +
           std::to_string(this->value[3]);
  }
};
#endif

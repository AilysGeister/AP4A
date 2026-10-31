#ifndef SIMULATOR_IP_HPP
#define SIMULATOR_IP_HPP

#include <string>

class Scheduler;

class Ipv4 {
private:
  int value[4] = {0};
  int subnetMask = 0;

public:
  // Constructeur:
  Ipv4();
  Ipv4(int value[4], int subnetMask);
  Ipv4(const Ipv4 &ipv4);

  // Destructeur:
  ~Ipv4();

  // Opérateurs:
  bool operator==(const Ipv4 &ipv4);
  Ipv4 operator+(const Ipv4 &ipv4);
  bool operator<(const Ipv4 &ipv4) const;
  friend std::ostream &operator<<(std::ostream &os, const Ipv4 &ipv4);

  // Getters & Setters:
  void setValue(int value[4]);
  int *getValue();
  void setSubnetMask(int subnetMask);
  int getSubnetMask();

  // Méthodes:
  /**
   * Simule un protocole d'adressaae dynamique comme DHCP.
   * @param scheduler
   * @return
   */
  void autoAssign(Scheduler *scheduler);
};
#endif

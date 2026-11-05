#include "Ip.hpp"
#ifndef SCHEDULER_HPP
#include "Scheduler.hpp"
#include "Server.hpp"
#endif

/**
 * Simule un protocole d'adressaae dynamique comme DHCP.
 * @param scheduler
 * @return
 */
inline void Ipv4::autoAssign(Scheduler *scheduler) {
  if (!scheduler)
    return;

  std::map<Ipv4, Ipv4>
      ipServers; // Declaration d'un tableau [ip serveur][ip dernier appareil],
  // pour garder en mémoire les différents serveurs.
  std::vector<ISensor *> sensors = scheduler->getSensors();

  for (auto &sensor : sensors) {
    // Sécurité des champs nulls:
    if (!sensor || !sensor->getServer()) {
      continue;
    }

    Ipv4 serverIp = sensor->getServer()->getIp();

    // Recherche si le serveur est déjà enregistré:
    if (ipServers.find(serverIp) != ipServers.end()) {
      // Incrémentation de l'ip du dernier sensor connu:
      const int *lastVal = ipServers[serverIp].getValue();
      int nextVal[4] = {lastVal[0], lastVal[1], lastVal[2], lastVal[3] + 1};
      Ipv4 nextIp(nextVal, serverIp.getSubnetMask());
      ipServers[serverIp] = nextIp;
      sensor->setIp(nextIp);
    } else {
      // Cas d'un serveur inconnu:
      const int *sVal = serverIp.getValue();
      int firstVal[4] = {sVal[0], sVal[1], sVal[2], sVal[3] + 1};
      Ipv4 firstIp(firstVal, serverIp.getSubnetMask());
      ipServers[serverIp] = firstIp;
      sensor->setIp(firstIp);
    }
  }

  // Mise à jour du Scheduler:
  scheduler->setSensors(sensors);
}
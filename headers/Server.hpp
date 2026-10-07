#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server {
private:
    std::string name;
    std::string ip;
    int version;
    int port;
    /*
    ofstream out;
    //pareil pour chauqe type de sensor
    */

public:
    Server();

    Server(std::string name, int version);

    Server(const Server&);

    ~Server();

    Server& operator= (const Server&);

    void setName(std::string name);

    void setIp(std::string ip);

    void setVersions(int version);

    void setPort(int port);

    std::string getName();

    std::string getIp();

    int getVersion();

    int getPort();

    void consoleWriter();

    void fileWriter();
};

#endif

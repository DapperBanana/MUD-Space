#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <string>

class PersistenceManager {
public:
    PersistenceManager(const std::string& filepath);
    bool saveWorldState(const std::string& worldState);
    std::string loadWorldState();
private:
    std::string filepath_;
};

#endif
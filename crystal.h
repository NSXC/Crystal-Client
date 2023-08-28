#ifndef CRYSTAL_H
#define CRYSTAL_H

#include <iostream>
#include <map>
#include <string>

class crystalserver {
public:
    std::string execute(const std::string& command);

private:
    std::map<std::string, std::string> cache;
};

#endif // CRYSTAL_H

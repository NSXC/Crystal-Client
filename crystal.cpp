#include "crystal.h"

std::string crystalserver::execute(const std::string& command) {
    std::string response;

    if (command.find("GET:") == 0) {
        std::string key = command.substr(4);
        if (cache.find(key) != cache.end()) {
            response = cache[key];
        }
        else {
            response = "Key not found in cache";
        }
    }
    else if (command.find("SET:") == 0) {
        std::string data = command.substr(4);
        size_t pos = data.find(':');
        if (pos != std::string::npos) {
            std::string key = data.substr(0, pos);
            std::string value = data.substr(pos + 1);
            cache[key] = value;
            response = "Key " + key + " set with value " + value;
        }
        else {
            response = "Invalid data format";
        }
    }
    else if (command.find("REWRITE:") == 0) {
        std::string data = command.substr(8);
        size_t pos = data.find(':');
        if (pos != std::string::npos) {
            std::string key = data.substr(0, pos);
            std::string value = data.substr(pos + 1);
            if (cache.find(key) != cache.end()) {
                cache[key] = value;
                response = "Key " + key + " rewritten with value " + value;
            }
            else {
                response = "Key not found in cache";
            }
        }
        else {
            response = "Invalid data format";
        }
    }
    else if (command.find("RENAME:") == 0) {
        std::string data = command.substr(7);
        size_t pos = data.find(':');
        if (pos != std::string::npos) {
            std::string oldKey = data.substr(0, pos);
            std::string newKey = data.substr(pos + 1);
            if (cache.find(oldKey) != cache.end()) {
                cache[newKey] = cache[oldKey];
                cache.erase(oldKey);
                response = "Key " + oldKey + " renamed to " + newKey;
            }
            else {
                response = "Key not found in cache";
            }
        }
        else {
            response = "Invalid data format";
        }
    }
    else {
        response = "Invalid command";
    }

    return response;
}

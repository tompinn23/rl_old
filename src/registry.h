#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <vector>

typedef unsigned char tile;

typedef struct {
    std::string name;
    std::vector<std::string> attrs;
    std::vector<tile> plan;
} room;



void add_to_registry(room room);

#endif // !REGISTRY_H

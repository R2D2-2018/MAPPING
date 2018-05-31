#ifndef NODE_HPP
#define NODE_HPP

#include <stdint.h>

namespace Pathfinding
{
    class Node
    {
    public:
        Node(){};
        Node(uint32_t id){};
        Node(uint32_t id, Node** edges, uint32_t edgesCount){};
    };
}

#endif

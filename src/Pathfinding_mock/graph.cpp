/**
 * @file      graph.cpp
 * @brief     Graph class definitions
 * @author    Julian van Doorn
 * @license   See LICENSE
 */

#include "graph.hpp"

namespace Pathfinding {
Graph::Graph() : nodes(nullptr), nodeCount(0) {
}

Graph::Graph(NodeArray nodes, uint32_t nodeCount) : nodes(nodes), nodeCount(nodeCount) {
}

void Graph::getNodes(NodeArray &nodes, uint32_t &len) const {
    nodes = this->nodes;
    len = this->nodeCount;
}

void Graph::setNodes(NodeArray nodes, uint32_t len) {
    this->nodes = nodes;
    this->nodeCount = len;
}

Node *Graph::getNodes() const {
    return nodes;
}

Node &Graph::getNodeWithId(NodeId id) const {
    // quick lookup
    if (id < nodeCount && nodes[id].getId() == id) {
        return nodes[id];
    }

    // fallback
    for (uint32_t i = 0; i < nodeCount; i++) {
        if (nodes[i].getId() == id) {
            return nodes[i];
        }
    }
}

} // namespace Pathfinding
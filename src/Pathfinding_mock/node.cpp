/**
 * @file      node.cpp
 * @brief     Node class definitions
 * @author    Julian van Doorn
 * @license   See LICENSE
 */

#include "node.hpp"

namespace Pathfinding {
Node::Node() : id(-1), edges(nullptr), edgesCount(0) {
}

Node::Node(int32_t id) : id(id), edges(nullptr), edgesCount(0) {
}

Node::Node(int32_t id, EdgeArray edges, uint32_t edgesCount) : id(id), edges(edges), edgesCount(edgesCount) {
}

int32_t Node::getId() const {
    return id;
}

void Node::getEdges(EdgeArray &edges, uint32_t &edgesCount) const {
    edges = this->edges;
    edgesCount = this->edgesCount;
}

void Node::setEdges(EdgeArray edges, uint32_t edgesCount) {
    this->edges = edges;
    this->edgesCount = edgesCount;
}

uint32_t Node::getState() const {
    return this->state;
}

void Node::setState(uint32_t state) {
    this->state = state;
}

Node &Node::getParent() const {
    return *this->parent;
}

void Node::setParent(Node &parent) {
    this->parent = &parent;
}

void Node::setParent(std::nullptr_t parent) {
    this->parent = nullptr;
}
} // namespace Pathfinding
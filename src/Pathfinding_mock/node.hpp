/**
 * @file      node.hpp
 * @brief     Node class declarations
 * @author    Julian van Doorn
 * @license   See LICENSE
 */

#ifndef NODE_HPP
#define NODE_HPP

#include "../wrap-hwlib.hpp"

namespace Pathfinding {
using NodeId = uint32_t;
using Edge = class Node *;
using NodeArray = class Node *;
using EdgeArray = Edge *;

class Node {
  private:
    int32_t id;
    EdgeArray edges;
    uint32_t edgesCount;
    uint32_t state;
    Edge parent;

  public:
    /**
     * @brief Empty constructor
     */
    Node();

    /**
     * @brief Construct a new Node object with the given id
     *
     * @param id Id of the constructed node
     */
    Node(int32_t id);

    /**
     * @brief Construct a new Node object with the given id and edges
     *
     * @param id Id of the constructed node
     * @param edges Edges array to use for this node
     * @param edgesCount Amount of edges this node has
     */
    Node(int32_t id, EdgeArray edges, uint32_t edgesCount);

    /**
     * @brief Returns the Id of this node as set by the constructor
     *
     * @return -1 when id is not set, any other int when id is set
     */
    int32_t getId() const;

    /**
     * @brief Gets the edges array of this Node
     *
     * @param[out] edges Edges array pointer to change its value to Node** Node::edges
     * @param[out] edgesCount Integer pointer to change its value to the length of Node** Node::edges
     */
    void getEdges(EdgeArray &edges, uint32_t &edgesCount) const;

    /**
     * @brief Sets the edges array of this Node
     *
     * @param[in] edges Edges array to useas reference
     * @param[in] edgesCount Amount of edges the edges array has
     */
    void setEdges(EdgeArray edges, uint32_t edgesCount);

    /**
     * @brief Returns int Node::state
     *
     * @return int State of this node
     */
    uint32_t getState() const;

    /**
     * @brief Changes int Node::state to state
     *
     * @param state State this node should have
     */
    void setState(uint32_t state);

    /**
     * @brief Get the parent of this node
     *
     * @return Node* Parent of this node
     */
    Node &getParent() const;

    /**
     * @brief Set the parent of this node
     *
     * @param parent Parent of this node
     */
    void setParent(Node &parent);

    /**
     * @brief Set the parent of this node
     *
     * @param parent Parent of this node
     */
    void setParent(std::nullptr_t parent);

    template <class T>
    friend T &operator<<(T &os, const Node &n) {
        return os << "Node " << n.id;
    }

    bool operator==(const Node &n) const {
        return this == &n;
    }

    bool operator!=(const Node &n) const {
        return !(this == &n);
    }

    bool operator==(nullptr_t n) const {
        (void)n; // Suppress warning for now.
        return this == n;
    }

    bool operator!=(nullptr_t n) const {
        (void)n; // Suppress warning for now.
        return !(this == n);
    }
};
} // namespace Pathfinding

#endif // NODE_HPP
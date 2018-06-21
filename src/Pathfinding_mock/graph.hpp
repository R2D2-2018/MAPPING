/**
 * @file      graph.hpp
 * @brief     Graph class declarations
 * @author    Julian van Doorn
 * @license   See LICENSE
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "node.hpp"

namespace Pathfinding {
class Graph {
  private:
    NodeArray nodes;
    uint32_t nodeCount;

  public:
    /**
     * @brief Default Graph Constructor
     *
     * @details
     * Constructs a graph object with all external references and parameters nulled.
     */
    Graph();

    /**
     * @brief Construct a new Graph object
     *
     * @details
     * Graphs are used in pathfinding to contain a travelable map.
     * All data regarding a map is reachable via this datatype.
     *
     * @param[in] nodes Array of all nodes in this graph.
     * @param[in] nodeCount Count of all nodes in this graph.
     * @param[in] cumulativeEdges Array of all edges in this graph.
     * @param[in] cumulativeEdgesCount Count of all edges in this graph.
     */
    Graph(NodeArray nodes, uint32_t nodeCount);

    /**
     * @brief Replaces the pointers given with pointers pointing towards Node* Graph::nodes and its length
     *
     * @param[out] nodes Nodes array pointer to write to
     * @param[out] len Length of the nodes array
     */
    void getNodes(NodeArray &nodes, uint32_t &len) const;

    /**
     * @brief Returns a reference to the Node with the given id
     *
     * @param[in] id Id to find in nodes
     */
    Node &getNodeWithId(NodeId id) const;

    /**
     * @brief Sets the internal nodes pointer to point to the given NodeArray nodes and sets the internal nodeCount to len
     *
     * @param[in] nodes
     * @param[in] len
     */
    void setNodes(NodeArray nodes, uint32_t len);

    /**
     * @brief Returns a pointer to the first node in Node* Graph::nodes
     *
     * @return Node* First node in Node* Graph::nodes
     */
    NodeArray getNodes() const;

    template <class T>
    friend T &operator<<(T &os, const Graph &n) {
        return os << "Graph " << (void *)&n;
    }
};
} // namespace Pathfinding

#endif // GRAPH_HPP
/**
 * @file
 * @brief     mock graph class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "node.hpp"

namespace Pathfinding {
class Graph {
    //< This is a mock class of the Graph class used by path finding.
    //< It contains a (dummy) implementations of the methods that are
    //< relevant for this module (mapping) in order to create a new
    //< instance of Pathfinding::Graph. The content of this file is
    //< based on the state of the development branch of PATHFINDING
    //< at 11:56 PM 31/5/2018. When the module gets updated, this
    //< file needs to be cahnged manually.
    //< Unfortunately, the pathfinding module is running on a
    //< different platform currently, so it is not possible to
    //< simply include the file from the pathfinding repo, however
    //< that would be desirable.
  public:
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
    Graph(Node *nodes, uint32_t nodeCount, Node **cumulativeEdges, uint32_t cumulativeEdgesCount){};
};
} // namespace Pathfinding

#endif

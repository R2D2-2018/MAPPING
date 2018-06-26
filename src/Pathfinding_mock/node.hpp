/**
 * @file
 * @brief     mock node class
 * @author    Bendeguz Toth
 * @license   See LICENSE
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <stdint.h>

namespace Pathfinding {
///< This is a mock class of the Node class used by path finding.
///< It contains a (dummy) implementations of the methods that are
///< relevant for this module (mapping) in order to create a new
///< instance of Pathfinding::Graph. The content of this file is
///< based on the state of the development branch of PATHFINDING
///< at 11:56 PM 31/5/2018. When the module gets updated, this
///< file needs to be cahnged manually.
///< Unfortunately, the pathfinding module is running on a
///< different platform currently, so it is not possible to
///< simply include the file from the pathfinding repo, however
///< that would be desirable.
class Node {
  public:
    /**
     * @brief Empty constructor
     */
    Node(){};
    /**
     * @brief Construct a new Node object with the given id
     *
     * @param id Id of the constructed node
     */
    Node(uint32_t id){};

    /**
     * @brief Construct a new Node object with the given id and edges
     *
     * @param id Id of the constructed node
     * @param edges Edges array to use for this node
     * @param edgesCount Amount of edges this node has
     */
    Node(uint32_t id, Node **edges, uint32_t edgesCount){};
};
} // namespace Pathfinding

#endif

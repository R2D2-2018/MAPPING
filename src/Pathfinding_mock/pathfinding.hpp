/**
 * @file      queue.hpp
 * @brief     queue declarations
 * @author    Julian van Doorn
 * @license   See LICENSE
 */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "graph.hpp"
#include "node.hpp"
#include "object_pool.hpp"
#include <array>

namespace Pathfinding {
/*
constexpr const uint32_t graphsLen = 10;
constexpr const uint32_t nodesLen = 64;
constexpr const uint32_t edgesLen = 512;
extern std::array<Graph, graphsLen> graphs;
extern ObjectPool<char, nodesLen> nodePool;
extern ObjectPool<NodeArray, edgesLen> edgePool;*/
extern ObjectPool<char, 64> nodePool;

/**
 * @brief Adds a node to the internal graph used for pathfinding.
 *
 * @param nodeId[in] Id of node to add
 * @return true On success
 * @return false On failure (memory full, id already used, etc.)
 */
bool addNode(NodeId nodeId);

/**
 * @brief Adds a strong edge from node 0 to node 1 and back.
 *
 * @param node0[in] First node
 * @param node1[in] Second node
 * @return true On success
 * @return false On failure (memory full, edge already exists, etc.)
 */
bool addEdge(NodeId node0, NodeId node1);

/**
 * @brief Removes the edges from node 0 to node 1 and back.
 *
 * @param node0[in] First node
 * @param node1[in] Second node
 * @return true On success
 * @return false On failure
 */
bool removeEdge(NodeId node0, NodeId node1);

} // namespace Pathfinding

#endif // PATHFINDING_HPP
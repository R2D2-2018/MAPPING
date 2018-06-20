#include "pathfinding.hpp"

namespace Pathfinding {
std::array<Graph, graphsLen> graphs = {};
ObjectPool<Node, nodesLen> nodePool = {};
ObjectPool<Edge, edgesLen> edgePool = {};

#ifdef BMPTK_TARGET_test
Graph &getDebugGraph() {
    return graphs[0];
}

NodeArray getDebugNodes() {
    return graphs[0].getNodes();
}

void reset() {
    graphs = std::array<Graph, graphsLen>{};
    nodePool = ObjectPool<Node, nodesLen>();
    edgePool = ObjectPool<Edge, edgesLen>();
}
#endif

bool addNode(NodeId nodeId) {
    Graph &graph = graphs[0];

    NodeArray nodes;
    uint32_t nodeCount;
    NodeArray newNodes;
    uint32_t newNodeCount;

    graphs[0].getNodes(nodes, nodeCount);

    newNodes = nodePool.allocateBlocks(nodeCount + 1);

    if (newNodes == nullptr) {
        return false;
    }

    for (uint32_t i = 0; i < nodeCount; i++) {
        newNodes[i] = nodes[i];
    }

    newNodes[nodeCount] = Node(nodeId);
    newNodeCount = nodeCount + 1;

    graph.setNodes(newNodes, newNodeCount);

    return true;
}

bool addEdge(NodeId node0Id, NodeId node1Id) {
    Graph &graph = graphs[0];

    Node &node0 = graph.getNodeWithId(node0Id);
    Node &node1 = graph.getNodeWithId(node1Id);

    EdgeArray edges;
    uint32_t edgesCount;

    {
        node0.getEdges(edges, edgesCount);
        EdgeArray newEdges = edgePool.allocateBlocks(edgesCount + 1);

        if (newEdges == nullptr) {
            return false;
        }

        for (uint32_t i = 0; i < edgesCount; i++) {
            newEdges[i] = edges[i];
        }

        newEdges[edgesCount] = &node1;

        node0.setEdges(newEdges, edgesCount + 1);

        if (edges != nullptr) {
            edgePool.deallocateBlocks(edges);
        }
    }

    {
        node1.getEdges(edges, edgesCount);
        EdgeArray newEdges = edgePool.allocateBlocks(edgesCount + 1);

        if (newEdges == nullptr) {
            return false;
        }

        for (uint32_t i = 0; i < edgesCount; i++) {
            newEdges[i] = edges[i];
        }

        newEdges[edgesCount] = &node0;

        node1.setEdges(newEdges, edgesCount + 1);

        if (edges != nullptr) {
            edgePool.deallocateBlocks(edges);
        }
    }

    return true;
}
} // namespace Pathfinding
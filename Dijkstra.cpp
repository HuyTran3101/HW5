#include "Dijkstra.h"
#include "BetterPriorityQueue.h"

#include <climits>
#include <stdexcept>

using namespace std;

// Time complexity for these implementations: O(V*E + V*log(V)).
// GetOutwardEdgesFrom() scans all E edges for each of V extracted nodes.
// Update() searches up to V queue items and bubbles an item up the heap;
// it may be called for each of E edges.
// Pushing/popping V items costs O(V*log(V)).
// The graph's GetNodes() also takes O(V*log(V)).
// Auxiliary space: O(V) for the priority queue.
int dijkstra(nodekey_t start, nodekey_t end, const Graph* g) {
    if (g == nullptr || !g->IsPresent(start) || !g->IsPresent(end)) {
        throw invalid_argument("Graph or start/end node is invalid");
    }

    if (start == end) {
        return 0;
    }

    BetterPriorityQueue queue;

    // Start has distance 0. Other nodes start unreachable (INT_MAX).
    for (nodekey_t key : g->GetNodes()) {
        BPQNode item;
        item.gnode = key;
        if (key == start) {
            item.pri = 0;
        }
        queue.push(item);
    }

    while (!queue.empty()) {
        // In a min-heap, top() has the shortest remaining distance.
        BPQNode current = queue.top();
        queue.pop();

        // All remaining nodes are unreachable from start.
        if (current.pri == INT_MAX) {
            return INT_MAX;
        }

        if (current.gnode == end) {
            return current.pri;
        }

        // Check each edge leaving the current node.
        for (const GraphEdge* edge :
             g->GetOutwardEdgesFrom(current.gnode)) {

            // Use a wider type so distance + weight cannot overflow int.
            long long candidate =
                static_cast<long long>(current.pri)
                + static_cast<long long>(edge->weight);

            // INT_MAX is reserved for unreachable distances.
            if (candidate >= INT_MAX) {
                continue;
            }

            BPQNode neighbor;
            neighbor.gnode = edge->to;
            neighbor.pri = static_cast<int>(candidate);

            // Update only succeeds when the new distance is smaller.
            // Already processed nodes have been removed from the queue.
            queue.Update(neighbor);
        }
    }

    return INT_MAX;
}
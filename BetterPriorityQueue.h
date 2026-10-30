#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include "Graph.h"
#include <climits>
#include <functional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Each queue item represents a graph node and its current known distance.
// The comparison operators compare priorities, while == matches node keys.
struct BPQNode {
    int pri = INT_MAX;
    bool visited = false;
    nodekey_t gnode = INVALID_NODE_KEY;

    bool operator<(const BPQNode& other) const {
        return pri < other.pri;
    }

    bool operator>(const BPQNode& other) const {
        return pri > other.pri;
    }

    bool operator==(const BPQNode& other) const {
        return gnode == other.gnode;
    }
};

// A min-priority queue with the ability to decrease a node's priority.
class BetterPriorityQueue :
    public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>> {
public:
    bool Contains(const BPQNode& node) const;
    bool Update(const BPQNode& node);
    string ToString() const;
    static string BPQNodeToString(const BPQNode& node);
};

#endif
#include "BetterPriorityQueue.h"

#include <utility>
#include <sstream>

// The protected vector 'c' contains the queue's heap elements.
// Equality checks gnode, so priorities do not have to match.
bool BetterPriorityQueue::Contains(const BPQNode& node) const {
    for (const BPQNode& current : this->c) {
        if (current == node) {
            return true;
        }
    }
    return false;
}

// Dijkstra only needs a lower priority (a shorter known distance).
// After decreasing a key, move it toward the root until the parent has
// a priority no greater than the child. This preserves the min-heap.
bool BetterPriorityQueue::Update(const BPQNode& node) {
    for (size_t i = 0; i < this->c.size(); i++) {
        if (this->c[i] == node) {
            if (node.pri >= this->c[i].pri) {
                return false;
            }
            this->c[i].pri = node.pri;

            // The only possible heap violation is between this item
            // and its parent. Bubble up until that is fixed.
            while (i > 0) {
                size_t parent = (i - 1) / 2;
                if (this->c[parent].pri <= this->c[i].pri) {
                    break;
                }
                std::swap(this->c[parent], this->c[i]);
                i = parent;
            }
            return true;
        }
    }
    return false;
}

string BetterPriorityQueue::BPQNodeToString(const BPQNode& node) {
    return "(" + to_string(node.gnode) + ", pri: " + to_string(node.pri) + ")";
}

// Print the underlying binary heap in its actual vector order.
string BetterPriorityQueue::ToString() const {
    ostringstream out;
    out << "[";
    for (size_t i = 0; i < this->c.size(); i++) {
        if (i > 0) {
            out << ", ";
        }
        out << BPQNodeToString(this->c[i]);
    }
    out << "]";
    return out.str();
}
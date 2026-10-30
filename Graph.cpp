#include "Graph.h"

#include <sstream>
#include <utility>
#include <stdexcept>

using namespace std;

// Make independent copies of heap-allocated edges to avoid shared ownership.
Graph::Graph(const Graph& other) : nodes(other.nodes) {
    try {
        for (const GraphEdge* edge : other.edges) {
            GraphEdge* copy = new GraphEdge(*edge);
            try {
                edges.push_back(copy);
            } catch (...) {
                delete copy;
                throw;
            }
        }
    } catch (...) {
        for (GraphEdge* edge : edges) delete edge;
        throw;
    }
}

// Copy-and-swap makes self-assignment safe and keeps this graph unchanged
// if allocating an edge for the copied graph fails.
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        Graph copy(other);
        nodes.swap(copy.nodes);
        edges.swap(copy.edges);
    }
    return *this;
}

Graph::~Graph() {
    for (GraphEdge* edge : edges) {
        delete edge;
    }
}

void Graph::AddNode(nodekey_t key) {
    if (key == INVALID_NODE_KEY || IsPresent(key)) {
        throw invalid_argument("Invalid or duplicate node key");
    }
    nodes.push_back(key);
}

const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey,
                                nodekey_t toNodeKey,
                                unsigned int weight) {
    if (!IsPresent(fromNodeKey) || !IsPresent(toNodeKey)) {
        throw invalid_argument("Both endpoints must exist in the graph");
    }
    for (const GraphEdge* edge : edges) {
        if (edge->from == fromNodeKey && edge->to == toNodeKey) {
            throw invalid_argument("Duplicate directed edge");
        }
    }

    // Allocate each edge on the heap: callers receive a pointer to it.
    GraphEdge* edge = new GraphEdge{fromNodeKey, toNodeKey, weight};
    try {
        edges.push_back(edge);
    } catch (...) {
        delete edge;
        throw;
    }
    return edge;
}

bool Graph::IsPresent(nodekey_t key) const {
    for (nodekey_t node : nodes) {
        if (node == key) return true;
    }
    return false;
}

string Graph::NodesToString() const {
    ostringstream out;
    out << "[";
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i != 0) out << ", ";
        out << "(" << nodes[i] << ")";
    }
    out << "]";
    return out.str();
}

string Graph::EdgesToString() const {
    ostringstream out;
    out << "[";
    for (size_t i = 0; i < edges.size(); ++i) {
        if (i != 0) out << ", ";
        const GraphEdge* edge = edges[i];
        out << "((" << edge->from << ")->(" << edge->to
            << ") w:" << edge->weight << ")";
    }
    out << "]";
    return out.str();
}

set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const {
    set<const GraphEdge*> result;
    for (const GraphEdge* edge : edges) {
        if (edge->from == nodeKey) result.insert(edge);
    }
    return result;
}

set<nodekey_t> Graph::GetNodes() const {
    // A set represents the nodes without depending on their insertion order.
    return set<nodekey_t>(nodes.begin(), nodes.end());
}

size_t Graph::Size() const {
    return edges.size();
}

size_t Graph::Order() const {
    return nodes.size();
}

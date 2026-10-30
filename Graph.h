#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <string>
#include <stdexcept>

using namespace std;

// Type used to identify nodes
#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

// Represents a directed edge between two nodes
struct GraphEdge {
    nodekey_t from;
    nodekey_t to;
    unsigned int weight;
};

class Graph {
public:
    // Constructor
    Graph() = default;

    // Copy constructor
    Graph(const Graph& other);

    // Copy assignment operator
    Graph& operator=(const Graph& other);

    // Destructor
    ~Graph();

    // Adds a node to the graph
    // Throws invalid_argument for duplicate or invalid keys
    void AddNode(nodekey_t key = 0);

    // Adds a directed edge between two existing nodes
    // Throws invalid_argument for invalid endpoints
    // or duplicate edges
    const GraphEdge* AddEdge(
        nodekey_t fromNodeKey,
        nodekey_t toNodeKey,
        unsigned int weight = 0
    );

    // Returns true if the node exists
    bool IsPresent(nodekey_t key) const;

    // Returns a string containing all nodes
    string NodesToString() const;

    // Returns a string containing all edges
    string EdgesToString() const;

    // Returns all outgoing edges from the given node
    set<const GraphEdge*> GetOutwardEdgesFrom(
        nodekey_t nodeKey
    ) const;

    // Returns a set of all node keys
    set<nodekey_t> GetNodes() const;

    // Returns the number of edges
    size_t Size() const;

    // Returns the number of nodes
    size_t Order() const;

private:
    // Stores node keys in insertion order
    vector<nodekey_t> nodes;

    // Stores pointers to dynamically allocated edges
    vector<GraphEdge*> edges;
};

#endif // GRAPH_H